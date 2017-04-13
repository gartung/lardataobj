////////////////////////////////////////////////////////////////////////
// \version $Id$
//
// \brief Definition of TrueCalorimetry analysis object
//
// \author jhugon@fnal.gov
////////////////////////////////////////////////////////////////////////

#include "lardataobj/AnalysisBase/TrueCalorimetry.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

namespace anab{

  //----------------------------------------------------------------------
  TrueCalorimetry::TrueCalorimetry() 
    : fKineticEnergy(0.)
    , fRange(0.)
  {
    fdEdx.clear();
    fdQdx.clear();
    fResidualRange.clear();
    fDeadWireResR.clear();
    fTrkPitch.clear();
    fXYZ.clear();
    fwire.clear();
    fdE.clear();
    fdQ.clear();
  }


 //----------------------------------------------------------------------
  TrueCalorimetry::TrueCalorimetry(double KineticEnergy,
			   std::vector<double> const& dEdx,
			   std::vector<double> const& dQdx,
			   std::vector<double> const& resRange,
			   std::vector<double> const& deadwire,
			   double Range,
			   double TrkPitch,
			   geo::PlaneID planeID,
               std::vector<UShort_t> wire,
               std::vector<double> dE,
               std::vector<double> dQ) 
  {
 
    fKineticEnergy = KineticEnergy;
    fRange = Range;
    for(size_t i=0; i!=dQdx.size(); ++i){
      fTrkPitch.push_back(TrkPitch);
      TVector3 v(-999,-999,-999);
      fXYZ.push_back(v);
    }
    if(dEdx.size() != resRange.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and residual range vectors "
						<< "have different sizes, this is a problem.\n";
    fdEdx.resize(dEdx.size());
    fdQdx.resize(dQdx.size());
    fResidualRange.resize(resRange.size());
    for(size_t i = 0; i < dEdx.size(); ++i){
      fdEdx[i]          = dEdx[i];
      fdQdx[i]          = dQdx[i];
      fResidualRange[i] = resRange[i];
    }
    
    fDeadWireResR.resize(deadwire.size());
    for(size_t i = 0; i<deadwire.size(); ++i){
      fDeadWireResR[i] = deadwire[i];
    }

    fPlaneID = planeID;

    if(dEdx.size() != wire.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and wire "
						<< "have different sizes, this is a problem.\n";
    fwire.resize(wire.size());
    for(size_t i = 0; i<wire.size(); ++i){
      fwire[i] = wire[i];
    }

    if(dEdx.size() != dE.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dE "
						<< "have different sizes, this is a problem.\n";
    fdE.resize(dE.size());
    for(size_t i = 0; i<dE.size(); ++i){
      fdE[i] = dE[i];
    }

    if(dEdx.size() != dQ.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dQ "
						<< "have different sizes, this is a problem.\n";
    fdQ.resize(dQ.size());
    for(size_t i = 0; i<dQ.size(); ++i){
      fdQ[i] = dQ[i];
    }
  }


  //----------------------------------------------------------------------
  TrueCalorimetry::TrueCalorimetry(double KineticEnergy,
			   std::vector<double> const& dEdx,
			   std::vector<double> const& dQdx,
			   std::vector<double> const& resRange,
			   std::vector<double> const& deadwire,
			   double Range,
			   std::vector<double> const& TrkPitch,
			   geo::PlaneID planeID,
               std::vector<UShort_t> wire,
               std::vector<double> dE,
               std::vector<double> dQ) 
  {
    
    fPlaneID = planeID;
    fKineticEnergy = KineticEnergy;
    fRange = Range;
    fTrkPitch = TrkPitch;
    if(dEdx.size() != resRange.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and residual range vectors "
						<< "have different sizes, this is a problem.\n";
    for(size_t i=0; i!=dQdx.size(); ++i){
      TVector3 v(-999,-999,-999);
      fXYZ.push_back(v);
    }
    fdEdx.resize(dEdx.size());
    fdQdx.resize(dQdx.size());
    fResidualRange.resize(resRange.size());
    for(size_t i = 0; i < dEdx.size(); ++i){
      fdEdx[i]          = dEdx[i];
      fdQdx[i]          = dQdx[i];
      fResidualRange[i] = resRange[i];
    }
    
    fDeadWireResR.resize(deadwire.size());
    for(size_t i = 0; i<deadwire.size(); ++i){
      fDeadWireResR[i] = deadwire[i];
    }

    if(dEdx.size() != wire.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and wire "
						<< "have different sizes, this is a problem.\n";
    fwire.resize(wire.size());
    for(size_t i = 0; i<wire.size(); ++i){
      fwire[i] = wire[i];
    }

    if(dEdx.size() != dE.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dE "
						<< "have different sizes, this is a problem.\n";
    fdE.resize(dE.size());
    for(size_t i = 0; i<dE.size(); ++i){
      fdE[i] = dE[i];
    }

    if(dEdx.size() != dQ.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dQ "
						<< "have different sizes, this is a problem.\n";
    fdQ.resize(dQ.size());
    for(size_t i = 0; i<dQ.size(); ++i){
      fdQ[i] = dQ[i];
    }
  }

  //----------------------------------------------------------------------
  TrueCalorimetry::TrueCalorimetry(double KineticEnergy,
			   std::vector<double> const& dEdx,
			   std::vector<double> const& dQdx,
			   std::vector<double> const& resRange,
			   std::vector<double> const& deadwire,
			   double Range,
			   std::vector<double> const& TrkPitch,
			   std::vector<TVector3> const& XYZ,
			   geo::PlaneID planeID,
               std::vector<UShort_t> wire,
               std::vector<double> dE,
               std::vector<double> dQ) 
  {
    
    fPlaneID = planeID;
    fKineticEnergy = KineticEnergy;
    fRange = Range;
    fTrkPitch = TrkPitch;
    if(dEdx.size() != resRange.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and residual range vectors "
						<< "have different sizes, this is a problem.\n";
    for(size_t i=0; i!=dQdx.size(); ++i){
      fXYZ.push_back(TVector3(-999,-999,-999));
    }
    fdEdx.resize(dEdx.size());
    fdQdx.resize(dQdx.size());
    fResidualRange.resize(resRange.size());
    fXYZ.resize(XYZ.size());
    for(size_t i = 0; i < dEdx.size(); ++i){
      fdEdx[i]          = dEdx[i];
      fdQdx[i]          = dQdx[i];
      fResidualRange[i] = resRange[i];
      fXYZ[i]           = XYZ[i];
    }
    
    fDeadWireResR.resize(deadwire.size());
    for(size_t i = 0; i<deadwire.size(); ++i){
      fDeadWireResR[i] = deadwire[i];
    }

    if(dEdx.size() != wire.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and wire "
						<< "have different sizes, this is a problem.\n";
    fwire.resize(wire.size());
    for(size_t i = 0; i<wire.size(); ++i){
      fwire[i] = wire[i];
    }

    if(dEdx.size() != dE.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dE "
						<< "have different sizes, this is a problem.\n";
    fdE.resize(dE.size());
    for(size_t i = 0; i<dE.size(); ++i){
      fdE[i] = dE[i];
    }

    if(dEdx.size() != dQ.size())
      throw cet::exception("anab::TrueCalorimetry") << "dE/dx and dQ "
						<< "have different sizes, this is a problem.\n";
    fdQ.resize(dQ.size());
    for(size_t i = 0; i<dQ.size(); ++i){
      fdQ[i] = dQ[i];
    }
  }

  //----------------------------------------------------------------------
  // ostream operator.  
  //
  std::ostream& operator<< (std::ostream & o, TrueCalorimetry const& a)
  {
    o << "True Calo\nKinetic Energy: " << a.fKineticEnergy 
      << "\n Range: "         << a.fRange << std::endl;
    
    for(size_t n = 0; n < a.fdEdx.size(); ++n)
      o << "dE/dx="           << a.fdEdx[n]
	<< " Residual range=" << a.fResidualRange[n] 
	<< " dQ/dx=" << a.fdQdx[n]
	<< " (x,y,z)=(" << a.fXYZ[n].X() << "," << a.fXYZ[n].Y() << "," << a.fXYZ[n].Z() << ")"
	<< " pitch=" << a.fTrkPitch[n]
	<< " planeID=(" << a.fPlaneID.Cryostat << "," << a.fPlaneID.TPC << "," << a.fPlaneID.Plane << ")"
	<< " wire=(" << a.fwire[n] << ")"
	<< " dE=(" << a.fdE[n] << ")"
	<< " dQ=(" << a.fdQ[n] << ")"
	<< std::endl;

    return o;
  }
  
}
