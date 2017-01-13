#include "FittedTrack.h"

using namespace recob;

SVector5 FittedTrack::VertexParametersLocal5D(const TVector3& surfpos,const TVector3& surfdir) const {
  SVector5 result;
  Global6DToLocal5DParameters(this->VertexParametersGlobal6D(), this->Vertex(), this->VertexDirection(), result);
  return result;
}

SVector5 FittedTrack::EndParametersLocal5D(const TVector3& surfpos,const TVector3& surfdir) const {
  SVector5 result;
  Global6DToLocal5DParameters(this->EndParametersGlobal6D(), this->End(), this->EndDirection(), result);
  return result;
}

SVector6 FittedTrack::VertexParametersGlobal6D() const {
  SVector6 result;
  result[0] = Vertex()[0];
  result[1] = Vertex()[1];
  result[2] = Vertex()[2];
  result[3] = VertexDirection()[0];
  result[4] = VertexDirection()[1];
  result[5] = VertexDirection()[2];
  return result;
}

SVector6 FittedTrack::EndParametersGlobal6D() const {
  SVector6 result;
  result[0] = End()[0];
  result[1] = End()[1];
  result[2] = End()[2];
  result[3] = EndDirection()[0];
  result[4] = EndDirection()[1];
  result[5] = EndDirection()[2];
  return result;
}

SMatrixSym66 FittedTrack::VertexCovarianceGlobal6D() const {
  SMatrix65 j;
  Local5DToGlobal6DJacobian(this->VertexDirection()*this->track().VertexMomentum(),this->VertexDirection(),j);
  return ROOT::Math::Similarity(j,this->VertexCovariance());
}

SMatrixSym66 FittedTrack::EndCovarianceGlobal6D() const {
  SMatrix65 j;
  Local5DToGlobal6DJacobian(this->EndDirection()*this->track().EndMomentum(),this->EndDirection(),j);
  return ROOT::Math::Similarity(j,this->EndCovariance());
}

void FittedTrack::Local5DToGlobal6DParameters(const SVector5& par5d, const TVector3& surfpos,const TVector3& surfdir, SVector6& par6d) const {
  const double theta = atan2(surfdir.X(), std::hypot(surfdir.Y(), surfdir.Z()));
  const double phi = atan2(-surfdir.Y(), surfdir.Z());
  const double sintheta = std::sin(theta);
  const double costheta = std::cos(theta);
  const double sinphi = std::sin(phi);
  const double cosphi = std::cos(phi);
  par6d[0] = surfpos.X() + par5d[0]*costheta;
  par6d[1] = surfpos.Y() + par5d[0]*sintheta*sinphi + par5d[1]*cosphi;
  par6d[2] = surfpos.Z() - par5d[0]*sintheta*cosphi + par5d[1]*sinphi;
  par6d[3] = (par5d[2]*costheta + 1.*sintheta)/(par5d[4]*std::sqrt(1. + par5d[2]*par5d[2] + par5d[3]*par5d[3]));
  par6d[4] = (par5d[2]*sintheta*sinphi + par5d[3]*cosphi - costheta*sinphi)/(par5d[4]*std::sqrt(1. + par5d[2]*par5d[2] + par5d[3]*par5d[3]));
  par6d[5] = (-par5d[2]*sintheta*cosphi + par5d[3]*sinphi + costheta*cosphi)/(par5d[4]*std::sqrt(1. + par5d[2]*par5d[2] + par5d[3]*par5d[3]));
}

