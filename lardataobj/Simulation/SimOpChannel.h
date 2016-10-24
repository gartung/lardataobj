/*
 * @file   SimOpChannel.h
 * @brief  object containing MC truth information necessary for making
 *         RawDigits and doing back tracking
 * @author seligman@nevis.columbia.edu
 * @see    SimOpChannel.cxx
 * 
 * This class uses only LArSoft libraries that are header only.
 */


#ifndef LARSIMOBJ_SIMULATION_SIMCHANNEL_H
#define LARSIMOBJ_SIMULATION_SIMCHANNEL_H

// LArSoftObj libraries
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"

// C/C++ standard libraries
#include <string>
#include <vector>
#include <utility> // std::pair


namespace sim {
  
  /// Ionization photons from a Geant4 track
  struct TrackSDP{
    int trackID;      ///< Geant4 supplied trackID
    float nPhotonsFrac; ///< fraction of hit energy from the particle with this trackID
    float nPhotons;     ///< energy from the particle with this trackID [MeV]

    TrackSDP() {}
    
#ifndef __GCCXML__
    
    TrackSDP(int id, float phF, float ph) : trackID(id), nPhotonsFrac(phF), nPhotons (ph) {}
    
#endif

  };
  
  
  /**
   * @brief Ionization at a point of the TPC sensitive volume
   * 
   * This class stores information about the ionization from the simulation
   * of a small step of a track through the TPC active volume.
   * 
   * Ionization information consists of both energy and number of electrons.
   * It is of paramount importance to understand what each field stores:
   * 
   * - position: where the ionization occurred (from Geant4 simulation)
   * - track ID: Geant4 track ID of the ionizing particle
   * - energy: amount of energy released by ionization (from Geant4 simulation)
   * - electrons: amount of electrons reaching the readout channel
   *
   * Note the different definition of the electrons respect to the rest:
   * it describes the electrons at the anode _after_ the drifting occurred,
   * while all the other quantities can be related to the moment the ionization
   * happened.
   * 
   * The number of electrons typically includes inefficiencies and physics
   * effects that reduce and spread the electrons. In the simulation,
   * this yields a fractional number of electrons.
   * 
   * Each SDP is also typically associated with a time (timePDclock) count, that is
   * the time at which the ionized electrons reached the readout channel, in
   * electronic ticks, as opposed as the time when ionization occurred.
   * The latter is not stored.
   * 
   * At the time of writing this documentation (LArSoft 6.4.0), SDPs are
   * computed in larg4::LArVoxelReadout.
   * The energy and track ID come directly from Geant4 simulation.
   * The position is the mid point of the Geant4 step that produced ionization.
   * The electrons are
   * 
   * 1. converted from that same energy (using a fundamental conversion factor
   *    stored in `larcoreobj/SimpleTypesAndConstants/PhysicalConstants.h`)
   * 2. applied recombination effect by larg4::IonizationAndScintillation::Reset()
   * 3. applied attenuation and diffusion in
   *    larg4::LArVoxelReadout::DriftIonizationElectrons()
   * 
   * The latter also assembles the sim::SDP objects to be stored into
   * sim::SimOpChannel.
   * 
   */
  struct SDP{
    
    /// Type of track ID (the value comes from Geant4)
    typedef int TrackID_t;
    
    /// Default constructor (sets "bogus" values)
    SDP();
    
#ifndef __GCCXML__
    
    /// Constructor: copies an SDP, and applies the specified offset to track ID
    SDP(SDP const& sdp, int offset);
    
    /// Constructor: sets all data members
    SDP(TrackID_t tid,
        float nPh,
        float e,
        float xpos,
        float ypos,
        float zpos)
    : trackID     (tid)
    , numPhotons  (nPh)
    , energy      (e)
    , x           (xpos)
    , y           (ypos)
    , z           (zpos)
    {}
    
#endif
    
    TrackID_t trackID;  ///< Geant4 supplied track ID
    float numPhotons;   ///< number of electrons at the readout for this track ID and time
    float energy;       ///< energy deposited by ionization
    float x;            ///< x position of ionization [cm]
    float y;            ///< y position of ionization [cm]
    float z;            ///< z position of ionization [cm]
  }; // struct SDP
  
  
  /// List of energy deposits at the same time (on this channel)
  typedef std::pair<unsigned short, std::vector<sim::SDP> > timePDclockSDP_t;
  
  /**
   * @brief Energy deposited on a readout channel by simulated tracks
   * 
   * This class stores the list of all energies deposited on a readout channel.
   * The number of electrons is stored as well.
   * 
   * The information is organized by time: it is divided by timePDclock ticks, and
   * each timePDclock tick where some energy was deposited appears in a separate entry,
   * while the quiet timePDclock ticks are omitted.
   * For each timePDclock, the information is stored as a list of energy deposits;
   * each deposit comes from a single Geant4 track and stores the location where
   * the ionization happened according to the simulation (see `sim::SDP` class).
   * 
   * Note that there can be multiple energy deposit records (that is `sim::SDP`)
   * for a single track in a single timePDclock tick.
   */
  class SimOpChannel
  {
  public:
    /// Type for timePDclock tick used in the internal representation 
    typedef timePDclockSDP_t::first_type storedTimePDclock_t;
  
