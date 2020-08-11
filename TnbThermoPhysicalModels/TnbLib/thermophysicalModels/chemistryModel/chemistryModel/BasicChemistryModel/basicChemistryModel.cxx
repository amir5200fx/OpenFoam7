#include <basicChemistryModel.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(basicChemistryModel, 0);
}

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::basicChemistryModel::correct()
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicChemistryModel::basicChemistryModel(basicThermo& thermo)
	:
	IOdictionary
	(
		IOobject
		(
			thermo.phasePropertyName("chemistryProperties"),
			thermo.db().time().constant(),
			thermo.db(),
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),
	mesh_(thermo.p().mesh()),
	chemistry_(lookup("chemistry")),
	deltaTChemIni_(readScalar(lookup("initialChemicalTimeStep"))),
	deltaTChemMax_(lookupOrDefault("maxChemicalTimeStep", great)),
	deltaTChem_
	(
		IOobject
		(
			thermo.phasePropertyName("deltaTChem"),
			mesh().time().constant(),
			mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh(),
		dimensionedScalar(dimTime, deltaTChemIni_)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::basicChemistryModel::~basicChemistryModel()
{}


// ************************************************************************* //