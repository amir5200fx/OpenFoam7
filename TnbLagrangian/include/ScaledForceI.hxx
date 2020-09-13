#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::dictionary tnbLib::ScaledForce<CloudType>::modelDict
(
	const dictionary& dict
) const
{
	dictionary modelDict(dict);
	modelDict.add<word>("type", dict.lookupType<word>("forceType"), true);
	return modelDict;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ScaledForce<CloudType>::ScaledForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	model_
	(
		ParticleForce<CloudType>::New
		(
			owner,
			mesh,
			modelDict(dict),
			dict.lookupType<word>("forceType")
		)
	),
	factor_(readScalar(this->coeffs().lookup("factor")))
{}


template<class CloudType>
tnbLib::ScaledForce<CloudType>::ScaledForce
(
	const ScaledForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df),
	model_(nullptr),
	factor_(1)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ScaledForce<CloudType>::~ScaledForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::ScaledForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	return factor_ * model_->calcCoupled(p, td, dt, mass, Re, muc);
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ScaledForce<CloudType>::calcNonCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	return factor_ * model_->calcCoupled(p, td, dt, mass, Re, muc);
}


template<class CloudType>
tnbLib::scalar tnbLib::ScaledForce<CloudType>::massAdd
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar mass
) const
{
	return factor_ * model_->massAdd(p, td, mass);
}


// ************************************************************************* //