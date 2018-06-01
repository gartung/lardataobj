#ifndef PARTICLEID_VARIABLETYPEENUMS_H 
#define PARTICLEID_VARIABLETYPEENUMS_H 

namespace anab{

  enum kVariableType{
    kGOF,
    kLikelihood,
    kLikelihood_fwd,
    kLikelihood_bwd,
    kLogL,
    kLogL_fwd,
    kLogL_bwd,
    kScore,
    kPIDA,
    kdEdxtruncmean,
    kdQdxtruncmean,
    kTrackLength,
    kEdeposited,
    kEbyRange,
    kNotSet
  };

}

#endif
