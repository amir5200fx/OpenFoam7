#include <PrghPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class PressureFvPatchScalarField>
tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
PrghPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	PressureFvPatchScalarField(p, iF)
{}


template<class PressureFvPatchScalarField>
tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
PrghPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	PressureFvPatchScalarField(p, iF, dict)
{}


template<class PressureFvPatchScalarField>
tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
PrghPressureFvPatchScalarField
(
	const PrghPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	PressureFvPatchScalarField(ptf, p, iF, mapper)
{}


template<class PressureFvPatchScalarField>
tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
PrghPressureFvPatchScalarField
(
	const PrghPressureFvPatchScalarField& ptf
)
	:
	PressureFvPatchScalarField(ptf)
{}


template<class PressureFvPatchScalarField>
tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
PrghPressureFvPatchScalarField
(
	const PrghPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	PressureFvPatchScalarField(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class PressureFvPatchScalarField>
void tnbLib::PrghPressureFvPatchScalarField<PressureFvPatchScalarField>::
updateCoeffs()
{
	if (PressureFvPatchScalarField::updated())
	{
		return;
	}

	PressureFvPatchScalarField::updateCoeffs();

	const scalarField& rhop = this->patch().template
		lookupPatchField<volScalarField, scalar>
		(
			"rho"
			);

	const uniformDimensionedVectorField& g =
		this->db().template lookupObject<uniformDimensionedVectorField>("g");

	const uniformDimensionedScalarField& hRef =
		this->db().template lookupObject<uniformDimensionedScalarField>("hRef");

	const dimensionedScalar ghRef(-mag(g)*hRef);

	this->operator==
		(
			*this - rhop * ((g.value() & this->patch().Cf()) - ghRef.value())
			);
}


// ************************************************************************* //