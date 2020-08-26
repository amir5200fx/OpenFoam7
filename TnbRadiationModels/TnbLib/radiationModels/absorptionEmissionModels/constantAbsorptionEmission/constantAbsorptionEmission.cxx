#include <constantAbsorptionEmission.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(constant, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				constant,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::constant::constant
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	absorptionEmissionModel(dict, mesh),
	coeffsDict_(dict.optionalSubDict(typeName + "Coeffs")),
	a_("absorptivity", dimless / dimLength, coeffsDict_),
	e_("emissivity", dimless / dimLength, coeffsDict_),
	E_("E", dimMass / dimLength / pow3(dimTime), coeffsDict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::constant::~constant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::constant::aCont
(
	const label bandI
) const
{
	return volScalarField::New
	(
		"a",
		mesh_,
		a_
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::constant::eCont
(
	const label bandI
) const
{
	return volScalarField::New
	(
		"e",
		mesh_,
		e_
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::constant::ECont
(
	const label bandI
) const
{
	return volScalarField::New
	(
		"E",
		mesh_,
		E_
	);
}


// ************************************************************************* //