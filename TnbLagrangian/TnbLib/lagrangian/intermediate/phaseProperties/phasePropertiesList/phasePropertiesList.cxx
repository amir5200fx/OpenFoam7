#include <phasePropertiesList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phasePropertiesList::phasePropertiesList()
	:
	props_(),
	phaseTypeNames_(),
	stateLabels_()
{}


tnbLib::phasePropertiesList::phasePropertiesList
(
	Istream& is,
	const wordList& gasNames,
	const wordList& liquidNames,
	const wordList& solidNames
)
	:
	props_(is),
	phaseTypeNames_(),
	stateLabels_()
{
	forAll(props_, i)
	{
		props_[i].reorder(gasNames, liquidNames, solidNames);
	}

	phaseTypeNames_.setSize(props_.size());
	stateLabels_.setSize(props_.size());
	forAll(props_, i)
	{
		phaseTypeNames_[i] = props_[i].phaseTypeName();
		stateLabels_[i] = props_[i].stateLabel();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phasePropertiesList::~phasePropertiesList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::List<tnbLib::phaseProperties>&
tnbLib::phasePropertiesList::props() const
{
	return props_;
}


const tnbLib::wordList& tnbLib::phasePropertiesList::phaseTypes() const
{
	return phaseTypeNames_;
}


const tnbLib::wordList& tnbLib::phasePropertiesList::stateLabels() const
{
	return stateLabels_;
}


tnbLib::label tnbLib::phasePropertiesList::size() const
{
	return props_.size();
}


const tnbLib::phaseProperties&
tnbLib::phasePropertiesList::operator[](const label phaseI) const
{
	return props_[phaseI];
}


// ************************************************************************* //