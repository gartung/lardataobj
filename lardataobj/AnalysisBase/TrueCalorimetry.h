////////////////////////////////////////////////////////////////////////////
// \version 
//
// \brief Definition of data product to hold truth information for TrueCalorimetry in MC
//
// Created by matching hits to IDEs so we can compare calorimetry performance to truth.
//
// \author jhugon@fnal.gov
//
////////////////////////////////////////////////////////////////////////////
#ifndef ANAB_TRUECALORIMETRY_H
#define ANAB_TRUECALORIMETRY_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <TVector3.h>

#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"

namespace anab {

  class TrueCalorimetry{
  public:
    
    TrueCalorimetry();

    double              fKineticEnergy;   ///< determined kinetic energy
    std::vector<double> fdEdx;            ///< dE/dx, should be same size as fResidualRange
    std::vector<double> fdQdx;            ///< dQ/dx
    std::vector<double> fResidualRange;   ///< range from end of track    
    std::vector<double> fDeadWireResR;    ///< dead wire residual range, collection plane
    double              fRange;           ///< total range of track
    std::vector<double> fTrkPitch;        ///< track pitch on collection plane
    std::vector<TVector3> fXYZ;           ///< coordinates of IDEs

    std::vector<UShort_t> fwire;           ///< wire id number for each calo hit
    std::vector<double> fdE;           ///< Energy deposited in TPC for each calo hit
    std::vector<double> fdQ;           ///< Charge collected by the wire for each calo hit

  private:
    geo::PlaneID        fPlaneID;

#ifndef __GCCXML__
  public:

    TrueCalorimetry(double KineticEnergy,
		std::vector<double> const& dEdx,
		std::vector<double> const& dQdx,
		std::vector<double> const& resRange,
		std::vector<double> const& deadwire,
		double Range,
		double TrkPitch,
		geo::PlaneID planeID,
        std::vector<UShort_t> wire,
        std::vector<double> dE,
        std::vector<double> dQ
        );

    TrueCalorimetry(double KineticEnergy,
		std::vector<double> const& dEdx,
		std::vector<double> const& dQdx,
		std::vector<double> const& resRange,
		std::vector<double> const& deadwire,
		double Range,
		std::vector<double> const& TrkPitch,
		geo::PlaneID planeID,
        std::vector<UShort_t> wire,
        std::vector<double> dE,
        std::vector<double> dQ
        );

    TrueCalorimetry(double KineticEnergy,
		std::vector<double> const& dEdx,
		std::vector<double> const& dQdx,
		std::vector<double> const& resRange,
		std::vector<double> const& deadwire,
		double Range,
		std::vector<double> const& TrkPitch,
		std::vector<TVector3> const& XYZ,
		geo::PlaneID planeID,
        std::vector<UShort_t> wire,
        std::vector<double> dE,
        std::vector<double> dQ
        );

    friend std::ostream& operator << (std::ostream &o, TrueCalorimetry const& a);

    const std::vector<double>& dEdx()          const; 
    const std::vector<double>& dQdx()          const; 
    const std::vector<double>& ResidualRange() const; 
    const std::vector<double>& DeadWireResRC() const; 
    const double&              KineticEnergy() const; 
    const double&              Range()         const; 
    double                     TrkPitchC()     const; 
    const std::vector<double>& TrkPitchVec()   const;
    const std::vector<TVector3>& XYZ()         const;
    const geo::PlaneID&        PlaneID()       const;
    const std::vector<UShort_t>& Wire()       const;
    const std::vector<double>& dE()   const;
    const std::vector<double>& dQ()   const;

#endif
    
  };

}

#ifndef __GCCXML__

inline const std::vector<double>& anab::TrueCalorimetry::dEdx()          const { return fdEdx;          }
inline const std::vector<double>& anab::TrueCalorimetry::dQdx()          const { return fdQdx;          }
inline const std::vector<double>& anab::TrueCalorimetry::ResidualRange() const { return fResidualRange; }
inline const std::vector<double>& anab::TrueCalorimetry::DeadWireResRC() const { return fDeadWireResR;  }
inline const double&              anab::TrueCalorimetry::KineticEnergy() const { return fKineticEnergy; } 
inline const double&              anab::TrueCalorimetry::Range()         const { return fRange;         }
inline const std::vector<double>& anab::TrueCalorimetry::TrkPitchVec()   const { return fTrkPitch;      }
inline double                     anab::TrueCalorimetry::TrkPitchC()     const 
{ 
  if (fTrkPitch.size()) 
    return fTrkPitch[0];
  else return 0;
}
inline const std::vector<TVector3>& anab::TrueCalorimetry::XYZ()         const { return fXYZ;      }
inline const geo::PlaneID& anab::TrueCalorimetry::PlaneID()              const { return fPlaneID; }
inline const std::vector<UShort_t>& anab::TrueCalorimetry::Wire()   const { return fwire;      }
inline const std::vector<double>& anab::TrueCalorimetry::dE()   const { return fdE;      }
inline const std::vector<double>& anab::TrueCalorimetry::dQ()   const { return fdQ;      }

#endif

#endif //ANAB_TRUECALORIMETRY_H
