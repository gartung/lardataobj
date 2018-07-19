#ifndef PARTICLEID_VARIABLETYPEENUMS_H
#define PARTICLEID_VARIABLETYPEENUMS_H

namespace anab{

  enum kVariableType{
    kGOF,
    kLikelihood,
    kLogL,
    kScore,
    kPIDA,
    kdEdxtruncmean,
    kdQdxtruncmean,
    kTrackLength,
    kEdeposited,
    kEbyRange,
    kNotSet
  };

  enum kTrackDir{
    kForward,
    kBackward,
    kNoDirection
  };

}

#endif
