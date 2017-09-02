/// PMTTrigger.h
/// William Seligman <seligman@nevis.columbia.edu>
///
/// The information associated with a PMT trigger issued by a Front End Module (FEM).

#ifndef optdata_PMTTrigger_h
#define optdata_PMTTrigger_h

// LArSoft includes
#include "lardataobj/OpticalDetectorData/OpticalTypes.h"

// C++ includes
#include <functional> // so we can redefine less<> below
#include <limits>

namespace optdata {

  class PMTTrigger
  {
  public:

    // Simple constructor/destructor.
    PMTTrigger ( Optical_Category_t category = kUndefined, 
		 TimeSlice_t time = 0,
		 Frame_t frame = 0 )
      : fm_category(category)
      , fm_timeSlice(time)
      , fm_frame(frame)
    {};

    ~PMTTrigger() {};

    // Here we have getters and setters for the time information.


    Optical_Category_t Category() const { return fm_category; }

    // A time slice associated with the first bin in the channel
    // data. For example, the first bin of the ADC channel may refer
    // to clock value 8595824 (in some arbitrary units).
    TimeSlice_t TimeSlice() const { return fm_timeSlice; }
    void SetTimeSlice( TimeSlice_t t ) { fm_timeSlice = t; }

    // The frame number associated with the first frame in the channel.
    Frame_t Frame() const { return fm_frame; }
    void SetFrame( Frame_t f ) { fm_frame = f; }


  private:
    Optical_Category_t fm_category; // A channel category from Types.h
    TimeSlice_t fm_timeSlice;       // The time of the first slice in the channel data
    Frame_t fm_frame;               // The frame number corresponding to the above time
  };

  // In case we want to sort a collection of PMTTriggers (e.g.,
  // std::set<PMTTrigger>), here's the definition of the less-than
  // operator.
  bool operator<( const PMTTrigger& lhs, const PMTTrigger& rhs )
  {
    // Sort by channel, frame number, and time associated with the first bin.
    if ( 
	 lhs.Frame()           < rhs.Frame()          &&
	 lhs.TimeSlice()       < rhs.TimeSlice()      && 
	 lhs.Category()        < rhs.Category()         )
      return true;
    return false;
  }

} // namespace optdata

// For no extra charge, include how to sort PMTTrigger*, just in
// case we want (for example) a std::set<PMTTrigger*>.
namespace std {
  template <> 
  class less<optdata::PMTTrigger*>
  {
  public:
    bool operator()( const optdata::PMTTrigger* lhs, const optdata::PMTTrigger* rhs )
    {
      return (*lhs) < (*rhs);
    }
  };
} // std

#endif // optdata_PMTTrigger_h
