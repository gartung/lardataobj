#ifndef FITTEDTRACK
#define FITTEDTRACK

#include "Track.h"

//fixme, maybe these should go somewhere else?
#include "Math/SMatrix.h"
typedef ROOT::Math::SMatrix<double,5,5,ROOT::Math::MatRepSym<double,5> > SMatrixSym55;
typedef ROOT::Math::SMatrix<double,6,6,ROOT::Math::MatRepSym<double,6> > SMatrixSym66;
typedef ROOT::Math::SMatrix<double,6,5> SMatrix65;
typedef ROOT::Math::SMatrix<double,5,6> SMatrix56;
typedef ROOT::Math::SVector<double,6> SVector6;
typedef ROOT::Math::SVector<double,5> SVector5;

namespace recob {
  
  class FittedTrack {

  public:

    FittedTrack() {}
    FittedTrack(Track track, int pId, float chi2, int ndof, SMatrixSym55 covVertex, SMatrixSym55 covEnd)
      :track_(track), pId_(pId), chi2_(chi2), ndof_(ndof), covVertex_(covVertex), covEnd_(covEnd) {}

    int ParticleId() const {return pId_;}
    float Chi2() const {return chi2_;}
    const Track& track() const {return track_;}
    int NumberOfDegreesOfFreedom() const { return ndof_;}
    float Chi2PerNdof() { return chi2_/float(ndof_);}
    
    size_t NumberTrajectoryPoints() const { return track_.NumberTrajectoryPoints(); }
    size_t NumberFitMomentum() const { return track_.NumberFitMomentum(); }
    double Length(size_t p=0) const { return track_.Length(p); }

    void TrajectoryAtPoint(unsigned int  p, TVector3& pos, TVector3& dir) const { return track_.TrajectoryAtPoint(p,pos,dir); }
    const TVector3& DirectionAtPoint(unsigned int p) const { return track_.DirectionAtPoint(p); }
    const TVector3& LocationAtPoint(unsigned int p) const { return track_.LocationAtPoint(p); }
    const TVector3& Vertex() const { return track_.Vertex(); }
    const TVector3& End() const { return track_.End(); }
    const TVector3& VertexDirection() const { return track_.VertexDirection(); }
    const TVector3& EndDirection() const { return track_.EndDirection(); }
    const SMatrixSym55& VertexCovariance() const { return covVertex_; }
    const SMatrixSym55& EndCovariance() const { return covEnd_; }

    SVector5 VertexParametersLocal5D(const TVector3& surfpos,const TVector3& surfdir) const;
    const SMatrixSym55& VertexCovarianceLocal5D() const { return covVertex_; }

    SVector5 EndParametersLocal5D(const TVector3& surfpos,const TVector3& surfdir) const;
    const SMatrixSym55& EndCovarianceLocal5D() const { return covEnd_; }
   
    SVector6 VertexParametersGlobal6D() const;
    SMatrixSym66 VertexCovarianceGlobal6D() const;

    SVector6 EndParametersGlobal6D() const;
    SMatrixSym66 EndCovarianceGlobal6D() const;

    void Global6DToLocal5DParameters(const SVector6& par6d, const TVector3& surfpos, const TVector3& surfdir, SVector5& par5d) const;
    void Local5DToGlobal6DParameters(const SVector5& par5d, const TVector3& surfpos, const TVector3& surfdir, SVector6& par6d) const;
    
    void Local5DToGlobal6DJacobian(const TVector3& p, const TVector3& surfdir, SMatrix65& j) const;
    void Global6DToLocal5DJacobian(const TVector3& p, const TVector3& surfdir, SMatrix56& j) const;
    
    double Theta() const { return track_.Theta(); }
    double Phi() const { return track_.Phi(); }
    double ZenithAngle() const { return track_.ZenithAngle(); }
    double AzimuthAngle() const { return track_.AzimuthAngle(); }

  private:
    Track track_;
    int pId_;
    float chi2_;
    int ndof_;
    SMatrixSym55 covVertex_;
    SMatrixSym55 covEnd_;
  };

}
#endif