    /// Type of list of energy deposits for each timePDclock with signal
    typedef std::vector<timePDclockSDP_t> timePDclockSDPs_t;
    
  private:
    int              iOpChannel; ///< readout channel where electrons are collected
    timePDclockSDPs_t      timePDclockSDPs; ///< list of energy deposits for each timePDclock with signal
    
    
  public:

    // Default constructor
    SimOpChannel();
    
#ifndef __GCCXML__
    /// Type for iTimePDclock tick used in the interface
    /// (different type than raw::TimePDclocktick_t! and from internal representation!
    ///  but same meaning!)
    typedef unsigned short timePDclock_t;
    
    /// Type of track ID (the value comes from Geant4)
    typedef SDP::TrackID_t TrackID_t;
    
    
    /// Constructor: immediately sets the channel number
    explicit SimOpChannel(int detNum);

    /**
     * @brief Add ionization electrons and energy to this channel
     * @param trackID ID of simulated track depositing this energy (from Geant4)
     * @param iTimePDclock timePDclock tick when this deposit was collected
     * @param numberElectrons electrons created at this point by this track
     * @param xyz coordinates of original location of ionization (3D array) [cm]
     * @param energy energy deposited at this point by this track [MeV]
     * 
     * The number of electrons can be fractional because of simulated
     * efficiency and physics effects.
     */
    void AddScintillationPhotons(TrackID_t trackID,
                                timePDclock_t timePDclock,
                                double numberPhotons,
                                double const* xyz,
                                double energy); 
    
    /// Returns the readout channel this object describes
    int Channel() const;
    
    /**
     * @brief Return all the recorded energy deposition within a time interval
     * @param startTimePDclock iTimePDclock tick opening the time window
     * @param endTimePDclock iTimePDclock tick closing the time window (included in the interval)
     * @return a collection of energy deposit information from all tracks
     * 
     * This method returns the energy deposited on this channel by each track
     * ID active in the specified iTimePDclock time interval.
     *
     * Each entry pertains a single track ID. For each entry, all energy
     * deposit information is merged into a single record. It includes:
     * * energy and number of electrons, as the integral in the time interval
     * * position, as average weighted by the number of electrons
     * * the ID of the track depositing this energy
     * 
     * Entries are sorted by track ID number.
     */
    std::vector<sim::SDP> TrackIDsAndPhotons(timePDclock_t startTimePDclock,
                                              timePDclock_t endTimePDclock) const;
    
    /**
     * @brief Returns all the deposited energy information as stored
     * @return all the deposited energy information as stored in the object
     * 
     * The returned list is organized in pairs. Each pair contains all
     * ionization information in a single iTimePDclock tick (collection of `sim::SDP`),
     * and the number of that tick. The information is sorted by increasing timePDclock
     * tick.
     * 
     * See the class description for the details of the ionization information
     * content.
     */
    timePDclockSDPs_t const& timePDclockSDPsMap() const;
    
    
    /// Returns the total number of ionization electrons on this channel in the specified timePDclock
    double Photons(timePDclock_t iTimePDclock) const;
    
    /// Returns the total energy on this channel in the specified iTimePDclock [MeV]
    double Energy(timePDclock_t iTimePDclock) const;

    /**
     * @brief Returns energies collected for each track within a time interval
     * @param startTimePDclock iTimePDclock tick opening the time window
     * @param endTimePDclock iTimePDclock tick closing the time window (included in the interval)
     * @return a collection of energy and fraction from each track in interval
     * @see TrackIDsAndEnergies()
     * 
     * This method returns the energy deposited on this channel by each track
     * ID active in the specified iTimePDclock time interval.
     *
     * Each entry pertains a single track ID. For each entry, all energy
     * deposit information is merged into a single record. It includes:
     * * energy of the track, as the integral in the time interval [MeV]
     * * energy fraction respect to the total (see below)
     * * the ID of the track depositing this energy
     * 
     * The energy fraction is the energy deposited by the track on this channel
     * in the specified time interval, divided by the total of the energy
     * deposited by all tracks on this channel in that same time interval.
     * 
     * Entries are sorted by track ID number.
     */
    std::vector<sim::TrackSDP> TrackSDPs(timePDclock_t startTimePDclock,
                                         timePDclock_t endTimePDclock) const;
    
    /// Comparison: sorts by channel ID
    bool operator<  (const SimOpChannel& other)     const;
    
