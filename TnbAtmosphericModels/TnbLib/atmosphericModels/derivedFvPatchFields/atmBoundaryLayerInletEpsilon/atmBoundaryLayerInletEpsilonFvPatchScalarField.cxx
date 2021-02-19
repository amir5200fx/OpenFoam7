#include <atmBoundaryLayerInletEpsilonFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	atmBoundaryLayerInletEpsilonFvPatchScalarField::
		atmBoundaryLayerInletEpsilonFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(p, iF),
		atmBoundaryLayer()
	{}


	atmBoundaryLayerInletEpsilonFvPatchScalarField::
		atmBoundaryLayerInletEpsilonFvPatchScalarField
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

		refValue() = epsilon(patch().Cf());
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


	atmBoundaryLayerInletEpsilonFvPatchScalarField::
		atmBoundaryLayerInletEpsilonFvPatchScalarField
		(
			const atmBoundaryLayerInletEpsilonFvPatchScalarField& psf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		inletOutletFvPatchScalarField(psf, p, iF, mapper),
		atmBoundaryLayer(psf, mapper)
	{}


	atmBoundaryLayerInletEpsilonFvPatchScalarField::
		atmBoundaryLayerInletEpsilonFvPatchScalarField
		(
			const atmBoundaryLayerInletEpsilonFvPatchScalarField& psf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		inletOutletFvPatchScalarField(psf, iF),
		atmBoundaryLayer(psf)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void atmBoundaryLayerInletEpsilonFvPatchScalarField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		inletOutletFvPatchScalarField::autoMap(m);
		atmBoundaryLayer::autoMap(m);
	}


	void atmBoundaryLayerInletEpsilonFvPatchScalarField::rmap
	(
		const fvPatchScalarField& psf,
		const labelList& addr
	)
	{
		inletOutletFvPatchScalarField::rmap(psf, addr);

		const atmBoundaryLayerInletEpsilonFvPatchScalarField& blpsf =
			refCast<const atmBoundaryLayerInletEpsilonFvPatchScalarField>(psf);

		atmBoundaryLayer::rmap(blpsf, addr);
	}


	void atmBoundaryLayerInletEpsilonFvPatchScalarField::write(Ostream& os) const
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
		atmBoundaryLayerInletEpsilonFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //