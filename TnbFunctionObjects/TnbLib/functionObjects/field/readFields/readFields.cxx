#include <readFields.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(readFields, 0);
		addToRunTimeSelectionTable(functionObject, readFields, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::readFields::readFields
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldSet_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::readFields::~readFields()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::readFields::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	dict.lookup("fields") >> fieldSet_;

	return true;
}


bool tnbLib::functionObjects::readFields::execute()
{
	// Clear out any previously loaded fields
	vsf_.clear();
	vvf_.clear();
	vSpheretf_.clear();
	vSymmtf_.clear();
	vtf_.clear();

	ssf_.clear();
	svf_.clear();
	sSpheretf_.clear();
	sSymmtf_.clear();
	stf_.clear();

	forAll(fieldSet_, fieldi)
	{
		const word& fieldName = fieldSet_[fieldi];

		// If necessary load field
		loadField<scalar>(fieldName, vsf_, ssf_);
		loadField<vector>(fieldName, vvf_, svf_);
		loadField<sphericalTensor>(fieldName, vSpheretf_, sSpheretf_);
		loadField<symmTensor>(fieldName, vSymmtf_, sSymmtf_);
		loadField<tensor>(fieldName, vtf_, stf_);
	}

	return true;
}


bool tnbLib::functionObjects::readFields::write()
{
	return true;
}


// ************************************************************************* //