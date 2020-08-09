#include <pressureDirectedInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureDirectedInletVelocityFvPatchVectorField::
pressureDirectedInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho"),
	inletDir_(p.size())
{}


tnbLib::pressureDirectedInletVelocityFvPatchVectorField::
pressureDirectedInletVelocityFvPatchVectorField
(
	const pressureDirectedInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	inletDir_(mapper(ptf.inletDir_))
{}


tnbLib::pressureDirectedInletVelocityFvPatchVectorField::
pressureDirectedInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	inletDir_("inletDirection", dict, p.size())
{}


tnbLib::pressureDirectedInletVelocityFvPatchVectorField::
pressureDirectedInletVelocityFvPatchVectorField
(
	const pressureDirectedInletVelocityFvPatchVectorField& pivpvf
)
	:
	fixedValueFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_),
	inletDir_(pivpvf.inletDir_)
{}


tnbLib::pressureDirectedInletVelocityFvPatchVectorField::
pressureDirectedInletVelocityFvPatchVectorField
(
	const pressureDirectedInletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_),
	inletDir_(pivpvf.inletDir_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureDirectedInletVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchVectorField::autoMap(m);
	m(inletDir_, inletDir_);
}


void tnbLib::pressureDirectedInletVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchVectorField::rmap(ptf, addr);

	const pressureDirectedInletVelocityFvPatchVectorField& tiptf =
		refCast<const pressureDirectedInletVelocityFvPatchVectorField>(ptf);

	inletDir_.rmap(tiptf.inletDir_, addr);
}


void tnbLib::pressureDirectedInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	const fvsPatchField<scalar>& phip =
		patch().patchField<surfaceScalarField, scalar>(phi);

	tmp<vectorField> n = patch().nf();
	tmp<scalarField> ndmagS = (n & inletDir_)*patch().magSf();

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		operator==(inletDir_*phip / ndmagS);
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		operator==(inletDir_*phip / (rhop*ndmagS));
	}
	else
	{
		FatalErrorInFunction
			<< "dimensions of phi are not correct"
			<< "\n    on patch " << this->patch().name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalError);
	}

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::pressureDirectedInletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "inletDirection", inletDir_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pressureDirectedInletVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	fvPatchField<vector>::operator=(inletDir_*(inletDir_ & pvf));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		pressureDirectedInletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //