#include <StochasticCollisionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::StochasticCollisionModel<CloudType>::StochasticCollisionModel
(
	CloudType& owner
)
	:
	CloudSubModelBase<CloudType>(owner)
{}


template<class CloudType>
tnbLib::StochasticCollisionModel<CloudType>::StochasticCollisionModel
(
	const StochasticCollisionModel<CloudType>& cm
)
	:
	CloudSubModelBase<CloudType>(cm)
{}


template<class CloudType>
tnbLib::StochasticCollisionModel<CloudType>::StochasticCollisionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::StochasticCollisionModel<CloudType>::~StochasticCollisionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::StochasticCollisionModel<CloudType>::update
(
	typename CloudType::parcelType::trackingData& td,
	const scalar dt
)
{
	if (this->active())
	{
		this->collide(td, dt);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <StochasticCollisionModelNew.cxx>

// ************************************************************************* //