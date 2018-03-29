#ifndef Simulation_EnergyDeposition_h_
#define Simulation_EnergyDeposition_h_

namespace sim {

  class EnergyDeposition
  {
  public:
    // Standard constructor and destructor.
    EnergyDeposition();
    virtual ~EnergyDeposition();

  private:
    // deposited energy per event
    double fDepositedEnergy;

    // number of ionization electrons per event
    int fNumElectrons;

    // number of scointillation photons per event
    int fNumPhotons;

#ifndef __GCCXML__
  public:
    EnergyDeposition(double energy, int electrons, int photons);

    double DepositedEnergy() const;

    int NumElectrons() const;

    int NumPhotons() const;
    
#endif
  };

} // namespace sim

#ifndef __GCCXML__

inline double sim::EnergyDeposition::DepositedEnergy() const 
{ return fDepositedEnergy; }

inline int sim::EnergyDeposition::NumElectrons() const 
{ return fNumElectrons; }

inline int sim::EnergyDeposition::NumPhotons() const 
{ return fNumPhotons; }

#endif

#endif // Simulation_EnergyDeposition_h_

