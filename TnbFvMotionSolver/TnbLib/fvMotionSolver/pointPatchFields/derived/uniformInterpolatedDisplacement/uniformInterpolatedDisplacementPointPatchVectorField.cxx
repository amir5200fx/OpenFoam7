#include <uniformInterpolatedDisplacementPointPatchVectorField.hxx>

#include <pointFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::
uniformInterpolatedDisplacementPointPatchVectorField
(
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF
)
	:
	fixedValuePointPatchField<vector>(p, iF)
{}


tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::
uniformInterpolatedDisplacementPointPatchVectorField
(
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF,
	const dictionary& dict
)
	:
	fixedValuePointPatchField<vector>(p, iF, dict),
	pointInterpolator_
	(
		new dynamicMeshPointInterpolator(iF.mesh().mesh(), dict)
	)
{
	if (!dict.found("value"))
	{
		updateCoeffs();
	}
}


tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::
uniformInterpolatedDisplacementPointPatchVectorField
(
	const uniformInterpolatedDisplacementPointPatchVectorField& ptf,
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	fixedValuePointPatchField<vector>(ptf, p, iF, mapper)
{}


tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::
uniformInterpolatedDisplacementPointPatchVectorField
(
	const uniformInterpolatedDisplacementPointPatchVectorField& ptf,
	const DimensionedField<vector, pointMesh>& iF
)
	:
	fixedValuePointPatchField<vector>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Extract back from the internal field
	this->operator==
		(
			patchInternalField(pointInterpolator_->curPointField()())
			);

	fixedValuePointPatchField<vector>::updateCoeffs();
}


void tnbLib::uniformInterpolatedDisplacementPointPatchVectorField::write
(
	Ostream& os
)
const
{
	pointPatchField<vector>::write(os);
	pointInterpolator_->write(os);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePointPatchTypeField
	(
		pointPatchVectorField,
		uniformInterpolatedDisplacementPointPatchVectorField
	);
}

// ************************************************************************* //