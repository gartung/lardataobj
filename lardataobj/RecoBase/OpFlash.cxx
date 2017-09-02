////////////////////////////////////////////////////////////////////////
//
// \brief Definition of OpFlash reconstruction object
//
// \author bjpjones@mit.edu
//         cschiu@mit.edu
//
////////////////////////////////////////////////////////////////////////

#include "lardataobj/RecoBase/OpFlash.h"

#include <cstddef> // std::size_t

namespace recob{

  //----------------------------------------------------------------------
  OpFlash::OpFlash()  
    : fTime(            0.      )
  {
    
  }

  //----------------------------------------------------------------------
  OpFlash::OpFlash(double time, double timewidth, double abstime, unsigned int frame,
		   std::vector<double> PEperOpDet, 
		   bool InBeamFrame, int onBeamTime, double FastToTotal,
		   double yCenter, double yWidth, 
		   double zCenter, double zWidth,
		   std::vector<double> WireCenters,
		   std::vector<double> WireWidths)
  {
    for (unsigned int i = 0; i < PEperOpDet.size(); ++i)
      fPEperOpDet.push_back(PEperOpDet[i]);
    fFrame       = frame;
    fAbsTime     = abstime;
    fTimeWidth   = timewidth;
    fTime        = time;
    fYCenter     = yCenter;
    fYWidth      = yWidth;
    fZCenter     = zCenter;
    fZWidth      = zWidth;
    fWireWidths  = WireWidths;
    fWireCenters = WireCenters;
    fInBeamFrame = InBeamFrame;
    fFastToTotal = FastToTotal;
    fOnBeamTime  = onBeamTime;
  }

  //----------------------------------------------------------------------
  bool operator < (const OpFlash & a, const OpFlash & b)
  {
    return a.Time() < b.Time();
  }

  //----------------------------------------------------------------------
  double OpFlash::TotalPE() const
  {
    double theTotalPE=0;
    for(size_t i=0; i!=fPEperOpDet.size(); ++i)
      theTotalPE+=fPEperOpDet.at(i);
    return theTotalPE;
  }
  


}
