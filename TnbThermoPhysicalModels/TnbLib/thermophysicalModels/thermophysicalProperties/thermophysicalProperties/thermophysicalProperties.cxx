#include <thermophysicalProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(thermophysicalProperties, 0);
	defineRunTimeSelectionTable(thermophysicalProperties, );
	defineRunTimeSelectionTable(thermophysicalProperties, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::thermophysicalProperties::thermophysicalProperties(scalar W)
	:
	W_(W)
{}


tnbLib::thermophysicalProperties::thermophysicalProperties(const dictionary& dict)
	:
	W_(readScalar(dict.lookup("W")))
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::thermophysicalProperties>
tnbLib::thermophysicalProperties::New
(
	const word& name
)
{
	if (debug)
	{
		InfoInFunction << "Constructing thermophysicalProperties" << endl;
	}

	ConstructorTable::iterator cstrIter = ConstructorTablePtr_->find(name);

	if (cstrIter == ConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown thermophysicalProperties type "
			<< name << nl << nl
			<< "Valid thermophysicalProperties types are:" << nl
			<< ConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<thermophysicalProperties>(cstrIter()());
}


tnbLib::autoPtr<tnbLib::thermophysicalProperties>
tnbLib::thermophysicalProperties::New
(
	const dictionary& dict
)
{
	if (debug)
	{
		InfoInFunction << "Constructing thermophysicalProperties" << endl;
	}

	const word& thermophysicalPropertiesTypeName = dict.dictName();

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(thermophysicalPropertiesTypeName);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown thermophysicalProperties type "
			<< thermophysicalPropertiesTypeName << nl << nl
			<< "Valid thermophysicalProperties types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<thermophysicalProperties>(cstrIter()(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::thermophysicalProperties::readIfPresent(const dictionary &dict)
{
	dict.readIfPresent("W", W_);
}


void tnbLib::thermophysicalProperties::writeData(Ostream& os) const
{
	os << W_;
}


void tnbLib::thermophysicalProperties::write(Ostream& os) const
{
	dictionary dict("thermophysicalProperties");
	dict.add("W", W_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const thermophysicalProperties& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //