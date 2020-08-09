#include <turbulenceModel.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <wallFvPatch.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(turbulenceModel, 0);
}

const tnbLib::word tnbLib::turbulenceModel::propertiesName("turbulenceProperties");


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulenceModel::turbulenceModel
(
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const word& propertiesName
)
	:
	IOdictionary
	(
		IOobject
		(
			IOobject::groupName(propertiesName, alphaRhoPhi.group()),
			U.time().constant(),
			U.db(),
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),

	runTime_(U.time()),
	mesh_(U.mesh()),

	U_(U),
	alphaRhoPhi_(alphaRhoPhi),
	phi_(phi),
	y_(mesh_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::turbulenceModel::phi() const
{
	return phi_;
}


bool tnbLib::turbulenceModel::read()
{
	return regIOobject::read();
}


void tnbLib::turbulenceModel::validate()
{}


void tnbLib::turbulenceModel::correct()
{
	if (mesh_.changing())
	{
		y_.correct();
	}
}


// ************************************************************************* //