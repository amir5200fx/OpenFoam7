#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::dimensionedVector& tnbLib::SurfaceFilmModel<CloudType>::g() const
{
	return g_;
}


template<class CloudType>
tnbLib::label& tnbLib::SurfaceFilmModel<CloudType>::nParcelsTransferred()
{
	return nParcelsTransferred_;
}


template<class CloudType>
tnbLib::label tnbLib::SurfaceFilmModel<CloudType>::nParcelsTransferred() const
{
	return nParcelsTransferred_;
}


template<class CloudType>
tnbLib::label& tnbLib::SurfaceFilmModel<CloudType>::nParcelsInjected()
{
	return nParcelsInjected_;
}


template<class CloudType>
tnbLib::label tnbLib::SurfaceFilmModel<CloudType>::nParcelsInjected() const
{
	return nParcelsInjected_;
}


// ************************************************************************* //