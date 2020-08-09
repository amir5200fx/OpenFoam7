#include <alphaFixedPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::alphaFixedPressureFvPatchScalarField::
alphaFixedPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	p_(p.size(), 0.0)
{}


tnbLib::alphaFixedPressureFvPatchScalarField::
alphaFixedPressureFvPatchScalarField
(
	const alphaFixedPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	p_(mapper(ptf.p_))
{}


tnbLib::alphaFixedPressureFvPatchScalarField::
alphaFixedPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict, false),
	p_("p", dict, p.size())
{
	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(p_);
	}
}


tnbLib::alphaFixedPressureFvPatchScalarField::
alphaFixedPressureFvPatchScalarField
(
	const alphaFixedPressureFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf),
	p_(tppsf.p_)
{}


tnbLib::alphaFixedPressureFvPatchScalarField::
alphaFixedPressureFvPatchScalarField
(
	const alphaFixedPressureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF),
	p_(tppsf.p_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::alphaFixedPressureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
	m(p_, p_);
}


void tnbLib::alphaFixedPressureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const alphaFixedPressureFvPatchScalarField& tiptf =
		refCast<const alphaFixedPressureFvPatchScalarField>(ptf);

	p_.rmap(tiptf.p_, addr);
}


void tnbLib::alphaFixedPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const uniformDimensionedVectorField& g =
		db().lookupObject<uniformDimensionedVectorField>("g");

	const fvPatchField<scalar>& rho =
		patch().lookupPatchField<volScalarField, scalar>("rho");

	operator==(p_ - rho * (g.value() & patch().Cf()));

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::alphaFixedPressureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntry(os, "p", p_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		alphaFixedPressureFvPatchScalarField
	);
}

// ************************************************************************* //