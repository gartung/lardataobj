////////////////////////////////////////////////////////////////////////
//
// ExternalTrigger class
//
// brebel@fnal.gov
//
////////////////////////////////////////////////////////////////////////

#include "lardataobj/RawData/ExternalTrigger.h"
#include <string>
#include <iostream>

namespace raw{

  //----------------------------------------------------------------------
  ExternalTrigger::ExternalTrigger() : 
    fTrigID(0),fTrigTime(0)
  {

  }

  //----------------------------------------------------------------------
  ExternalTrigger::ExternalTrigger(unsigned int trigid, TriggerTimeStamp_t trigtime) 
    : fTrigID(trigid)
    , fTrigTime(trigtime)
  {

  }


}
////////////////////////////////////////////////////////////////////////

