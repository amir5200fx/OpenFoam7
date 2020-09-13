#pragma once
// * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::demandDrivenEntry<Type>::demandDrivenEntry
(
	const dictionary& dict,
	const Type& value
)
	:
	dict_(dict),
	keyword_("unknown-keyword"),
	value_(value),
	stored_(true)
{}


template<class Type>
tnbLib::demandDrivenEntry<Type>::demandDrivenEntry
(
	const dictionary& dict,
	const word& keyword
)
	:
	dict_(dict),
	keyword_(keyword),
	value_(Zero),
	stored_(false)
{}


template<class Type>
tnbLib::demandDrivenEntry<Type>::demandDrivenEntry
(
	const dictionary& dict,
	const word& keyword,
	const Type& defaultValue,
	const bool readIfPresent
)
	:
	dict_(dict),
	keyword_(keyword),
	value_(defaultValue),
	stored_(true)
{
	if (readIfPresent)
	{
		dict_.readIfPresent<Type>(keyword, value_);
	}
}


template<class Type>
tnbLib::demandDrivenEntry<Type>::demandDrivenEntry(const demandDrivenEntry& dde)
	:
	dict_(dde.dict_),
	keyword_(dde.keyword_),
	value_(dde.value_),
	stored_(dde.stored_)
{}


// ************************************************************************* //