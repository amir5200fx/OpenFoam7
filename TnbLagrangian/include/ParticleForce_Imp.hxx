#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleForce<CloudType>::ParticleForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& forceType,
	const bool readCoeffs
)
	:
	owner_(owner),
	mesh_(mesh),
	coeffs_
	(
		readCoeffs
		? dict.optionalSubDict(forceType + "Coeffs")
		: dictionary::null
	)
{
	if (readCoeffs && coeffs_.isNull())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Force " << forceType << " must be specified as a dictionary"
			<< exit(FatalIOError);
	}
}


template<class CloudType>
tnbLib::ParticleForce<CloudType>::ParticleForce(const ParticleForce& pf)
	:
	owner_(pf.owner_),
	mesh_(pf.mesh_),
	coeffs_(pf.coeffs_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleForce<CloudType>::~ParticleForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ParticleForce<CloudType>::cacheFields(const bool store)
{}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ParticleForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType&,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value;
	value.Su() = Zero;
	value.Sp() = 0.0;

	return value;
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ParticleForce<CloudType>::calcNonCoupled
(
	const typename CloudType::parcelType&,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value;
	value.Su() = Zero;
	value.Sp() = 0.0;

	return value;
}


template<class CloudType>
tnbLib::scalar tnbLib::ParticleForce<CloudType>::massAdd
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar mass
) const
{
	return 0.0;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
