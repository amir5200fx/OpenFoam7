#include <NoInjection.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoInjection<CloudType>::NoInjection
(
	const dictionary&,
	CloudType& owner,
	const word&
)
	:
	InjectionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoInjection<CloudType>::NoInjection(const NoInjection<CloudType>& im)
	:
	InjectionModel<CloudType>(im.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoInjection<CloudType>::~NoInjection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoInjection<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoInjection<CloudType>::timeEnd() const
{
	return 0.0;
}


template<class CloudType>
tnbLib::label tnbLib::NoInjection<CloudType>::parcelsToInject
(
	const scalar,
	const scalar
)
{
	return 0;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoInjection<CloudType>::volumeToInject
(
	const scalar,
	const scalar
)
{
	return 0.0;
}


template<class CloudType>
void tnbLib::NoInjection<CloudType>::setPositionAndCell
(
	const label,
	const label,
	const scalar,
	vector&,
	label&,
	label&,
	label&
)
{}


template<class CloudType>
void tnbLib::NoInjection<CloudType>::setProperties
(
	const label,
	const label,
	const scalar,
	typename CloudType::parcelType& parcel
)
{
	// set particle velocity
	parcel.U() = Zero;

	// set particle diameter
	parcel.d() = 0.0;
}


template<class CloudType>
bool tnbLib::NoInjection<CloudType>::fullyDescribed() const
{
	return false;
}


template<class CloudType>
bool tnbLib::NoInjection<CloudType>::validInjection(const label)
{
	return false;
}


// ************************************************************************* //