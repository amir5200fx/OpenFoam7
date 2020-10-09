#include <residuals.hxx>

#include <fieldTypes.hxx>  // added by amir
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(residuals, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			residuals,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::residuals::residuals
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	fieldSet_()
{
	read(dict);
	resetName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::residuals::~residuals()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::residuals::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	dict.lookup("fields") >> fieldSet_;

	return true;
}


void tnbLib::functionObjects::residuals::writeFileHeader(const label i)
{
	if (Pstream::master())
	{
		writeHeader(file(), "Residuals");
		writeCommented(file(), "Time");

		forAll(fieldSet_, fieldi)
		{
			const word& fieldName = fieldSet_[fieldi];

			writeFileHeader<scalar>(fieldName);
			writeFileHeader<vector>(fieldName);
			writeFileHeader<sphericalTensor>(fieldName);
			writeFileHeader<symmTensor>(fieldName);
			writeFileHeader<tensor>(fieldName);
		}

		file() << endl;
	}
}


bool tnbLib::functionObjects::residuals::execute()
{
	return true;
}


bool tnbLib::functionObjects::residuals::write()
{
	logFiles::write();

	if (Pstream::master())
	{
		writeTime(file());

		forAll(fieldSet_, fieldi)
		{
			const word& fieldName = fieldSet_[fieldi];

			writeResidual<scalar>(fieldName);
			writeResidual<vector>(fieldName);
			writeResidual<sphericalTensor>(fieldName);
			writeResidual<symmTensor>(fieldName);
			writeResidual<tensor>(fieldName);
		}

		file() << endl;
	}

	return true;
}


// ************************************************************************* //