////////////////////////////////////////////////////////////////////////////
// \version
//
// \brief Definition of data product to hold ParticleID information
//
// \author brebel@fnal.gov, tjyang@fnal.gov
//
////////////////////////////////////////////////////////////////////////////
#ifndef ANAB_PARTICLEID_H
#define ANAB_PARTICLEID_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <bitset>
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "lardataobj/AnalysisBase/ParticleID_VariableTypeEnums.h"

namespace anab {

struct sParticleIDAlgScores { ///< determined particle ID
  std::string fAlgName; ///< Algorithm name (to be defined by experiment). Set to "AlgNameNotSet" by default.
  kVariableType fVariableType; ///< Variable type enum: defined in ParticleID_VariableTypeEnums.h. Set to kNotSet by default.
  kTrackDir fTrackDir; ///< Track direction enum: defined in ParticleID_VariableTypeEnums.h. Set to kNoDirection by default.
  int fNdf; ///< Number of degrees of freedom used by algorithm, if applicable. Set to -9999 by default.
  int fAssumedPdg; ///< PDG of particle hypothesis assumed by algorithm, if applicable. Set to 0 by default.
  float fValue; ///< Result of Particle ID algorithm/test
  std::bitset<5> fPlaneID; ///< Bitset for PlaneID used by algorithm, allowing for multiple planes and up to 5 total planes. Set to "00000" by default. Convention for bitset and helper functions defined in PlaneIDBitsetHelperFunctions.h

  sParticleIDAlgScores(){
  fAlgName = "AlgNameNotSet";
  fVariableType = kNotSet;
  fTrackDir = kNoDirection;
  fAssumedPdg = 0;
  fNdf = -9999;
  fValue = -9999.;
  // fPlaneID will use default constructor: sets all values to 0
  }
};

  class ParticleID{
  public:

    ParticleID();

    int    fPdg;             ///< determined particle ID
    int    fNdf;             ///< ndf for chi2 test
    double fMinChi2;         ///< Minimum reduced chi2
    double fDeltaChi2;       ///< difference between two lowest reduced chi2's
    double fChi2Proton;      ///< reduced chi2 using proton template
    double fChi2Kaon;        ///< reduced chi2 using kaon template
    double fChi2Pion;        ///< reduced chi2 using pion template
    double fChi2Muon;        ///< reduced chi2 using muon template
    double fMissingE;        ///< missing energy from dead wires for contained particle
    double fMissingEavg;     ///< missing energy from dead wires using average dEdx
    double fPIDA;            ///< PID developed by Bruce Baller
    geo::PlaneID fPlaneID;
    std::vector<sParticleIDAlgScores> fParticleIDAlgScores; ///< Vector of structs to hold outputs from generic PID algorithms

#ifndef __GCCXML__
  public:

    ParticleID(int Pdg,
	       int Ndf,
	       double MinChi2,
	       double DeltaChi2,
	       double Chi2Proton,
	       double Chi2Kaon,
	       double Chi2Pion,
	       double Chi2Muon,
	       double MissingE,
	       double MissingEavg,
	       double PIDA,
	       geo::PlaneID planeID);

    ParticleID(std::vector<anab::sParticleIDAlgScores> &ParticleIDAlgScores);


    friend std::ostream& operator << (std::ostream &o, ParticleID const& a);

    const int&    Pdg()         const;
    const int&    Ndf()         const;
    const double& MinChi2()     const;
    const double& DeltaChi2()   const;
    const double& Chi2Proton()  const;
    const double& Chi2Kaon()    const;
    const double& Chi2Pion()    const;
    const double& Chi2Muon()    const;
    const double& MissingE()    const;
    const double& MissingEavg() const;
    const double& PIDA()        const;
    const geo::PlaneID& PlaneID() const;
    const std::vector<anab::sParticleIDAlgScores> ParticleIDAlgScores() const;

#endif
  };

}

#ifndef __GCCXML__

inline const int&    anab::ParticleID::Pdg()         const { return fPdg;         }
inline const int&    anab::ParticleID::Ndf()         const { return fNdf;         }
inline const double& anab::ParticleID::MinChi2()     const { return fMinChi2;     }
inline const double& anab::ParticleID::DeltaChi2()   const { return fDeltaChi2;   }
inline const double& anab::ParticleID::Chi2Proton()  const { return fChi2Proton;  }
inline const double& anab::ParticleID::Chi2Kaon()    const { return fChi2Kaon;    }
inline const double& anab::ParticleID::Chi2Pion()    const { return fChi2Pion;    }
inline const double& anab::ParticleID::Chi2Muon()    const { return fChi2Muon;    }
inline const double& anab::ParticleID::MissingE()    const { return fMissingE;    }
inline const double& anab::ParticleID::MissingEavg() const { return fMissingEavg; }
inline const double& anab::ParticleID::PIDA()        const { return fPIDA; }
inline const geo::PlaneID& anab::ParticleID::PlaneID() const { return fPlaneID; }
inline const std::vector<anab::sParticleIDAlgScores> anab::ParticleID::ParticleIDAlgScores() const { return fParticleIDAlgScores; }
#endif

#endif //ANAB_PARTICLEID_H
