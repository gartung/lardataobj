////////////////////////////////////////////////////////////////////////////
// \version 
//
// \brief Definition of data product to hold T0 information
//
// \author k.warburton@sheffield.ac.uk
//
////////////////////////////////////////////////////////////////////////////
#ifndef ANAB_T0_H
#define ANAB_T0_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <iomanip>

namespace anab {

  class T0{
  public:
    
    T0();
    
    double       fTime;              ///< Time in ns
    unsigned int fTriggerType;       ///< Type of trigger used. 0 - Muon Counters, 1 - Photon Detectors, 2 - Monte Carlo Truth
    int          fTriggerBits;       ///< An identifier for the Muon track / Flash / MCParticle used in matching.
    int          fID;                ///< Current size of T0 data product.
    double       fTriggerConfidence; ///< Confidence with which this T0 is known.

  public:

    T0(double Time, unsigned int TriggerType, int TriggerBits, int ID=-1, double TriggerConfidence=-1);

    friend std::ostream& operator << (std::ostream &o, T0 const& a);

    const double&          Time()              const; 
    const unsigned int&    TriggerType()       const;
    const int&             TriggerBits()       const;
    const int&             ID()                const;
    const double&          TriggerConfidence() const;
    
  };

}


inline const double&          anab::T0::Time()              const { return fTime;              }
inline const unsigned int&    anab::T0::TriggerType()       const { return fTriggerType;       }
inline const int&             anab::T0::TriggerBits()       const { return fTriggerBits;       }
inline const int&             anab::T0::ID()                const { return fID;                }
inline const double&          anab::T0::TriggerConfidence() const { return fTriggerConfidence; }


#endif //ANAB_T0
