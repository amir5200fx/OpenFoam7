#define FoamNamedEnum_EXPORT_DEFINE

#include <fieldMinMax.hxx>

#include <fieldTypes.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldMinMax, 0);
		addToRunTimeSelectionTable(functionObject, fieldMinMax, dictionary);
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldMinMax::modeType,
	2
>::names[] = { "magnitude", "component" };

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldMinMax::modeType,
	2
> tnbLib::functionObjects::fieldMinMax::modeTypeNames_;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldMinMax::writeFileHeader(const label i)
{
	OFstream& file = this->file();

	writeHeader(file, "Field minima and maxima");
	writeCommented(file, "Time");

	if (location_)
	{
		writeTabbed(file, "field");

		writeTabbed(file, "min");
		writeTabbed(file, "location(min)");

		if (Pstream::parRun())
		{
			writeTabbed(file, "processor");
		}

		writeTabbed(file, "max");
		writeTabbed(file, "location(max)");

		if (Pstream::parRun())
		{
			writeTabbed(file, "processor");
		}
	}
	else
	{
		forAll(fieldSet_, fieldi)
		{
			writeTabbed(file, "min(" + fieldSet_[fieldi] + ')');
			writeTabbed(file, "max(" + fieldSet_[fieldi] + ')');
		}
	}

	file << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldMinMax::fieldMinMax
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	location_(true),
	mode_(modeType::mag),
	fieldSet_()
{
	read(dict);
	resetName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldMinMax::~fieldMinMax()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldMinMax::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	location_ = dict.lookupOrDefault<Switch>("location", true);

	mode_ = modeTypeNames_[dict.lookupOrDefault<word>("mode", "magnitude")];
	dict.lookup("fields") >> fieldSet_;

	return true;
}


bool tnbLib::functionObjects::fieldMinMax::execute()
{
	return true;
}


bool tnbLib::functionObjects::fieldMinMax::write()
{
	logFiles::write();

	if (Pstream::master() && !location_) writeTime(file());
	TnbLog << type() << " " << name() << " write:" << nl;

	forAll(fieldSet_, fieldi)
	{
		calcMinMaxFields<scalar>(fieldSet_[fieldi], modeType::cmpt);
		calcMinMaxFields<vector>(fieldSet_[fieldi], mode_);
		calcMinMaxFields<sphericalTensor>(fieldSet_[fieldi], mode_);
		calcMinMaxFields<symmTensor>(fieldSet_[fieldi], mode_);
		calcMinMaxFields<tensor>(fieldSet_[fieldi], mode_);
	}

	if (Pstream::master() && !location_) file() << endl;
	TnbLog << endl;

	return true;
}



// ************************************************************************* //