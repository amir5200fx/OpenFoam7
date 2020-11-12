#define FoamNamedEnum_EXPORT_DEFINE

#include <fieldValueDelta.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <fvPatchField.hxx> // added by Amin
#include <fvsPatchField.hxx> // added by Amin

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		namespace fieldValues
		{
			defineTypeNameAndDebug(fieldValueDelta, 0);
			addToRunTimeSelectionTable(functionObject, fieldValueDelta, dictionary);
		}
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::fieldValueDelta::operationType,
	5
>::names[] =
{
	"add",
	"subtract",
	"min",
	"max",
	"average"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::fieldValueDelta::operationType,
	5
> tnbLib::functionObjects::fieldValues::fieldValueDelta::operationTypeNames_;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldValues::fieldValueDelta::writeFileHeader
(
	const label i
)
{
	const wordList& fields1 = region1Ptr_->fields();
	const wordList& fields2 = region2Ptr_->fields();

	DynamicList<word> commonFields(fields1.size());
	forAll(fields1, fieldi)
	{
		label index = findIndex(fields2, fields1[fieldi]);
		if (index != -1)
		{
			commonFields.append(fields1[fieldi]);
		}
	}

	Ostream& os = file();

	writeHeaderValue(os, "Source1", region1Ptr_->name());
	writeHeaderValue(os, "Source2", region2Ptr_->name());
	writeHeaderValue(os, "Operation", operationTypeNames_[operation_]);
	writeCommented(os, "Time");

	forAll(commonFields, i)
	{
		os << tab << commonFields[i];
	}

	os << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::fieldValueDelta::fieldValueDelta
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	regionFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	operation_(operationType::subtract),
	region1Ptr_(nullptr),
	region2Ptr_(nullptr)
{
	read(dict);
	resetName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::fieldValueDelta::~fieldValueDelta()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldValues::fieldValueDelta::read
(
	const dictionary& dict
)
{
	regionFunctionObject::read(dict);

	region1Ptr_.reset
	(
		fieldValue::New
		(
			name() + ".region1",
			obr_,
			dict.subDict("region1"),
			false
		).ptr()
	);
	region2Ptr_.reset
	(
		fieldValue::New
		(
			name() + ".region2",
			obr_,
			dict.subDict("region2"),
			false
		).ptr()
	);

	operation_ = operationTypeNames_.read(dict.lookup("operation"));

	return true;
}


bool tnbLib::functionObjects::fieldValues::fieldValueDelta::write()
{
	logFiles::write();

	region1Ptr_->write();
	region2Ptr_->write();

	if (Pstream::master())
	{
		writeTime(file());
	}

	TnbLog << type() << " " << name() << " write:" << endl;

	bool found = false;
	processFields<scalar>(found);
	processFields<vector>(found);
	processFields<sphericalTensor>(found);
	processFields<symmTensor>(found);
	processFields<tensor>(found);

	if (Pstream::master())
	{
		file() << endl;
	}

	if (!found)
	{
		TnbLog << "    none" << endl;
	}
	else
	{
		TnbLog << endl;
	}

	return true;
}


bool tnbLib::functionObjects::fieldValues::fieldValueDelta::execute()
{
	return true;
}


// ************************************************************************* //