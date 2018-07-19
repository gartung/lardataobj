// MicroBooNE-specific helper functions to translate bitset planeIDs used in anab::ParticleID

#include <bitset>

namespace particleid{

  inline bool hasCollectionPlane(std::bitset<5> planeid){
    if (planeid[0]==1) return true;
    else return false;
  }

  inline bool hasInductionPlane1(std::bitset<5> planeid){
    if (planeid[1]==1) return true;
    else return false;
  }

  inline bool hasInductionPlane2(std::bitset<5> planeid){
    if (planeid[2]==1) return true;
    else return false;
  }

  inline bool hasInductionPlane3(std::bitset<5> planeid){
    if (planeid[3]==1) return true;
    else return false;
  }

  inline bool hasInductionPlane4(std::bitset<5> planeid){
    if (planeid[4]==1) return true;
    else return false;
  }

}
