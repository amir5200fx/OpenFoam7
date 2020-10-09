#include <fixedRhoFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedRhoFvPatchScalarField::fixedRhoFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	pName_("p"),
	psiName_("thermo:psi")
{}


tnbLib::fixedRhoFvPatchScalarField::fixedRhoFvPatchScalarField
(
	const fixedRhoFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	pName_(ptf.pName_),
	psiName_(ptf.psiName_)
{}


tnbLib::fixedRhoFvPatchScalarField::fixedRhoFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict),
	pName_(dict.lookupOrDefault<word>("p", "p")),
	psiName_(dict.lookupOrDefault<word>("psi", "thermo:psi"))
{}


tnbLib::fixedRhoFvPatchScalarField::fixedRhoFvPatchScalarField
(
	const fixedRhoFvPatchScalarField& frpsf
)
	:
	fixedValueFvPatchScalarField(frpsf),
	pName_(frpsf.pName_),
	psiName_(frpsf.psiName_)
{}


tnbLib::fixedRhoFvPatchScalarField::fixedRhoFvPatchScalarField
(
	const fixedRhoFvPatchScalarField& frpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(frpsf, iF),
	pName_(frpsf.pName_),
	psiName_(frpsf.psiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedRhoFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchField<scalar>& psip =
		patch().lookupPatchField<volScalarField, scalar>(psiName_);

	const fvPatchField<scalar>& pp =
		patch().lookupPatchField<volScalarField, scalar>(pName_);

	operator==(psip*pp);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::fixedRhoFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);

	writeEntryIfDifferent<word>(os, "p", "p", this->pName_);
	writeEntryIfDifferent<word>(os, "psi", "thermo:psi", psiName_);
	writeEntry(os, "value", *this);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedRhoFvPatchScalarField
	);
}

// ************************************************************************* //