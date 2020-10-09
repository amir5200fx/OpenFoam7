#include <writeObjects.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(writeObjects, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			writeObjects,
			dictionary
		);
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::writeObjects::writeOption,
	3
>::names[] =
{
	"autoWrite",
	"noWrite",
	"anyWrite"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::writeObjects::writeOption,
	3
> tnbLib::functionObjects::writeObjects::writeOptionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::writeObjects::writeObject
(
	const regIOobject& obj
)
{
	switch (writeOption_)
	{
	case writeOption::AUTO_WRITE:
	{
		if (obj.writeOpt() != IOobject::AUTO_WRITE)
		{
			return;
		}

		break;
	}
	case writeOption::NO_WRITE:
	{
		if (obj.writeOpt() != IOobject::NO_WRITE)
		{
			return;
		}

		break;
	}
	case writeOption::ANY_WRITE:
	{
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown writeOption "
			<< writeOptionNames_[writeOption_]
			<< ". Valid writeOption types are" << writeOptionNames_
			<< exit(FatalError);
	}
	}

	if
		(
			obj.writeOpt() == IOobject::AUTO_WRITE
			&& writeObr_.time().writeTime()
			)
	{
		TnbLog << "    automatically written object " << obj.name() << endl;
	}
	else
	{
		writeObjectsBase::writeObject(obj);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeObjects::writeObjects
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	writeObjectsBase
	(
		runTime.lookupObject<objectRegistry>
		(
			dict.lookupOrDefault("region", polyMesh::defaultRegion)
			),
		log
	),
	writeOption_(writeOption::ANY_WRITE)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeObjects::~writeObjects()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::writeObjects::read(const dictionary& dict)
{
	if (dict.found("field"))
	{
		writeObjectNames_.setSize(1);
		dict.lookup("field") >> writeObjectNames_[0];
	}
	else if (dict.found("fields"))
	{
		dict.lookup("fields") >> writeObjectNames_;
	}
	else
	{
		writeObjectsBase::read(dict);
	}

	if (dict.found("writeOption"))
	{
		writeOption_ = writeOptionNames_.read(dict.lookup("writeOption"));
	}
	else
	{
		writeOption_ = writeOption::ANY_WRITE;
	}

	return functionObject::read(dict);
}


bool tnbLib::functionObjects::writeObjects::execute()
{
	return true;
}


bool tnbLib::functionObjects::writeObjects::write()
{
	Info << type() << " " << name() << " write:" << nl;

	writeObjectsBase::write();

	TnbLog << endl;

	return true;
}


// ************************************************************************* //