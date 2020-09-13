#pragma once
#include <fvcDdt.hxx>
#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PressureGradientForce<CloudType>::PressureGradientForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& forceType
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, forceType, true),
	UName_(this->coeffs().template lookupOrDefault<word>("U", "U")),
	DUcDtInterpPtr_(nullptr)
{}


template<class CloudType>
tnbLib::PressureGradientForce<CloudType>::PressureGradientForce
(
	const PressureGradientForce& pgf
)
	:
	ParticleForce<CloudType>(pgf),
	UName_(pgf.UName_),
	DUcDtInterpPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PressureGradientForce<CloudType>::~PressureGradientForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PressureGradientForce<CloudType>::cacheFields(const bool store)
{
	static word fName("DUcDt");

	bool fieldExists = this->mesh().template foundObject<volVectorField>(fName);

	if (store)
	{
		if (!fieldExists)
		{
			const volVectorField& Uc = this->mesh().template
				lookupObject<volVectorField>(UName_);

			volVectorField* DUcDtPtr = new volVectorField
			(
				fName,
				fvc::ddt(Uc) + (Uc & fvc::grad(Uc))
			);

			DUcDtPtr->store();
		}

		const volVectorField& DUcDt = this->mesh().template
			lookupObject<volVectorField>(fName);

		DUcDtInterpPtr_.reset
		(
			interpolation<vector>::New
			(
				this->owner().solution().interpolationSchemes(),
				DUcDt
			).ptr()
		);
	}
	else
	{
		DUcDtInterpPtr_.clear();

		if (fieldExists)
		{
			const volVectorField& DUcDt = this->mesh().template
				lookupObject<volVectorField>(fName);

			const_cast<volVectorField&>(DUcDt).checkOut();
		}
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::PressureGradientForce<CloudType>::calcCoupled
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

	vector DUcDt =
		DUcDtInterp().interpolate(p.coordinates(), p.currentTetIndices());

	value.Su() = mass * td.rhoc() / p.rho()*DUcDt;

	return value;
}


template<class CloudType>
tnbLib::scalar tnbLib::PressureGradientForce<CloudType>::massAdd
(
	const typename CloudType::parcelType&,
	const typename CloudType::parcelType::trackingData& td,
	const scalar
) const
{
	return 0.0;
}


// ************************************************************************* //