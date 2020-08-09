#include <energyJumpAMIFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fixedJumpAMIFvPatchFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::energyJumpAMIFvPatchScalarField::energyJumpAMIFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpAMIFvPatchField<scalar>(p, iF)
{}


tnbLib::energyJumpAMIFvPatchScalarField::energyJumpAMIFvPatchScalarField
(
	const energyJumpAMIFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedJumpAMIFvPatchField<scalar>(ptf, p, iF, mapper)
{}


tnbLib::energyJumpAMIFvPatchScalarField::energyJumpAMIFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedJumpAMIFvPatchField<scalar>(p, iF)
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


tnbLib::energyJumpAMIFvPatchScalarField::energyJumpAMIFvPatchScalarField
(
	const energyJumpAMIFvPatchScalarField& ptf
)
	:
	fixedJumpAMIFvPatchField<scalar>(ptf)
{}


tnbLib::energyJumpAMIFvPatchScalarField::energyJumpAMIFvPatchScalarField
(
	const energyJumpAMIFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedJumpAMIFvPatchField<scalar>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::energyJumpAMIFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	if (this->cyclicAMIPatch().owner())
	{
		const basicThermo& thermo = basicThermo::lookupThermo(*this);
		label patchID = patch().index();

		const scalarField& pp = thermo.p().boundaryField()[patchID];
		const fixedJumpAMIFvPatchScalarField& TbPatch =
			refCast<const fixedJumpAMIFvPatchScalarField>
			(
				thermo.T().boundaryField()[patchID]
				);

		fixedJumpAMIFvPatchScalarField& Tbp =
			const_cast<fixedJumpAMIFvPatchScalarField&>(TbPatch);

		// force update of jump
		Tbp.updateCoeffs();

		const labelUList& faceCells = this->patch().faceCells();

		jump_ = thermo.he(pp, Tbp.jump(), faceCells);
	}

	fixedJumpAMIFvPatchField<scalar>::updateCoeffs();
}


void tnbLib::energyJumpAMIFvPatchScalarField::write(Ostream& os) const
{
	fixedJumpAMIFvPatchField<scalar>::write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		energyJumpAMIFvPatchScalarField
	);
}

// ************************************************************************* //