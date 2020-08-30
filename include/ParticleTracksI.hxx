#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
inline tnbLib::label tnbLib::ParticleTracks<CloudType>::trackInterval() const
{
	return trackInterval_;
}


template<class CloudType>
inline tnbLib::label tnbLib::ParticleTracks<CloudType>::maxSamples() const
{
	return maxSamples_;
}


template<class CloudType>
inline const tnbLib::Switch& tnbLib::ParticleTracks<CloudType>::resetOnWrite() const
{
	return resetOnWrite_;
}


template<class CloudType>
inline const typename tnbLib::ParticleTracks<CloudType>::hitTableType&
tnbLib::ParticleTracks<CloudType>::faceHitCounter() const
{
	return faceHitCounter_;
}


template<class CloudType>
inline const tnbLib::Cloud<typename CloudType::parcelType>&
tnbLib::ParticleTracks<CloudType>::cloud() const
{
	return cloudPtr_();
}


// ************************************************************************* //