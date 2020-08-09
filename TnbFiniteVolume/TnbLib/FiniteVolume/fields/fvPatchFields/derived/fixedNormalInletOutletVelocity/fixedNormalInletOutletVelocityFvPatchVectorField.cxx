#include <fixedNormalInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <symmTransformField.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::
fixedNormalInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_("phi"),
	fixTangentialInflow_(true),
	normalVelocity_
	(
		fvPatchVectorField::New("fixedValue", p, iF)
	)
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::
fixedNormalInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	fixTangentialInflow_(dict.lookup("fixTangentialInflow")),
	normalVelocity_
	(
		fvPatchVectorField::New(p, iF, dict.subDict("normalVelocity"))
	)
{
	fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
	refValue() = normalVelocity();
	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::
fixedNormalInletOutletVelocityFvPatchVectorField
(
	const fixedNormalInletOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	directionMixedFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	fixTangentialInflow_(ptf.fixTangentialInflow_),
	normalVelocity_
	(
		fvPatchVectorField::New(ptf.normalVelocity(), p, iF, mapper)
	)
{}


tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::
fixedNormalInletOutletVelocityFvPatchVectorField
(
	const fixedNormalInletOutletVelocityFvPatchVectorField& pivpvf
)
	:
	directionMixedFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	fixTangentialInflow_(pivpvf.fixTangentialInflow_),
	normalVelocity_(pivpvf.normalVelocity().clone())
{}


tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::
fixedNormalInletOutletVelocityFvPatchVectorField
(
	const fixedNormalInletOutletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	fixTangentialInflow_(pivpvf.fixTangentialInflow_),
	normalVelocity_(pivpvf.normalVelocity().clone())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	directionMixedFvPatchVectorField::autoMap(m);
	normalVelocity_->autoMap(m);
}


void tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	directionMixedFvPatchVectorField::rmap(ptf, addr);

	const fixedNormalInletOutletVelocityFvPatchVectorField& fniovptf =
		refCast<const fixedNormalInletOutletVelocityFvPatchVectorField>(ptf);

	normalVelocity_->rmap(fniovptf.normalVelocity(), addr);
}


void tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	normalVelocity_->evaluate();
	refValue() = normalVelocity();

	valueFraction() = sqr(patch().nf());

	if (fixTangentialInflow_)
	{
		const fvsPatchField<scalar>& phip =
			patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

		valueFraction() += neg(phip)*(I - valueFraction());
	}

	directionMixedFvPatchVectorField::updateCoeffs();
	directionMixedFvPatchVectorField::evaluate();
}


void tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::write
(
	Ostream& os
)
const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntry(os, "fixTangentialInflow", fixTangentialInflow_);
	os.writeKeyword("normalVelocity")
		<< nl << indent << token::BEGIN_BLOCK << nl << incrIndent;
	normalVelocity_->write(os);
	os << decrIndent << indent << token::END_BLOCK << endl;
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::fixedNormalInletOutletVelocityFvPatchVectorField::operator=
(
	const fvPatchField<vector>& pvf
	)
{
	tmp<vectorField> normalValue = transform(valueFraction(), refValue());
	tmp<vectorField> transformGradValue = transform(I - valueFraction(), pvf);
	fvPatchField<vector>::operator=(normalValue + transformGradValue);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		fixedNormalInletOutletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //