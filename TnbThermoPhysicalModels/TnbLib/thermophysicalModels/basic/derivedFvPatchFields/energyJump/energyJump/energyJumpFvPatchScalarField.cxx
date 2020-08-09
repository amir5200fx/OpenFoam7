#include <energyJumpFvPatchScalarField.hxx>

#include <fixedJumpFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::energyJumpFvPatchScalarField::energyJumpFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpFvPatchField<scalar>(p, iF)
{}


tnbLib::energyJumpFvPatchScalarField::energyJumpFvPatchScalarField
(
	const energyJumpFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedJumpFvPatchField<scalar>(ptf, p, iF, mapper)
{}


tnbLib::energyJumpFvPatchScalarField::energyJumpFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedJumpFvPatchField<scalar>(p, iF)
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
		evaluate(Pstream::commsTypes::blocking);
	}
}


tnbLib::energyJumpFvPatchScalarField::energyJumpFvPatchScalarField
(
	const energyJumpFvPatchScalarField& ptf
)
	:
	fixedJumpFvPatchField<scalar>(ptf)
{}


tnbLib::energyJumpFvPatchScalarField::energyJumpFvPatchScalarField
(
	const energyJumpFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpFvPatchField<scalar>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::energyJumpFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	if (this->cyclicPatch().owner())
	{
		const basicThermo& thermo = basicThermo::lookupThermo(*this);
		label patchID = patch().index();

		const scalarField& pp = thermo.p().boundaryField()[patchID];
		const fixedJumpFvPatchScalarField& TbPatch =
			refCast<const fixedJumpFvPatchScalarField>
			(
				thermo.T().boundaryField()[patchID]
				);

		fixedJumpFvPatchScalarField& Tbp =
			const_cast<fixedJumpFvPatchScalarField&>(TbPatch);

		// force update of jump
		Tbp.updateCoeffs();

		const labelUList& faceCells = this->patch().faceCells();

		jump_ = thermo.he(pp, Tbp.jump(), faceCells);
	}

	fixedJumpFvPatchField<scalar>::updateCoeffs();
}


void tnbLib::energyJumpFvPatchScalarField::write(Ostream& os) const
{
	fixedJumpFvPatchField<scalar>::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		energyJumpFvPatchScalarField
	);
}

// ************************************************************************* //