    /// Comparison: true if SimOpChannels have the same channel ID
    bool operator== (const SimOpChannel& other)     const;
    
    /**
     * @brief Merges the deposits from another channel into this one
     * @param channel the sim::SimOpChannel holding information to be merged
     * @param offset track ID offset for the merge
     * @return range of the IDs of the added tracks
     * 
     * The information from the specified simulated channel is added to the
     * current one.
     * This is achieved by appending the energy deposit information (`sim::SDP`)
     * at each iTimePDclock tick from the merged channel to the list of existing energy
     * deposits for that iTimePDclock tick.
     * 
     * In addition, the track IDs of the merged channel are added an offset,
     * so that they can be distinguished from the existing ones.
     * This is useful when simulating tracks with multiple Geant4 runs. Geant4
     * will reuse track IDs on each run, and using the highest number of track
     * ID from one run as the offset for the next avoids track ID collisions.
     * Note however that this function does not perform any collision check, and
     * it is caller's duty to ensure that the offset is properly large.
     * The return value is a pair including the lowest and the largest track IDs
     * added to this channel, equivalent to the lowest and the highest track IDs
     * present in the merged channel, both augmented by the applied offset.
     * 
     * The channel number of the merged channel is ignored.
     */
    std::pair<TrackID_t,TrackID_t> MergeSimOpChannel
      (const SimOpChannel& channel, int offset);
    
    
    //@{
    /**
     * @brief Dumps the full content of the SimOpChannel into a stream
     * @tparam Stream an ostream-like stream object
     * @param out the stream to send the information into
     * @param indent indentation of the lines (default: none)
     * @param indent_first indentation for the first line (default: as indent)
     */
    template <typename Stream>
    void Dump(Stream&& out, std::string indent, std::string first_indent) const;
    
    template <typename Stream>
    void Dump(Stream&& out, std::string indent = "") const
      { Dump(std::forward<Stream>(out), indent, indent); }
    //@}
    
    
  private:
    /// Comparison functor, sorts by increasing timePDclocktick value
    struct CompareByTimePDclock;
    
    /// Return the iterator to the first timePDclockSDP not earlier than timePDclock
    timePDclockSDPs_t::iterator findClosestTimePDclockSDP(storedTimePDclock_t timePDclock);
    
    /// Return the (constant) iterator to the first timePDclockSDP not earlier than timePDclock
    timePDclockSDPs_t::const_iterator findClosestTimePDclockSDP
      (storedTimePDclock_t timePDclock) const;
    /// @}

#endif

  };

} // namespace sim

#ifndef __GCCXML__

inline bool                                sim::SimOpChannel::operator<  (const sim::SimOpChannel& other) const { return iOpChannel < other.Channel(); }
inline bool                                sim::SimOpChannel::operator== (const sim::SimOpChannel& other) const { return iOpChannel == other.Channel(); }
inline                                     sim::SimOpChannel::timePDclockSDPs_t const& sim::SimOpChannel::timePDclockSDPsMap()                             const { return timePDclockSDPs; }
inline int                                 sim::SimOpChannel::Channel()                                 const { return iOpChannel; }


// -----------------------------------------------------------------------------
// ---  template implementation
// ---
template <class Stream>
void sim::SimOpChannel::Dump
  (Stream&& out, std::string indent, std::string first_indent) const
{
  out << first_indent << "channel #" << Channel() << " read " << timePDclockSDPs.size()
    << " timePDclocks:\n";
  double channel_energy = 0., channel_photons = 0.;
  for (const auto& timePDclockinfo: timePDclockSDPs) {
    auto const iTimePDclock = timePDclockinfo.first;
    out << indent << "  timePDclock #" << iTimePDclock
      << " with " << timePDclockinfo.second.size() << " SDPs\n";
    double timePDclock_energy = 0., timePDclock_photons = 0.;
    for (const sim::SDP& sdp: timePDclockinfo.second) {
      out << indent
        << "    (" << sdp.x << ", " << sdp.y << ", " << sdp.z << ") "
        << sdp.numPhotons << " photons, " << sdp.energy << "MeV  (trkID="
        << sdp.trackID << ")\n";
      timePDclock_energy += sdp.energy;
      timePDclock_photons += sdp.numPhotons;
    } // for SDPs
    out << indent << "    => timePDclock #" << iTimePDclock << " CH #" << Channel()
      << " collected " << timePDclock_energy << " MeV and " 
      << timePDclock_photons <<" photons. \n";
    channel_energy += timePDclock_energy;
    channel_photons += timePDclock_photons;
  } // for timePDclocks
  out << indent << "  => channel #" << Channel() << " collected "
    << channel_photons << " photons and "<< channel_energy << " MeV.\n" ;
} // sim::SimOpChannel::Dump<>()

#endif

#endif // LARSIMOBJ_SIMULATION_SIMCHANNEL_H

////////////////////////////////////////////////////////////////////////
