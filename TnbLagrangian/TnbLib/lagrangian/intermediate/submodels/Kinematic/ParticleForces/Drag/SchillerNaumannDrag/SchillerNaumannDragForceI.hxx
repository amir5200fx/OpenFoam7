#pragma once
// * * * * * * * * * * * * *  Static Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::SchillerNaumannDragForce<CloudType>::CdRe(const scalar Re)
{
	if (Re > 1000.0)
	{
		return 0.44*Re;
	}
	else
	{
		return 24.0*(1.0 + 0.15*pow(Re, 0.687));
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SchillerNaumannDragForce<CloudType>::SchillerNaumannDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, false)
{}


template<class CloudType>
tnbLib::SchillerNaumannDragForce<CloudType>::SchillerNaumannDragForce
(
	const SchillerNaumannDragForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SchillerNaumannDragForce<CloudType>::~SchillerNaumannDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::SchillerNaumannDragForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	return forceSuSp(Zero, mass*0.75*muc*CdRe(Re) / (p.rho()*sqr(p.d())));
}


// ************************************************************************* //