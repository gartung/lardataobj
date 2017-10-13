////////////////////////////////////////////////////////////////////////
/// \file  SimEnergyDeposit.h
/// \brief contains information for a single step in the detector simulation
///
/// \author  Hans Wenzel and William Seligman
////////////////////////////////////////////////////////////////////////
//
// The detector simulation (presently LArG4, which invokes Geant4)
// propagates particles through the detector in intervals of "steps". 
// In Geant4, a step is normally defined by the smallest of the distance
// from the current position of the particle to the point where it
// enters a new volume boundary, the particle undergoes some "interesting"
// physics event, or the range of the particle due to its energy falls
// below a given limit.
//
// In LArG4, an additional limit is applied: We force the steps to be
// small (typically 1/10th the wire spacing in the planes of the TPC)
// so we can process the energy deposited by each step into
// electron clusters. 
//
// The SimEnergyDeposit class defines what Geant4 truth information for
// each step is passed to the ionization->sim::SimChannel conversion,
// and for the optical-photon->sim::SimPhoton conversion. 
// 
// William Seligman, Nevis Labs, 10/12/2017
//

#ifndef SimEnergyDeposit_h
#define SimEnergyDeposit_h

#include "TVector3.h"
#include "TLorentzVector.h"
#include "Math/GenVector/Cartesian3D.h" 
#include "Math/GenVector/PositionVector3D.h" 
#include "Math/GenVector/PxPyPzE4D.h" 
#include "Math/GenVector/LorentzVector.h" 

namespace sim
{
  class SimEnergyDeposit 
  {
  public:
    SimEnergyDeposit(int np = 0,
		     double e = 0,
		     double x = 0,
		     double y = 0,
		     double z = 0,
		     double t = 0,
		     int id = 0)
      : numPhotons(np)
      , edep(e)
      , xpos(x)
      , ypos(y)
      , zpos(z)
      , time(t)
      , trackID(id)
    {};

#ifndef __GCCXML__
    // Accessors, hidden from the ROOT dictionary generation.
    // Note that even if we store a value as float, we return
    // it as double so the user doesn't have to think about
    // precision issues. 

    int NumPhotons() const { return numPhotons; }
    double E() const { return edep; }
    double X() const { return xpos; }
    double Y() const { return ypos; }
    double Z() const { return zpos; }
    double T() const { return time; }
    int TrackID() const { return trackID; }

    // While it's clear how a SimEnergyDeposit will be created by its
    // constructor, it's not clear how users will want to access its
    // data. So give them as many different kinds of accessors as I
    // can think of.
    const TVector3 Position() const { return TVector3(xpos,ypos,zpos); }
    const TLorentzVector FourVector() const { return TLorentzVector(xpos,ypos,zpos,time); }

    using Point_t = ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>>;
    const Point_t Position3D() const { return {xpos,ypos,zpos}; }

    using Position4_t = ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double>>;
    const Position4_t Position4D() const { return {xpos,ypos,zpos,time}; }

#endif

  private:

    // There are roughly 7 digits of decimal precision in a float.
    // This will suffice for energy and position (the largest LAr TPC
    // presently comtemplated is on the order of 10^2 meters, the
    // position accuracy need be no better than 10^-4 meters). 
    // 
    // For time, it's possible for long-lived particles like neutrons
    // to deposit energy after billions of ns. Chances are time cuts
    // will take care of that, but let's make sure that any overlay studies
    // won't suffer due to lack of precision.

    int           numPhotons; // of scintillation photons
    float         edep;       // energy deposition (GeV)
    float         xpos;       // position (mm)
    float         ypos;
    float         zpos;
    double        time;       // (ns)
    int           trackID;    // track id
  };

} // namespace sim
#endif // SimEnergyDeposit_n
