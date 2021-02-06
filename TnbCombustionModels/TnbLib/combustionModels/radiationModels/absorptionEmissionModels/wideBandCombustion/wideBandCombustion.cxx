#include <wideBandCombustion.hxx>

#include <combustionModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(wideBandCombustion, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				wideBandCombustion,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::wideBandCombustion::
wideBandCombustion
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	wideBand(dict, mesh, typeName)
{
	label bandi = 0;
	forAllConstIter(dictionary, coeffsDict_, iter)
	{
		if (!iter().isDict()) continue;

		iter().dict().lookup("EhrrCoeff") >> iEhrrCoeffs_[bandi];

		++bandi;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::wideBandCombustion::
~wideBandCombustion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::wideBandCombustion::ECont
(
	const label bandi
) const
{
	tmp<volScalarField> E = wideBand::ECont(bandi);

	const word& name = combustionModel::combustionPropertiesName;
	E.ref() +=
		iEhrrCoeffs_[bandi]
		* mesh_.lookupObject<combustionModel>(name).Qdot()
		*(iBands_[bandi][1] - iBands_[bandi][0])
		/ totalWaveLength_;

	return E;
}


// ************************************************************************* //