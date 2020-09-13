#pragma once
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NonInertialFrameForce<CloudType>::NonInertialFrameForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	WName_
	(
		this->coeffs().template lookupOrDefault<word>
		(
			"linearAccelerationName",
			"linearAcceleration"
			)
	),
	W_(Zero),
	omegaName_
	(
		this->coeffs().template lookupOrDefault<word>
		(
			"angularVelocityName",
			"angularVelocity"
			)
	),
	omega_(Zero),
	omegaDotName_
	(
		this->coeffs().template lookupOrDefault<word>
		(
			"angularAccelerationName",
			"angularAcceleration"
			)
	),
	omegaDot_(Zero),
	centreOfRotationName_
	(
		this->coeffs().template lookupOrDefault<word>
		(
			"centreOfRotationName",
			"centreOfRotation"
			)
	),
	centreOfRotation_(Zero)
{}


template<class CloudType>
tnbLib::NonInertialFrameForce<CloudType>::NonInertialFrameForce
(
	const NonInertialFrameForce& niff
)
	:
	ParticleForce<CloudType>(niff),
	WName_(niff.WName_),
	W_(niff.W_),
	omegaName_(niff.omegaName_),
	omega_(niff.omega_),
	omegaDotName_(niff.omegaDotName_),
	omegaDot_(niff.omegaDot_),
	centreOfRotationName_(niff.centreOfRotationName_),
	centreOfRotation_(niff.centreOfRotation_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NonInertialFrameForce<CloudType>::~NonInertialFrameForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::NonInertialFrameForce<CloudType>::cacheFields(const bool store)
{
	W_ = Zero;
	omega_ = Zero;
	omegaDot_ = Zero;
	centreOfRotation_ = Zero;

	if (store)
	{
		if
			(
				this->mesh().template foundObject<uniformDimensionedVectorField>
				(
					WName_
					)
				)
		{
			const uniformDimensionedVectorField& W = this->mesh().template
				lookupObject<uniformDimensionedVectorField>(WName_);

			W_ = W.value();
		}

		if
			(
				this->mesh().template foundObject<uniformDimensionedVectorField>
				(
					omegaName_
					)
				)
		{
			const uniformDimensionedVectorField& omega = this->mesh().template
				lookupObject<uniformDimensionedVectorField>(omegaName_);

			omega_ = omega.value();
		}

		if
			(
				this->mesh().template foundObject<uniformDimensionedVectorField>
				(
					omegaDotName_
					)
				)
		{
			const uniformDimensionedVectorField& omegaDot =
				this->mesh().template
				lookupObject<uniformDimensionedVectorField>(omegaDotName_);

			omegaDot_ = omegaDot.value();
		}

		if
			(
				this->mesh().template foundObject<uniformDimensionedVectorField>
				(
					centreOfRotationName_
					)
				)
		{
			const uniformDimensionedVectorField& centreOfRotation =
				this->mesh().template
				lookupObject<uniformDimensionedVectorField>
				(
					centreOfRotationName_
					);

			centreOfRotation_ = centreOfRotation.value();
		}
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::NonInertialFrameForce<CloudType>::calcNonCoupled
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

	const vector r = p.position() - centreOfRotation_;

	value.Su() =
		mass
		* (
			-W_
			+ (r ^ omegaDot_)
			+ 2.0*(p.U() ^ omega_)
			+ (omega_ ^ (r ^ omega_))
			);

	return value;
}


// ************************************************************************* //