#include <binary.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(binary, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				binary,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::binary::binary
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	absorptionEmissionModel(dict, mesh),
	coeffsDict_(dict.optionalSubDict(typeName + "Coeffs")),
	model1_
	(
		absorptionEmissionModel::New(coeffsDict_.subDict("model1"), mesh)
	),
	model2_
	(
		absorptionEmissionModel::New(coeffsDict_.subDict("model2"), mesh)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::binary::~binary()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::aCont
(
	const label bandI
) const
{
	return model1_->aCont(bandI) + model2_->aCont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::aDisp
(
	const label bandI
) const
{
	return model1_->aDisp(bandI) + model2_->aDisp(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::eCont
(
	const label bandI
) const
{
	return model1_->eCont(bandI) + model2_->eCont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::eDisp
(
	const label bandI
) const
{
	return model1_->eDisp(bandI) + model2_->eDisp(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::ECont
(
	const label bandI
) const
{
	return model1_->ECont(bandI) + model2_->ECont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::binary::EDisp
(
	const label bandI
) const
{
	return model1_->EDisp(bandI) + model2_->EDisp(bandI);
}


// ************************************************************************* //