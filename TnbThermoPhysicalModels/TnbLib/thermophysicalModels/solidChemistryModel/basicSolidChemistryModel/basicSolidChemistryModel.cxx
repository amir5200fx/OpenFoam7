#include <basicSolidChemistryModel.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(basicSolidChemistryModel, 0);
	defineRunTimeSelectionTable(basicSolidChemistryModel, thermo);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicSolidChemistryModel::basicSolidChemistryModel
(
	solidReactionThermo& thermo
)
	:
	basicChemistryModel(thermo),
	solidThermo_(thermo)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::basicSolidChemistryModel::~basicSolidChemistryModel()
{}


const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::basicSolidChemistryModel::RR(const label i) const
{
	NotImplemented;
	return (volScalarField::Internal::null());
}


tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::basicSolidChemistryModel::RR(const label i)
{
	NotImplemented;

	return dynamic_cast<volScalarField::Internal&>
		(
			const_cast<volScalarField::Internal&>
			(
				volScalarField::Internal::null()
				)
			);
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::basicSolidChemistryModel::calculateRR
(
	const label reactionI,
	const label speciei
) const
{
	NotImplemented;

	return dynamic_cast<tmp<volScalarField::Internal>&>
		(
			const_cast<volScalarField::Internal&>
			(
				volScalarField::Internal::null()
				)
			);
}


// ************************************************************************* //