void FittedTrack::Global6DToLocal5DParameters(const SVector6& par6d, const TVector3& surfpos,const TVector3& surfdir, SVector5& par5d) const {
  const double theta = atan2(surfdir.X(), std::hypot(surfdir.Y(), surfdir.Z()));
  const double phi = atan2(-surfdir.Y(), surfdir.Z());
  const double sintheta = std::sin(theta);
  const double costheta = std::cos(theta);
  const double sinphi = std::sin(phi);
  const double cosphi = std::cos(phi);
  const double pu = par6d[3]*costheta + par6d[4]*sintheta*sinphi - par6d[5]*sintheta*cosphi;
  const double pv = par6d[4]*cosphi + par6d[5]*sinphi;
  const double pw = par6d[3]*sintheta - par6d[4]*costheta*sinphi + par6d[5]*costheta*cosphi;
  const double pval = sqrt(par6d[3]*par6d[3]+par6d[4]*par6d[4]+par6d[5]*par6d[5]);
  par5d[0] = (par6d[0]-surfpos.X())*costheta + (par6d[1]-surfpos.Y())*sintheta*sinphi - (par6d[2]-surfpos.Z())*sintheta*cosphi;
  par5d[1] = (par6d[1]-surfpos.Y())*cosphi + (par6d[2]-surfpos.Z())*sinphi;
  par5d[2] = pu/pw;
  par5d[3] = pv/pw;
  par5d[4] = (pval>0 ? 1./pval : 1.);
}

void FittedTrack::Local5DToGlobal6DJacobian(const TVector3& p, const TVector3& surfdir, SMatrix65& j) const {
  const double theta = atan2(surfdir.X(), std::hypot(surfdir.Y(), surfdir.Z()));
  const double phi = atan2(-surfdir.Y(), surfdir.Z());
  const double sintheta = std::sin(theta);
  const double costheta = std::cos(theta);
  const double sinphi = std::sin(phi);
  const double cosphi = std::cos(phi);
  const double pu = p.X()*costheta + p.Y()*sintheta*sinphi - p.Z()*sintheta*cosphi;
  const double pv = p.Y()*cosphi + p.Z()*sinphi;
  const double pw = p.X()*sintheta - p.Y()*costheta*sinphi + p.Z()*costheta*cosphi;
  //local parameters 2,3,4
  const double l2 = pu/pw;
  const double l3 = pv/pw;
  const double p2 = p.X()*p.X() + p.Y()*p.Y() + p.Z()*p.Z();
  const double l4 = (p2>0 ? 1./sqrt(p2) : 1.);
  const double den23 = l4+(l2*l2+l3*l3+1.)*sqrt(l2*l2+l3*l3+1.);
  const double den4 = l4*l4*sqrt(l2*l2+l3*l3+1.);
  j(0,0) = costheta;
  j(0,1) = 0.;
  j(0,2) = 0.;
  j(0,3) = 0.;
  j(0,4) = 0.;
  //
  j(1,0) = sintheta*sinphi;
  j(1,1) = cosphi;
  j(1,2) = 0.;
  j(1,3) = 0.;
  j(1,4) = 0.;
  //
  j(2,0) = -sintheta*cosphi;
  j(2,1) = sinphi;
  j(2,2) = 0.;
  j(2,3) = 0.;
  j(2,4) = 0.;
  //
  j(3,0) = 0.;
  j(3,1) = 0.;
  j(3,2) = (costheta*(l3*l3+1.) - sintheta*l2)/den23;
  j(3,3) = -l3*(l2*costheta + sintheta)/den23;
  j(3,4) = -(l2*costheta + sintheta)/den4;
  //
  j(4,0) = 0.;
  j(4,1) = 0.;
  j(4,2) = (costheta*sinphi*l2 - cosphi*l2*l3 + sintheta*sinphi*(l3*l3+1.))/den23;
  j(4,3) = (sinphi*l3*(costheta-sintheta*l2) + cosphi*(l2*l2+1.))/den23;
  j(4,4) = (costheta*sinphi - cosphi*l3 - sintheta*sinphi*l2)/den4;
  //
  j(5,0) = 0.;
  j(5,1) = 0.;
  j(5,2) = -(costheta*cosphi*l2 + cosphi*sintheta*l3*l3 + cosphi*sintheta + sinphi*l2*l3)/den23;
  j(5,3) = (-costheta*cosphi*l3 + cosphi*sintheta*l2*l3 + sinphi*l2*l2 + sinphi)/den23;
  j(5,4) = (-costheta*cosphi + cosphi*sintheta*l2 - sinphi*l3)/den4;
  //
}

