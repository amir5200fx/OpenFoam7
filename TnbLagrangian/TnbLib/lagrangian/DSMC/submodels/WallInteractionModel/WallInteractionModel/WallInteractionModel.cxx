#include <WallInteractionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::WallInteractionModel<CloudType>::WallInteractionModel(CloudType& owner)
	:
	dict_(dictionary::null),
	owner_(owner),
	coeffDict_(dictionary::null)
{}


template<class CloudType>
tnbLib::WallInteractionModel<CloudType>::WallInteractionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	dict_(dict),
	owner_(owner),
	coeffDict_(dict.subDict(type + "Coeffs"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::WallInteractionModel<CloudType>::~WallInteractionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType& tnbLib::WallInteractionModel<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
CloudType& tnbLib::WallInteractionModel<CloudType>::owner()
{
	return owner_;
}


template<class CloudType>
const tnbLib::dictionary& tnbLib::WallInteractionModel<CloudType>::dict() const
{
	return dict_;
}


template<class CloudType>
const tnbLib::dictionary&
tnbLib::WallInteractionModel<CloudType>::coeffDict() const
{
	return coeffDict_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WallInteractionModelNew.cxx>

// ************************************************************************* //