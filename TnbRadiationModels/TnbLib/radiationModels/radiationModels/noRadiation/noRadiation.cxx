#include <noRadiation.hxx>

#include <physicoChemicalConstants.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		defineTypeNameAndDebug(noRadiation, 0);
		addToRadiationRunTimeSelectionTables(noRadiation);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::noRadiation::noRadiation(const volScalarField& T)
	:
	radiationModel(T)
{}


tnbLib::radiationModels::noRadiation::noRadiation
(
	const dictionary& dict,
	const volScalarField& T
)
	:
	radiationModel(T)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::noRadiation::~noRadiation()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::radiationModels::noRadiation::correct()
{}


void tnbLib::radiationModels::noRadiation::calculate()
{}


bool tnbLib::radiationModels::noRadiation::read()
{
	return radiationModel::read();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::radiationModels::noRadiation::Rp() const
{
	return volScalarField::New
	(
		"Rp",
		mesh_,
		dimensionedScalar
		(
			constant::physicoChemical::sigma.dimensions() / dimLength,
			0
		)
	);
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::radiationModels::noRadiation::Ru() const
{
	return volScalarField::Internal::New
	(
		"Ru",
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	);
}


// ************************************************************************* //
