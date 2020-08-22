#include <ParamagneticForce.hxx>

#include <demandDrivenData.hxx>
#include <electromagneticConstants.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParamagneticForce<CloudType>::ParamagneticForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	HdotGradHName_
	(
		this->coeffs().template lookupOrDefault<word>("HdotGradH", "HdotGradH")
	),
	HdotGradHInterpPtr_(nullptr),
	magneticSusceptibility_
	(
		readScalar(this->coeffs().lookup("magneticSusceptibility"))
	)
{}


template<class CloudType>
tnbLib::ParamagneticForce<CloudType>::ParamagneticForce
(
	const ParamagneticForce& pf
)
	:
	ParticleForce<CloudType>(pf),
	HdotGradHName_(pf.HdotGradHName_),
	HdotGradHInterpPtr_(pf.HdotGradHInterpPtr_),
	magneticSusceptibility_(pf.magneticSusceptibility_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParamagneticForce<CloudType>::~ParamagneticForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ParamagneticForce<CloudType>::cacheFields(const bool store)
{
	if (store)
	{
		const volVectorField& HdotGradH =
			this->mesh().template lookupObject<volVectorField>(HdotGradHName_);

		HdotGradHInterpPtr_ = interpolation<vector>::New
		(
			this->owner().solution().interpolationSchemes(),
			HdotGradH
		).ptr();
	}
	else
	{
		deleteDemandDrivenData(HdotGradHInterpPtr_);
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ParamagneticForce<CloudType>::calcNonCoupled
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

	const interpolation<vector>& HdotGradHInterp = *HdotGradHInterpPtr_;

	value.Su() =
		mass * 3.0*constant::electromagnetic::mu0.value() / p.rho()
		*magneticSusceptibility_ / (magneticSusceptibility_ + 3)
		*HdotGradHInterp.interpolate(p.coordinates(), p.currentTetIndices());

	return value;
}


// ************************************************************************* //