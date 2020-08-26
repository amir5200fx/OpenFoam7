#include <opaqueSolid.hxx>

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
		defineTypeNameAndDebug(opaqueSolid, 0);

		addToRadiationRunTimeSelectionTables(opaqueSolid);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::opaqueSolid::opaqueSolid(const volScalarField& T)
	:
	radiationModel(typeName, T)
{}


tnbLib::radiationModels::opaqueSolid::opaqueSolid
(
	const dictionary& dict,
	const volScalarField& T
)
	:
	radiationModel(typeName, dict, T)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::opaqueSolid::~opaqueSolid()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::radiationModels::opaqueSolid::read()
{
	return radiationModel::read();
}


void tnbLib::radiationModels::opaqueSolid::calculate()
{}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::radiationModels::opaqueSolid::Rp() const
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
tnbLib::radiationModels::opaqueSolid::Ru() const
{
	return volScalarField::Internal::New
	(
		"Ru",
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	);
}


// ************************************************************************* //