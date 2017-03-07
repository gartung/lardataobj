/**
 * @file   SimEDep.h
 * @brief  object containing MC energy deposits
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
    int   trackID;
    int   pdgCode;

    SimEDep() {}

#ifndef __GCCXML__

    SimEDep(float x, float y, float z, double t,
	    float e,
	    int trk, int pdg)
    : time(t),
      xpos(x),
      ypos(y),
      zpos(z),
      energy(e),
      trackID(trk),
      pdgCode(pdg)
    {}

#endif

  };


} // namespace sim

#endif // LARDATAOBJ_SIMULATION_SIMEDEP_H

////////////////////////////////////////////////////////////////////////
