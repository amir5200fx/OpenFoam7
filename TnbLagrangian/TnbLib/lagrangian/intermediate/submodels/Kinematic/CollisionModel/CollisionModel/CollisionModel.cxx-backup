#include <CollisionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CollisionModel<CloudType>::CollisionModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner)
{}


template<class CloudType>
tnbLib::CollisionModel<CloudType>::CollisionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type)
{}


template<class CloudType>
tnbLib::CollisionModel<CloudType>::CollisionModel
(
	const CollisionModel<CloudType>& cm
)
	:
	CloudSubModelBase<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CollisionModel<CloudType>::~CollisionModel()
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CollisionModelNew.cxx>

// ************************************************************************* //