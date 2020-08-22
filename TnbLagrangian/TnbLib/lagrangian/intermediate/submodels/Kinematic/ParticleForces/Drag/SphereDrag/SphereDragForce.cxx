#include <SphereDragForce.hxx>

// * * * * * * * * * * * * *  Static Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::SphereDragForce<CloudType>::CdRe(const scalar Re)
{
	if (Re > 1000.0)
	{
		return 0.424*Re;
	}
	else
	{
		return 24.0*(1.0 + 1.0 / 6.0*pow(Re, 2.0 / 3.0));
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SphereDragForce<CloudType>::SphereDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, false)
{}


template<class CloudType>
tnbLib::SphereDragForce<CloudType>::SphereDragForce
(
	const SphereDragForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SphereDragForce<CloudType>::~SphereDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::SphereDragForce<CloudType>::calcCoupled
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