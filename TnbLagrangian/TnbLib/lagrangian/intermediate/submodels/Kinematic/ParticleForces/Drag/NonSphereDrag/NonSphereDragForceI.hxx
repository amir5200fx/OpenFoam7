#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NonSphereDragForce<CloudType>::NonSphereDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	phi_(readScalar(this->coeffs().lookup("phi"))),
	a_(exp(2.3288 - 6.4581*phi_ + 2.4486*sqr(phi_))),
	b_(0.0964 + 0.5565*phi_),
	c_(exp(4.9050 - 13.8944*phi_ + 18.4222*sqr(phi_) - 10.2599*pow3(phi_))),
	d_(exp(1.4681 + 12.2584*phi_ - 20.7322*sqr(phi_) + 15.8855*pow3(phi_)))
{
	if (phi_ <= 0 || phi_ > 1)
	{
		FatalErrorInFunction
			<< "Ratio of surface of sphere having same volume as particle to "
			<< "actual surface area of particle (phi) must be greater than 0 "
			<< "and less than or equal to 1" << exit(FatalError);
	}
}


template<class CloudType>
tnbLib::NonSphereDragForce<CloudType>::NonSphereDragForce
(
	const NonSphereDragForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df),
	phi_(df.phi_),
	a_(df.a_),
	b_(df.b_),
	c_(df.c_),
	d_(df.d_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NonSphereDragForce<CloudType>::~NonSphereDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::NonSphereDragForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	const scalar CdRe =
		24 * (1 + a_ * pow(Re, b_)) + Re * c_ / (1 + d_ / (Re + rootVSmall));

	return forceSuSp(Zero, mass*0.75*muc*CdRe / (p.rho()*sqr(p.d())));
}


// ************************************************************************* //