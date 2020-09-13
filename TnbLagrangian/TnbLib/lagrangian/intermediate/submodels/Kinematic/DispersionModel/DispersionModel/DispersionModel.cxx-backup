#include <DispersionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DispersionModel<CloudType>::DispersionModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner)
{}


template<class CloudType>
tnbLib::DispersionModel<CloudType>::DispersionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type)
{}


template<class CloudType>
tnbLib::DispersionModel<CloudType>::DispersionModel
(
	const DispersionModel<CloudType>& dm
)
	:
	CloudSubModelBase<CloudType>(dm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DispersionModel<CloudType>::~DispersionModel()
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <DispersionModelNew.cxx>

// ************************************************************************* //