void FittedTrack::Global6DToLocal5DJacobian(const TVector3& p, const TVector3& surfdir, SMatrix56& j) const {
  const double theta = atan2(surfdir.X(), std::hypot(surfdir.Y(), surfdir.Z()));
  const double phi = atan2(-surfdir.Y(), surfdir.Z());
  const double sintheta = std::sin(theta);
  const double costheta = std::cos(theta);
  const double sinphi = std::sin(phi);
  const double cosphi = std::cos(phi);
  const double den23 = (costheta*(cosphi*p.Z() - sinphi*p.Y()) + sintheta*p.X())*(costheta*(cosphi*p.Z() - sinphi*p.Y()) + sintheta*p.X());
  const double den4 = sqrt(p.X()*p.X()+p.Y()*p.Y()+p.Z()*p.Z())*(p.X()*p.X()+p.Y()*p.Y()+p.Z()*p.Z());
  //
  j(0,0) = costheta;
  j(0,1) = sintheta*sinphi ;
  j(0,2) = sintheta*cosphi;
  j(0,3) = 0.;
  j(0,4) = 0.;
  j(0,5) = 0.;
  //
  j(1,0) = 0.;
  j(1,1) = cosphi;
  j(1,2) = sinphi;
  j(1,3) = 0.;
  j(1,4) = 0.;
  j(1,5) = 0.;
  //
  j(2,0) = 0.;
  j(2,1) = 0.;
  j(2,2) = 0.;
  j(2,3) = ((costheta*costheta + sintheta*sintheta)*(cosphi*p.Z() - sinphi*p.Y()))/den23;
  j(2,4) = (sinphi*p.X()*(costheta*costheta + sintheta*sintheta))/den23;
  j(2,5) = -(cosphi*p.X()*(costheta*costheta + sintheta*sintheta))/den23;
  //
  j(3,0) = 0.;
  j(3,1) = 0.;
  j(3,2) = 0.;
  j(3,3) = -(sintheta*(cosphi*p.Y() + sinphi*p.Z()))/den23;
  j(3,4) = (costheta*p.Z()*(cosphi*cosphi + sinphi*sinphi) + cosphi*sintheta*p.X())/den23;
  j(3,5) = (-costheta*cosphi*cosphi*p.Y() - costheta*sinphi*sinphi*p.Y() + sintheta*sinphi*p.X())/den23;
  //
  j(4,0) = 0.;
  j(4,1) = 0.;
  j(4,2) = 0.;
  j(4,3) = -p.X()/den4;
  j(4,4) = -p.Y()/den4;
  j(4,5) = -p.Z()/den4;
}

  // formulas
  // g0 = X0 + l0*costheta;
  // g1 = Y0 + l0*sintheta*sinphi + l1*cosphi;
  // g2 = Z0 - l0*sintheta*cosphi + l1*sinphi;
  // g3 = (l2*costheta + 1.*sintheta)/(l4*std::sqrt(1. + l2*l2 + l3*l3));
  // g4 = (l2*sintheta*sinphi + l3*cosphi - costheta*sinphi)/(l4*std::sqrt(1. + l2*l2 + l3*l3));
  // g5 = (-l2*sintheta*cosphi + l3*sinphi + costheta*cosphi)/(l4*std::sqrt(1. + l2*l2 + l3*l3));

  // par5d[0] = (par6d[0]-surfpos.X())*costheta + (par6d[1]-surfpos.Y())*sintheta*sinphi - (par6d[2]-surfpos.Z())*sintheta*cosphi;
  // par5d[1] = (par6d[1]-surfpos.Y())*cosphi + (par6d[2]-surfpos.Z())*sinphi;
  // par5d[2] = (par6d[3]*costheta + par6d[4]*sintheta*sinphi - par6d[5]*sintheta*cosphi)/(par6d[3]*sintheta - par6d[4]*costheta*sinphi + par6d[5]*costheta*cosphi);
  // par5d[3] = (par6d[4]*cosphi + par6d[5]*sinphi)/(par6d[3]*sintheta - par6d[4]*costheta*sinphi + par6d[5]*costheta*cosphi);
  // par5d[4] = 1./sqrt(par6d[3]*par6d[3]+par6d[4]*par6d[4]+par6d[5]*par6d[5]);  
