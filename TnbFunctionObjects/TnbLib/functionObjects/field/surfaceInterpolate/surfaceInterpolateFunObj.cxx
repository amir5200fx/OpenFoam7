#include <surfaceInterpolateFunObj.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(surfaceInterpolate, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			surfaceInterpolate,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::surfaceInterpolate::surfaceInterpolate
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

tnbLib::functionObjects::surfaceInterpolate::~surfaceInterpolate()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::surfaceInterpolate::read
(
	const dictionary& dict
)
{
	dict.lookup("fields") >> fieldSet_;

	return true;
}


bool tnbLib::functionObjects::surfaceInterpolate::execute()
{
	Info << type() << " " << name() << " write:" << nl;

	// Clear out any previously loaded fields
	ssf_.clear();
	svf_.clear();
	sSpheretf_.clear();
	sSymmtf_.clear();
	stf_.clear();

	interpolateFields<scalar>(ssf_);
	interpolateFields<vector>(svf_);
	interpolateFields<sphericalTensor>(sSpheretf_);
	interpolateFields<symmTensor>(sSymmtf_);
	interpolateFields<tensor>(stf_);

	Info << endl;

	return true;
}


bool tnbLib::functionObjects::surfaceInterpolate::write()
{
	Info << type() << " " << name() << " write:" << nl;

	Info << "    Writing interpolated surface fields to "
		<< obr_.time().timeName() << endl;

	forAll(ssf_, i)
	{
		ssf_[i].write();
	}
	forAll(svf_, i)
	{
		svf_[i].write();
	}
	forAll(sSpheretf_, i)
	{
		sSpheretf_[i].write();
	}
	forAll(sSymmtf_, i)
	{
		sSymmtf_[i].write();
	}
	forAll(stf_, i)
	{
		stf_[i].write();
	}

	return true;
}


// ************************************************************************* //