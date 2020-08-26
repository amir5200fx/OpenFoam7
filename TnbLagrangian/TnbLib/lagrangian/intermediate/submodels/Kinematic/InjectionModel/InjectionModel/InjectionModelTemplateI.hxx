#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::InjectionModel<CloudType>::timeStart() const
{
	return SOI_;
}


template<class CloudType>
tnbLib::scalar tnbLib::InjectionModel<CloudType>::volumeTotal() const
{
	return volumeTotal_;
}


template<class CloudType>
tnbLib::scalar tnbLib::InjectionModel<CloudType>::massTotal() const
{
	return massTotal_;
}


template<class CloudType>
tnbLib::scalar tnbLib::InjectionModel<CloudType>::massInjected() const
{
	return massInjected_;
}


template<class CloudType>
tnbLib::label tnbLib::InjectionModel<CloudType>::nInjections() const
{
	return nInjections_;
}


template<class CloudType>
tnbLib::label tnbLib::InjectionModel<CloudType>::parcelsAddedTotal() const
{
	return parcelsAddedTotal_;
}


// ************************************************************************* //