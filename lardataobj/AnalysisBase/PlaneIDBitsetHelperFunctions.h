////////////////////////////////////////////////////////////////////////
// \version $Id:
//
// \brief Experiment-agnostic helper functions to translate bitset planeIDs used in anab::ParticleID into something more user friendly
//
// The convention to be used is: from left to right in the planeID bitset - collection plane, induction plane 1, induction plane 2, induction plane 3, induction plane 4
// So, for example, 10000 means collection plane only. 10100 means collection plane and second induction plane.
//
// \author kduff@fnal.gov
////////////////////////////////////////////////////////////////////////


#include <bitset>

namespace particleid{

  /// Returns true if collection plane bit is 1
  inline bool hasCollectionPlane(std::bitset<5> planeid){
    if (planeid[4]==1) return true;
    else return false;
  }

  /// Returns true if first induction plane bit is 1
  inline bool hasInductionPlane1(std::bitset<5> planeid){
    if (planeid[3]==1) return true;
    else return false;
  }

  /// Returns true if second induction plane bit is 1
  inline bool hasInductionPlane2(std::bitset<5> planeid){
    if (planeid[2]==1) return true;
    else return false;
  }

  /// Returns true if third induction plane bit is 1
  inline bool hasInductionPlane3(std::bitset<5> planeid){
    if (planeid[1]==1) return true;
    else return false;
  }

  /// Returns true if fourth induction plane bit is 1
  inline bool hasInductionPlane4(std::bitset<5> planeid){
    if (planeid[0]==1) return true;
    else return false;
  }

  /// \brief Returns true if more than one plane bits are 1, indicating that more than one plane is used
  inline bool isMultiPlane(std::bitset<5> planeid){
    if (planeid[0]+planeid[1]+planeid[2]+planeid[3]+planeid[4]>1) return true;
    else return false;
  }

}
