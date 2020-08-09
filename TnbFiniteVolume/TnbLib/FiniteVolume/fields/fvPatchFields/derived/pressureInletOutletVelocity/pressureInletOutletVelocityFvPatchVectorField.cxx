#include <pressureInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <fvPatchFieldMapper.hxx>  // added by amir
#include <symmTransformField.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pressureInletOutletVelocityFvPatchVectorField::
pressureInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_("phi")
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::pressureInletOutletVelocityFvPatchVectorField::
pressureInletOutletVelocityFvPatchVectorField
(
	const pressureInletOutletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	directionMixedFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_)
{
	if (ptf.tangentialVelocity_.size())
	{
		tangentialVelocity_ = mapper(ptf.tangentialVelocity_);
	}
}


tnbLib::pressureInletOutletVelocityFvPatchVectorField::
pressureInletOutletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	fvPatchVectorField::operator=(vectorField("value", dict, p.size()));

	if (dict.found("tangentialVelocity"))
	{
		setTangentialVelocity
		(
			vectorField("tangentialVelocity", dict, p.size())
		);
	}
	else
	{
		refValue() = Zero;
	}

	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::pressureInletOutletVelocityFvPatchVectorField::
pressureInletOutletVelocityFvPatchVectorField
(
	const pressureInletOutletVelocityFvPatchVectorField& pivpvf
)
	:
	directionMixedFvPatchVectorField(pivpvf),
	phiName_(pivpvf.phiName_),
	tangentialVelocity_(pivpvf.tangentialVelocity_)
{}


tnbLib::pressureInletOutletVelocityFvPatchVectorField::
pressureInletOutletVelocityFvPatchVectorField
(
	const pressureInletOutletVelocityFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(pivpvf, iF),
	phiName_(pivpvf.phiName_),
	tangentialVelocity_(pivpvf.tangentialVelocity_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pressureInletOutletVelocityFvPatchVectorField::
setTangentialVelocity(const vectorField& tangentialVelocity)
{
	tangentialVelocity_ = tangentialVelocity;
	const vectorField n(patch().nf());
	refValue() = tangentialVelocity_ - n * (n & tangentialVelocity_);
}


void tnbLib::pressureInletOutletVelocityFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	directionMixedFvPatchVectorField::autoMap(m);
	if (tangentialVelocity_.size())
	{
		m(tangentialVelocity_, tangentialVelocity_);
	}
}


void tnbLib::pressureInletOutletVelocityFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	directionMixedFvPatchVectorField::rmap(ptf, addr);

	if (tangentialVelocity_.size())
	{
		const pressureInletOutletVelocityFvPatchVectorField& tiptf =
			refCast<const pressureInletOutletVelocityFvPatchVectorField>(ptf);

		tangentialVelocity_.rmap(tiptf.tangentialVelocity_, addr);
	}
}


void tnbLib::pressureInletOutletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvsPatchField<scalar>& phip =
		patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);

	valueFraction() = neg(phip)*(I - sqr(patch().nf()));

	directionMixedFvPatchVectorField::updateCoeffs();
	directionMixedFvPatchVectorField::evaluate();
}


void tnbLib::pressureInletOutletVelocityFvPatchVectorField::write
(
	Ostream& os
)
const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	if (tangentialVelocity_.size())
	{
		writeEntry(os, "tangentialVelocity", tangentialVelocity_);
	}
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pressureInletOutletVelocityFvPatchVectorField::operator=
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
		pressureInletOutletVelocityFvPatchVectorField
	);
}

// ************************************************************************* //