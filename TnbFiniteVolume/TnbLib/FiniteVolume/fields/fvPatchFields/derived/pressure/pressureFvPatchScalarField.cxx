#include <pressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureFvPatchScalarField::pressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	p_(p.size(), 0.0)
{}


tnbLib::pressureFvPatchScalarField::pressureFvPatchScalarField
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
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(p_);
	}
}


tnbLib::pressureFvPatchScalarField::pressureFvPatchScalarField
(
	const pressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	p_(mapper(ptf.p_))
{}


tnbLib::pressureFvPatchScalarField::pressureFvPatchScalarField
(
	const pressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	p_(ptf.p_)
{}


tnbLib::pressureFvPatchScalarField::pressureFvPatchScalarField
(
	const pressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	p_(ptf.p_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	m(p_, p_);
}


void tnbLib::pressureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const pressureFvPatchScalarField& tiptf =
		refCast<const pressureFvPatchScalarField>(ptf);

	p_.rmap(tiptf.p_, addr);
}


void tnbLib::pressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	operator==(p_);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::pressureFvPatchScalarField::write(Ostream& os) const
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
		pressureFvPatchScalarField
	);
}

// ************************************************************************* //