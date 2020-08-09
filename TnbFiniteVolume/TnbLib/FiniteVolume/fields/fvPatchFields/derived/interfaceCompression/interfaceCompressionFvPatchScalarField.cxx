#include <interfaceCompressionFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::interfaceCompressionFvPatchScalarField::
interfaceCompressionFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF)
{}


tnbLib::interfaceCompressionFvPatchScalarField::
interfaceCompressionFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF)
{
	evaluate();
}


tnbLib::interfaceCompressionFvPatchScalarField::
interfaceCompressionFvPatchScalarField
(
	const interfaceCompressionFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::interfaceCompressionFvPatchScalarField::
interfaceCompressionFvPatchScalarField
(
	const interfaceCompressionFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf)
{}


tnbLib::interfaceCompressionFvPatchScalarField::
interfaceCompressionFvPatchScalarField
(
	const interfaceCompressionFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::interfaceCompressionFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	operator==(pos0(this->patchInternalField() - 0.5));

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::interfaceCompressionFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		interfaceCompressionFvPatchScalarField
	);
}

// ************************************************************************* //