#include <atmBoundaryLayerInletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	atmBoundaryLayerInletVelocityFvPatchVectorField::
		atmBoundaryLayerInletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		inletOutletFvPatchVectorField(p, iF),
		atmBoundaryLayer()
	{}


	atmBoundaryLayerInletVelocityFvPatchVectorField::
		atmBoundaryLayerInletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		inletOutletFvPatchVectorField(p, iF),
		atmBoundaryLayer(patch().Cf(), dict)
	{
		phiName_ = dict.lookupOrDefault<word>("phi", "phi");

		refValue() = U(patch().Cf());
		refGrad() = Zero;
		valueFraction() = 1;

		if (dict.found("value"))
		{
			vectorField::operator=(vectorField("value", dict, p.size()));
		}
		else
		{
			vectorField::operator=(refValue());
		}
	}


	atmBoundaryLayerInletVelocityFvPatchVectorField::
		atmBoundaryLayerInletVelocityFvPatchVectorField
		(
			const atmBoundaryLayerInletVelocityFvPatchVectorField& pvf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		inletOutletFvPatchVectorField(pvf, p, iF, mapper),
		atmBoundaryLayer(pvf, mapper)
	{}


	atmBoundaryLayerInletVelocityFvPatchVectorField::
		atmBoundaryLayerInletVelocityFvPatchVectorField
		(
			const atmBoundaryLayerInletVelocityFvPatchVectorField& pvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		inletOutletFvPatchVectorField(pvf, iF),
		atmBoundaryLayer(pvf)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void atmBoundaryLayerInletVelocityFvPatchVectorField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		inletOutletFvPatchVectorField::autoMap(m);
		atmBoundaryLayer::autoMap(m);
	}


	void atmBoundaryLayerInletVelocityFvPatchVectorField::rmap
	(
		const fvPatchVectorField& pvf,
		const labelList& addr
	)
	{
		inletOutletFvPatchVectorField::rmap(pvf, addr);

		const atmBoundaryLayerInletVelocityFvPatchVectorField& blpvf =
			refCast<const atmBoundaryLayerInletVelocityFvPatchVectorField>(pvf);

		atmBoundaryLayer::rmap(blpvf, addr);
	}


	void atmBoundaryLayerInletVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		atmBoundaryLayer::write(os);
		writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		atmBoundaryLayerInletVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //