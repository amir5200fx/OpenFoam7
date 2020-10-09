#include <fieldValue.hxx>

#include <Time.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldValue, 0);
		defineRunTimeSelectionTable(fieldValue, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValue::fieldValue
(
	const word& name,
	const Time& runTime,
	const dictionary& dict,
	const word& valueType
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	dict_(dict),
	regionName_(word::null),
	resultDict_(fileName("name"), dictionary::null)
{
	read(dict);
	resetName(valueType);
}


tnbLib::functionObjects::fieldValue::fieldValue
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict,
	const word& valueType
)
	:
	fvMeshFunctionObject(name, obr, dict),
	logFiles(obr_, name),
	dict_(dict),
	regionName_(word::null),
	resultDict_(fileName("name"), dictionary::null)
{
	read(dict);
	resetName(valueType);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValue::~fieldValue()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldValue::read(const dictionary& dict)
{
	if (dict != dict_)
	{
		dict_ = dict;
	}

	fvMeshFunctionObject::read(dict);

	dict.lookup("fields") >> fields_;
	dict.lookup("writeFields") >> writeFields_;

	return true;
}


bool tnbLib::functionObjects::fieldValue::execute()
{
	return true;
}


bool tnbLib::functionObjects::fieldValue::write()
{
	logFiles::write();

	TnbLog << type() << " " << name() << " write:" << nl;

	return true;
}


// ************************************************************************* //