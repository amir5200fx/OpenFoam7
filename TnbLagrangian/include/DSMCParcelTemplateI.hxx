#pragma once
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::DSMCParcel<ParcelType>::constantProperties::constantProperties()
	:
	mass_(0),
	d_(0)
{}


template<class ParcelType>
inline tnbLib::DSMCParcel<ParcelType>::constantProperties::constantProperties
(
	const dictionary& dict
)
	:
	mass_(readScalar(dict.lookup("mass"))),
	d_(readScalar(dict.lookup("diameter"))),
	internalDegreesOfFreedom_
	(
		readInt(dict.lookup("internalDegreesOfFreedom"))
	),
	omega_(readScalar(dict.lookup("omega")))
{}


template<class ParcelType>
inline tnbLib::DSMCParcel<ParcelType>::DSMCParcel
(
	const polyMesh& mesh,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti,
	const vector& U,
	const scalar Ei,
	const label typeId
)
	:
	ParcelType(mesh, coordinates, celli, tetFacei, tetPti),
	U_(U),
	Ei_(Ei),
	typeId_(typeId)
{}


template<class ParcelType>
inline tnbLib::DSMCParcel<ParcelType>::DSMCParcel
(
	const polyMesh& mesh,
	const vector& position,
	const label celli,
	const vector& U,
	const scalar Ei,
	const label typeId
)
	:
	ParcelType(mesh, position, celli),
	U_(U),
	Ei_(Ei),
	typeId_(typeId)
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCParcel<ParcelType>::constantProperties::mass() const
{
	return mass_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCParcel<ParcelType>::constantProperties::d() const
{
	return d_;
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCParcel<ParcelType>::constantProperties::sigmaT() const
{
	return constant::mathematical::pi*d_*d_;
}


template<class ParcelType>
inline tnbLib::direction
tnbLib::DSMCParcel<ParcelType>::constantProperties::internalDegreesOfFreedom()
const
{
	return internalDegreesOfFreedom_;
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCParcel<ParcelType>::constantProperties::omega() const
{
	return omega_;
}


// * * * * * * * * * * DSMCParcel Member Functions  * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::label tnbLib::DSMCParcel<ParcelType>::typeId() const
{
	return typeId_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::DSMCParcel<ParcelType>::U() const
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCParcel<ParcelType>::Ei() const
{
	return Ei_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::DSMCParcel<ParcelType>::U()
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::DSMCParcel<ParcelType>::Ei()
{
	return Ei_;
}


// ************************************************************************* //