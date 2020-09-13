#include <VirtualMassForce.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::VirtualMassForce<CloudType>::VirtualMassForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& forceType
)
	:
	PressureGradientForce<CloudType>(owner, mesh, dict, forceType),
	Cvm_(readScalar(this->coeffs().lookup("Cvm")))
{}


template<class CloudType>
tnbLib::VirtualMassForce<CloudType>::VirtualMassForce
(
	const VirtualMassForce& vmf
)
	:
	PressureGradientForce<CloudType>(vmf),
	Cvm_(vmf.Cvm_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::VirtualMassForce<CloudType>::~VirtualMassForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::VirtualMassForce<CloudType>::cacheFields(const bool store)
{
	PressureGradientForce<CloudType>::cacheFields(store);
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::VirtualMassForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value =
		PressureGradientForce<CloudType>::calcCoupled(p, td, dt, mass, Re, muc);

	value.Su() *= Cvm_;

	return value;
}


template<class CloudType>
tnbLib::scalar tnbLib::VirtualMassForce<CloudType>::massAdd
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar mass
) const
{
	return mass * td.rhoc() / p.rho()*Cvm_;
}


// ************************************************************************* //