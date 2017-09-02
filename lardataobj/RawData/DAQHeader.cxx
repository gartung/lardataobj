////////////////////////////////////////////////////////////////////////
//
// DAQHeader class
//
// brebel@fnal.gov
//
////////////////////////////////////////////////////////////////////////

#include "lardataobj/RawData/DAQHeader.h"
#include <string>
#include <iostream>

namespace raw{

  //----------------------------------------------------------------------
  DAQHeader::DAQHeader() 
    : fStatus(0)
    , fFixed(0)
    , fFormat(0)
    , fSoftware(0)
    , fRun(0)
    , fSubRun(0)
    , fEvent(0)
    , fTime(0)
    , fSpare(0)
    , fNchan(0)
  {

  }

  //----------------------------------------------------------------------
  DAQHeader::DAQHeader(unsigned int status) 
    : fStatus(status)
    , fFixed(0)
    , fFormat(0)
    , fSoftware(0)
    , fRun(0)
    , fSubRun(0)
    , fEvent(0)
    , fTime(0)
    , fSpare(0)
    , fNchan(0)
  {

  }

  //----------------------------------------------------------------------
  DAQHeader::DAQHeader(unsigned int status,
		       int fixed,
		       unsigned short format,
		       unsigned short software,
		       unsigned short run,
		       unsigned short subrun,
		       unsigned short event,
		       time_t time,
		       short spare,
		       uint32_t nchan) 
    : fStatus(status)
    , fFixed(fixed)
    , fFormat(format)
    , fSoftware(software)
    , fRun(run)
    , fSubRun(subrun)
    , fEvent(event)
    , fTime(time)
    , fSpare(spare)
    , fNchan(nchan)
  { 
  
  }


  //----------------------------------------------------------------------
  DAQHeader::DAQHeader(unsigned int status,
		       int fixed,
		       unsigned short format,
		       unsigned short software,
		       unsigned short run,
		       unsigned short event,
		       time_t time,
		       short spare,
		       uint32_t nchan) 
    : fStatus(status)
    , fFixed(fixed)
    , fFormat(format)
    , fSoftware(software)
    , fRun(run)
    , fSubRun(0)
    , fEvent(event)
    , fTime(time)
    , fSpare(spare)
    , fNchan(nchan)
  { 
  
  }

}
////////////////////////////////////////////////////////////////////////

