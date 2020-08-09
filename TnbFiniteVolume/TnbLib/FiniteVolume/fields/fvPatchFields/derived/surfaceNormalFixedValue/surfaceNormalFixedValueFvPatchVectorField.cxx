#include <surfaceNormalFixedValueFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceNormalFixedValueFvPatchVectorField::
surfaceNormalFixedValueFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	refValue_(p.size())
{}


tnbLib::surfaceNormalFixedValueFvPatchVectorField::
surfaceNormalFixedValueFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict, false),
	refValue_("refValue", dict, p.size())
{
	fvPatchVectorField::operator=(refValue_*patch().nf());
}


tnbLib::surfaceNormalFixedValueFvPatchVectorField::
surfaceNormalFixedValueFvPatchVectorField
(
	const surfaceNormalFixedValueFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(p, iF),
	refValue_(mapper(ptf.refValue_))
{
	// Note: calculate product only on ptf to avoid multiplication on
	// unset values in reconstructPar.
	fvPatchVectorField::operator=
		(
			mapper(ptf.refValue_*ptf.patch().nf())
			);
}


tnbLib::surfaceNormalFixedValueFvPatchVectorField::
surfaceNormalFixedValueFvPatchVectorField
(
	const surfaceNormalFixedValueFvPatchVectorField& pivpvf
)
	:
	fixedValueFvPatchVectorField(pivpvf),
	refValue_(pivpvf.refValue_)
{}


tnbLib::surfaceNormalFixedValueFvPatchVectorField::
surfaceNormalFixedValueFvPatchVectorField
(
	const surfaceNormalFixedValueFvPatchVectorField& pivpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(pivpvf, iF),
	refValue_(pivpvf.refValue_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfaceNormalFixedValueFvPatchVectorField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchVectorField::autoMap(m);
	m(refValue_, refValue_);
}


void tnbLib::surfaceNormalFixedValueFvPatchVectorField::rmap
(
	const fvPatchVectorField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchVectorField::rmap(ptf, addr);

	const surfaceNormalFixedValueFvPatchVectorField& tiptf =
		refCast<const surfaceNormalFixedValueFvPatchVectorField>(ptf);

	refValue_.rmap(tiptf.refValue_, addr);
}


void tnbLib::surfaceNormalFixedValueFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	fvPatchVectorField::operator=(refValue_*patch().nf());
	fvPatchVectorField::updateCoeffs();
}


void tnbLib::surfaceNormalFixedValueFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, "refValue", refValue_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		surfaceNormalFixedValueFvPatchVectorField
	);
}

// ************************************************************************* //