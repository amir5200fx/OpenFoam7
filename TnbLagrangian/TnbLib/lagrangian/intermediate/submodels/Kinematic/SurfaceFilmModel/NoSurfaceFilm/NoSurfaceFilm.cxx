#include <NoSurfaceFilm.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoSurfaceFilm<CloudType>::NoSurfaceFilm
(
	const dictionary&,
	CloudType& owner
)
	:
	SurfaceFilmModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoSurfaceFilm<CloudType>::NoSurfaceFilm
(
	const NoSurfaceFilm<CloudType>& sfm
)
	:
	SurfaceFilmModel<CloudType>(sfm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoSurfaceFilm<CloudType>::~NoSurfaceFilm()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoSurfaceFilm<CloudType>::active() const
{
	return false;
}


template<class CloudType>
bool tnbLib::NoSurfaceFilm<CloudType>::transferParcel
(
	parcelType&,
	const polyPatch&,
	bool&
)
{
	return false;
}


template<class CloudType>
void tnbLib::NoSurfaceFilm<CloudType>::setParcelProperties
(
	parcelType&,
	const label
) const
{}


template<class CloudType>
void tnbLib::NoSurfaceFilm<CloudType>::info(Ostream&)
{}


// ************************************************************************* //