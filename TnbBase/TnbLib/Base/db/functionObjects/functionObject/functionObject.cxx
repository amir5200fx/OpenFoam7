#include <functionObject.hxx>

#include <dictionary.hxx>
#include <dlLibraryTable.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineDebugSwitchWithName(functionObject, "functionObject", 0);
	defineRunTimeSelectionTable(functionObject, dictionary);
}

bool tnbLib::functionObject::postProcess(false);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObject::functionObject(const word& name)
	:
	name_(name),
	log(postProcess)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::functionObject> tnbLib::functionObject::New
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
{
	const word functionType(dict.lookup("type"));

	if (debug)
	{
		Info << "Selecting function " << functionType << endl;
	}

	if (dict.found("functionObjectLibs"))
	{
		const_cast<Time&>(runTime).libs().open
		(
			dict,
			"functionObjectLibs",
			dictionaryConstructorTablePtr_
		);
	}
	else
	{
		const_cast<Time&>(runTime).libs().open
		(
			dict,
			"libs",
			dictionaryConstructorTablePtr_
		);
	}

	if (!dictionaryConstructorTablePtr_)
	{
		FatalErrorInFunction
			<< "Unknown function type "
			<< functionType << nl << nl
			<< "Table of functionObjects is empty" << endl
			<< exit(FatalError);
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(functionType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown function type "
			<< functionType << nl << nl
			<< "Valid functions are : " << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << endl
			<< exit(FatalError);
	}

	return autoPtr<functionObject>(cstrIter()(name, runTime, dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObject::~functionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::functionObject::name() const
{
	return name_;
}


bool tnbLib::functionObject::read(const dictionary& dict)
{
	if (!postProcess)
	{
		log = dict.lookupOrDefault<Switch>("log", true);
	}

	return true;
}


bool tnbLib::functionObject::end()
{
	return true;
}


bool tnbLib::functionObject::setTimeStep()
{
	return false;
}


tnbLib::scalar tnbLib::functionObject::timeToNextWrite()
{
	return vGreat;
}


void tnbLib::functionObject::updateMesh(const mapPolyMesh&)
{}


void tnbLib::functionObject::movePoints(const polyMesh&)
{}


// ************************************************************************* //