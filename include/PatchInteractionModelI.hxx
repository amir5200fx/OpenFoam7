#pragma once
#include <fvMesh.hxx>
#include <Time.hxx>
#include <volFields.hxx>

#include <IStringStream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::wordList tnbLib::PatchInteractionModel<CloudType>::interactionTypeNames_
(
	IStringStream
	(
		"(none rebound stick escape)"
	)()
);

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::word tnbLib::PatchInteractionModel<CloudType>::interactionTypeToWord
(
	const interactionType& itEnum
)
{
	word it = "other";

	switch (itEnum)
	{
	case itNone:
	{
		it = "none";
		break;
	}
	case itRebound:
	{
		it = "rebound";
		break;
	}
	case itStick:
	{
		it = "stick";
		break;
	}
	case itEscape:
	{
		it = "escape";
		break;
	}
	default:
	{
	}
	}

	return it;
}


template<class CloudType>
typename tnbLib::PatchInteractionModel<CloudType>::interactionType
tnbLib::PatchInteractionModel<CloudType>::wordToInteractionType
(
	const word& itWord
)
{
	if (itWord == "none")
	{
		return itNone;
	}
	if (itWord == "rebound")
	{
		return itRebound;
	}
	else if (itWord == "stick")
	{
		return itStick;
	}
	else if (itWord == "escape")
	{
		return itEscape;
	}
	else
	{
		return itOther;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchInteractionModel<CloudType>::PatchInteractionModel
(
	CloudType& owner
)
	:
	CloudSubModelBase<CloudType>(owner),
	UName_("unknown_U")
{}


template<class CloudType>
tnbLib::PatchInteractionModel<CloudType>::PatchInteractionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	UName_(this->coeffDict().lookupOrDefault("U", word("U")))
{}


template<class CloudType>
tnbLib::PatchInteractionModel<CloudType>::PatchInteractionModel
(
	const PatchInteractionModel<CloudType>& pim
)
	:
	CloudSubModelBase<CloudType>(pim),
	UName_(pim.UName_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchInteractionModel<CloudType>::~PatchInteractionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::word& tnbLib::PatchInteractionModel<CloudType>::UName() const
{
	return UName_;
}


template<class CloudType>
void tnbLib::PatchInteractionModel<CloudType>::info(Ostream& os)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //