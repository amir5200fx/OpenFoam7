#include <pressureDirectedInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::
pressureDirectedInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(p, iF),
	phiName_("phi"),
	rhoName_("rho"),
	inletDir_(p.size())
{
	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = 0.0;
}


tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::
pressureDirectedInletOutletVelocityFvPatchVectorField
(
	const pressureDirectedInletOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	inletDir_(mapper(ptf.inletDir_))
{}


tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::
pressureDirectedInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	inletDir_("inletDirection", dict, p.size())
{
	fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = 0.0;
}


tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::
pressureDirectedInletOutletVelocityFvPatchVectorField
(
	const pressureDirectedInletOutletVelocityFvPatchVectorField& pivpvf
)
	:
	mixedFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_),
	inletDir_(pivpvf.inletDir_)
{}


tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::
pressureDirectedInletOutletVelocityFvPatchVectorField
(
	const pressureDirectedInletOutletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	rhoName_(pivpvf.rhoName_),
	inletDir_(pivpvf.inletDir_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	mixedFvPatchVectorField::autoMap(m);
	m(inletDir_, inletDir_);
}


void tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	mixedFvPatchVectorField::rmap(ptf, addr);

	const pressureDirectedInletOutletVelocityFvPatchVectorField& tiptf =
		refCast<const pressureDirectedInletOutletVelocityFvPatchVectorField>
		(ptf);

	inletDir_.rmap(tiptf.inletDir_, addr);
}


void tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::updateCoeffs()
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
		refValue() = inletDir_ * phip / ndmagS;
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			patch().lookupPatchField<volScalarField, scalar>(rhoName_);

		refValue() = inletDir_ * phip / (rhop*ndmagS);
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

	valueFraction() = 1.0 - pos0(phip);

	mixedFvPatchVectorField::updateCoeffs();
}


void tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::write
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

void tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	fvPatchField<vector>::operator=
		(
			valueFraction()*(inletDir_*(inletDir_ & pvf))
			+ (1 - valueFraction())*pvf
			);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		pressureDirectedInletOutletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //