#include <volFieldValue.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		namespace fieldValues
		{
			defineTypeNameAndDebug(volFieldValue, 0);
			addToRunTimeSelectionTable(fieldValue, volFieldValue, dictionary);
			addToRunTimeSelectionTable(functionObject, volFieldValue, dictionary);
		}
	}
}

//template<>
//const char*
//tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::volFieldValue::operationType,
//	13
//>::names[] =
//{
//	"none",
//	"sum",
//	"weightedSum",
//	"sumMag",
//	"average",
//	"weightedAverage",
//	"volAverage",
//	"weightedVolAverage",
//	"volIntegrate",
//	"weightedVolIntegrate",
//	"min",
//	"max",
//	"CoV"
//};
//
//const tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::volFieldValue::operationType,
//	13
//> tnbLib::functionObjects::fieldValues::volFieldValue::operationTypeNames_;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldValues::volFieldValue::initialise
(
	const dictionary& dict
)
{
	if (dict.readIfPresent("weightField", weightFieldName_))
	{
		Info << "    weight field = " << weightFieldName_;
	}

	Info << nl << endl;
}


void tnbLib::functionObjects::fieldValues::volFieldValue::writeFileHeader
(
	const label i
)
{
	volRegion::writeFileHeader(*this, file());

	writeCommented(file(), "Time");

	forAll(fields_, fieldi)
	{
		file()
			<< tab << operationTypeNames_[operation_]
			<< "(" << fields_[fieldi] << ")";
	}

	file() << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::volFieldValue::volFieldValue
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldValue(name, runTime, dict, typeName),
	volRegion(fieldValue::mesh_, dict),
	operation_(operationTypeNames_.read(dict.lookup("operation"))),
	weightFieldName_("none")
{
	read(dict);
}


tnbLib::functionObjects::fieldValues::volFieldValue::volFieldValue
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	fieldValue(name, obr, dict, typeName),
	volRegion(fieldValue::mesh_, dict),
	operation_(operationTypeNames_.read(dict.lookup("operation"))),
	weightFieldName_("none")
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::volFieldValue::~volFieldValue()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldValues::volFieldValue::read
(
	const dictionary& dict
)
{
	fieldValue::read(dict);

	// No additional info to read
	initialise(dict);

	return true;
}


bool tnbLib::functionObjects::fieldValues::volFieldValue::write()
{
	fieldValue::write();

	if (Pstream::master())
	{
		writeTime(file());
	}

	forAll(fields_, i)
	{
		const word& fieldName = fields_[i];
		bool processed = false;

		processed = processed || writeValues<scalar>(fieldName);
		processed = processed || writeValues<vector>(fieldName);
		processed = processed || writeValues<sphericalTensor>(fieldName);
		processed = processed || writeValues<symmTensor>(fieldName);
		processed = processed || writeValues<tensor>(fieldName);

		if (!processed)
		{
			WarningInFunction
				<< "Requested field " << fieldName
				<< " not found in database and not processed"
				<< endl;
		}
	}

	if (Pstream::master())
	{
		file() << endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //