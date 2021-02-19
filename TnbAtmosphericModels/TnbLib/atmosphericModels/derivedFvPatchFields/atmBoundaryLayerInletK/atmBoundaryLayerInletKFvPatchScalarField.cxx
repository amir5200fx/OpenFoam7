#include <atmBoundaryLayerInletKFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	atmBoundaryLayerInletKFvPatchScalarField::
		atmBoundaryLayerInletKFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(p, iF),
		atmBoundaryLayer()
	{}


	atmBoundaryLayerInletKFvPatchScalarField::
		atmBoundaryLayerInletKFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		inletOutletFvPatchScalarField(p, iF),
		atmBoundaryLayer(patch().Cf(), dict)
	{
		phiName_ = dict.lookupOrDefault<word>("phi", "phi");

		refValue() = k(patch().Cf());
		refGrad() = 0;
		valueFraction() = 1;

		if (dict.found("value"))
		{
			scalarField::operator=(scalarField("value", dict, p.size()));
		}
		else
		{
			scalarField::operator=(refValue());
		}
	}


	atmBoundaryLayerInletKFvPatchScalarField::
		atmBoundaryLayerInletKFvPatchScalarField
		(
			const atmBoundaryLayerInletKFvPatchScalarField& psf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		inletOutletFvPatchScalarField(psf, p, iF, mapper),
		atmBoundaryLayer(psf, mapper)
	{}


	atmBoundaryLayerInletKFvPatchScalarField::
		atmBoundaryLayerInletKFvPatchScalarField
		(
			const atmBoundaryLayerInletKFvPatchScalarField& psf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(psf, iF),
		atmBoundaryLayer(psf)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void atmBoundaryLayerInletKFvPatchScalarField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		inletOutletFvPatchScalarField::autoMap(m);
		atmBoundaryLayer::autoMap(m);
	}


	void atmBoundaryLayerInletKFvPatchScalarField::rmap
	(
		const fvPatchScalarField& psf,
		const labelList& addr
	)
	{
		inletOutletFvPatchScalarField::rmap(psf, addr);

		const atmBoundaryLayerInletKFvPatchScalarField& blpsf =
			refCast<const atmBoundaryLayerInletKFvPatchScalarField>(psf);

		atmBoundaryLayer::rmap(blpsf, addr);
	}


	void atmBoundaryLayerInletKFvPatchScalarField::write(Ostream& os) const
	{
		fvPatchScalarField::write(os);
		atmBoundaryLayer::write(os);
		writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		atmBoundaryLayerInletKFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //