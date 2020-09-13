#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::GravityForce<CloudType>::GravityForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, false),
	g_(owner.g().value())
{}


template<class CloudType>
tnbLib::GravityForce<CloudType>::GravityForce(const GravityForce& gf)
	:
	ParticleForce<CloudType>(gf),
	g_(gf.g_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::GravityForce<CloudType>::~GravityForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::GravityForce<CloudType>::calcNonCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value(Zero, 0.0);

	value.Su() = mass * g_*(1.0 - td.rhoc() / p.rho());

	return value;
}


// ************************************************************************* //