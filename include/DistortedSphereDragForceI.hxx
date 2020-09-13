#pragma once
#include <SphereDragForce.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DistortedSphereDragForce<CloudType>::DistortedSphereDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, false)
{}


template<class CloudType>
tnbLib::DistortedSphereDragForce<CloudType>::DistortedSphereDragForce
(
	const DistortedSphereDragForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DistortedSphereDragForce<CloudType>::~DistortedSphereDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::DistortedSphereDragForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	// Limit the drop distortion to y=0 (sphere) and y=1 (disk)
	const scalar y = min(max(p.y(), 0), 1);

	const scalar CdRe = SphereDragForce<CloudType>::CdRe(Re);

	return forceSuSp
	(
		Zero,
		mass*0.75*muc*CdRe*(1 + 2.632*y) / (p.rho()*sqr(p.d()))
	);
}


// ************************************************************************* //