#include "lardataobj/Simulation/EnergyDeposition.h"

namespace sim {

  //----------------------------------------------------------------------------
  // Constructors; take care of any initializations.
  EnergyDeposition::EnergyDeposition() 
    : fDepositedEnergy(0.), fNumElectrons(0), fNumPhotons(0)
  {}
  

  EnergyDeposition::EnergyDeposition(double energy, int electrons, int photons) 
    : fDepositedEnergy(energy), fNumElectrons(electrons), fNumPhotons(photons)
  {}

  //----------------------------------------------------------------------------
  // Destructor.
  EnergyDeposition::~EnergyDeposition() {}

} // namespace sim
