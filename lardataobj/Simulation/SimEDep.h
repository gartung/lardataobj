/**
 * @file   SimEDep.h
 * @brief  object containing MC energy deposits and electron/photon creation
 * @author wketchum@fnal.gov
 * 
 * This class uses only LArSoft libraries that are header only.
 */


#ifndef LARDATAOBJ_SIMULATION_SIMEDEP_H
#define LARDATAOBJ_SIMULATION_SIMEDEP_H

// C/C++ standard libraries
#include <string>
#include <vector>


namespace sim {

  struct SimEDep{
    double time; 
    float xpos;  
    float ypos;
    float zpos;

    float energy;

    //these elements should be removed when ionization/scintillation
    //code is decoupled from LArG4 geometry and/or can be handled in
    //different step
    int n_el;  //number electrons
    int n_ph;  //number photons

    //these elements should be removed once TPC/cryo location is decoupled
    // (used in DriftIonizationElectrons)
    int trackID;
    unsigned short int tpc;
    unsigned short int cryostat;

    SimEDep() {}

#ifndef __GCCXML__

    SimEDep(float x, float y, float z, double t,
	    float e, int ne, int np,
	    int trk, unsigned short int i_t, unsigned short int i_c)
    : time(t),
      xpos(x),
      ypos(y),
      zpos(z),
      energy(e),
      n_el(ne),
      n_ph(np),
      trackID(trk),
      tpc(i_t),
      cryostat(i_c)
    {}

#endif

  };


} // namespace sim

#endif // LARDATAOBJ_SIMULATION_SIMEDEP_H

////////////////////////////////////////////////////////////////////////
