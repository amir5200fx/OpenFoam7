#include <greyMeanCombustion.hxx>

#include <combustionModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(greyMeanCombustion, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				greyMeanCombustion,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::greyMeanCombustion::
greyMeanCombustion
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	greyMean(dict, mesh, typeName),
	EhrrCoeff_(readScalar(coeffsDict_.lookup("EhrrCoeff")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::greyMeanCombustion::
~greyMeanCombustion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::greyMeanCombustion::ECont
(
	const label bandI
) const
{
	tmp<volScalarField> E = greyMean::ECont(bandI);

	const word& name = combustionModel::combustionPropertiesName;
	E.ref() += EhrrCoeff_ * mesh_.lookupObject<combustionModel>(name).Qdot();

	return E;
}


// ************************************************************************* //