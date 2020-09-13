#include <NoCollision.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoCollision<CloudType>::NoCollision
(
	const dictionary& dict,
	CloudType& owner
)
	:
	CollisionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoCollision<CloudType>::NoCollision
(
	const NoCollision<CloudType>& cm
)
	:
	CollisionModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoCollision<CloudType>::~NoCollision()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::label tnbLib::NoCollision<CloudType>::nSubCycles() const
{
	return 1;
}


template<class CloudType>
bool tnbLib::NoCollision<CloudType>::active() const
{
	return false;
}


template<class CloudType>
void tnbLib::NoCollision<CloudType>::collide()
{}


// ************************************************************************* //