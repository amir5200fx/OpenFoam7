#pragma once
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
inline
tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties()
	:
	dict_(dictionary::null),
	parcelTypeId_(dict_, -1),
	rhoMin_(dict_, 0.0),
	rho0_(dict_, 0.0),
	minParcelMass_(dict_, 0.0)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties
(
	const constantProperties& cp
)
	:
	dict_(cp.dict_),
	parcelTypeId_(cp.parcelTypeId_),
	rhoMin_(cp.rhoMin_),
	rho0_(cp.rho0_),
	minParcelMass_(cp.minParcelMass_)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties
(
	const dictionary& parentDict
)
	:
	dict_(parentDict.subOrEmptyDict("constantProperties")),
	parcelTypeId_(dict_, "parcelTypeId", -1),
	rhoMin_(dict_, "rhoMin", 1e-15),
	rho0_(dict_, "rho0"),
	minParcelMass_(dict_, "minParcelMass", 1e-15)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	active_(true),
	typeId_(-1),
	nParticle_(0),
	d_(0.0),
	dTarget_(0.0),
	U_(Zero),
	rho_(0.0),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const vector& position,
	const label celli
)
	:
	ParcelType(owner, position, celli),
	active_(true),
	typeId_(-1),
	nParticle_(0),
	d_(0.0),
	dTarget_(0.0),
	U_(Zero),
	rho_(0.0),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti,
	const label typeId,
	const scalar nParticle0,
	const scalar d0,
	const scalar dTarget0,
	const vector& U0,
	const constantProperties& constProps
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	active_(true),
	typeId_(typeId),
	nParticle_(nParticle0),
	d_(d0),
	dTarget_(dTarget0),
	U_(U0),
	rho_(constProps.rho0()),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::dictionary&
tnbLib::KinematicParcel<ParcelType>::constantProperties::dict() const
{
	return dict_;
}


template<class ParcelType>
inline tnbLib::label
tnbLib::KinematicParcel<ParcelType>::constantProperties::parcelTypeId() const
{
	return parcelTypeId_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::rhoMin() const
{
	return rhoMin_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::rho0() const
{
	return rho0_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::minParcelMass() const
{
	return minParcelMass_.value();
}


// * * * * * * * KinematicParcel Member Functions  * * * * * * * //

template<class ParcelType>
inline bool tnbLib::KinematicParcel<ParcelType>::active() const
{
	return active_;
}


template<class ParcelType>
inline tnbLib::label tnbLib::KinematicParcel<ParcelType>::typeId() const
{
	return typeId_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::nParticle() const
{
	return nParticle_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::d() const
{
	return d_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::dTarget() const
{
	return dTarget_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::U() const
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::rho() const
{
	return rho_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::age() const
{
	return age_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::tTurb() const
{
	return tTurb_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::UTurb() const
{
	return UTurb_;
}


template<class ParcelType>
inline bool& tnbLib::KinematicParcel<ParcelType>::active()
{
	return active_;
}


template<class ParcelType>
inline tnbLib::label& tnbLib::KinematicParcel<ParcelType>::typeId()
{
	return typeId_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::nParticle()
{
	return nParticle_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::d()
{
	return d_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::dTarget()
{
	return dTarget_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::U()
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::rho()
{
	return rho_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::age()
{
	return age_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::tTurb()
{
	return tTurb_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::UTurb()
{
	return UTurb_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::massCell
(
	const trackingData& td
) const
{
	return td.rhoc()*this->mesh().cellVolumes()[this->cell()];
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::mass() const
{
	return rho_ * volume();
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::momentOfInertia() const
{
	return 0.1*mass()*sqr(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::volume() const
{
	return volume(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::volume(const scalar d)
{
	return pi / 6.0*pow3(d);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaP() const
{
	return areaP(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaP(const scalar d)
{
	return 0.25*areaS(d);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaS() const
{
	return areaS(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaS(const scalar d)
{
	return pi * d*d;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Re
(
	const trackingData& td
) const
{
	return Re(td.rhoc(), U_, td.Uc(), d_, td.muc());
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Re
(
	const scalar rhoc,
	const vector& U,
	const vector& Uc,
	const scalar d,
	const scalar muc
)
{
	return rhoc * mag(U - Uc)*d / max(muc, rootVSmall);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::We
(
	const trackingData& td,
	const scalar sigma
) const
{
	return We(td.rhoc(), U_, td.Uc(), d_, sigma);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::We
(
	const scalar rhoc,
	const vector& U,
	const vector& Uc,
	const scalar d,
	const scalar sigma
)
{
	return rhoc * magSqr(U - Uc)*d / max(sigma, rootVSmall);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Eo
(
	const trackingData& td,
	const scalar sigma
) const
{
	return Eo(td.g(), rho_, td.rhoc(), U_, d_, sigma);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Eo
(
	const vector& g,
	const scalar rho,
	const scalar rhoc,
	const vector& U,
	const scalar d,
	const scalar sigma
)
{
	const vector dir = U / max(mag(U), rootVSmall);
	return mag(g & dir)*mag(rho - rhoc)*sqr(d) / max(sigma, rootVSmall);
}


// ************************************************************************* //