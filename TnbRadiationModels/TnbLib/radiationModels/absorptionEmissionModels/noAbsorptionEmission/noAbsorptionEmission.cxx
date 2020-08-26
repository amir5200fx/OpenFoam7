#include <noAbsorptionEmission.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(noAbsorptionEmission, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				noAbsorptionEmission,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::noAbsorptionEmission::
noAbsorptionEmission
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	absorptionEmissionModel(dict, mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::noAbsorptionEmission::
~noAbsorptionEmission()
{}


// ************************************************************************* //