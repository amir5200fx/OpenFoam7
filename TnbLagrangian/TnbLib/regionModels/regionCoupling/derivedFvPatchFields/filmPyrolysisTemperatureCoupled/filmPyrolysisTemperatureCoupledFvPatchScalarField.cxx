#include <filmPyrolysisTemperatureCoupledFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>
#include <pyrolysisModel.hxx>
#include <surfaceFilmRegionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::
filmPyrolysisTemperatureCoupledFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	filmRegionName_("surfaceFilmProperties"),
	pyrolysisRegionName_("pyrolysisProperties"),
	phiName_("phi"),
	rhoName_("rho")
{}


tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::
filmPyrolysisTemperatureCoupledFvPatchScalarField
(
	const filmPyrolysisTemperatureCoupledFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	filmRegionName_(ptf.filmRegionName_),
	pyrolysisRegionName_(ptf.pyrolysisRegionName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_)
{}


tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::
filmPyrolysisTemperatureCoupledFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict),
	filmRegionName_
	(
		dict.lookupOrDefault<word>("filmRegion", "surfaceFilmProperties")
	),
	pyrolysisRegionName_
	(
		dict.lookupOrDefault<word>("pyrolysisRegion", "pyrolysisProperties")
	),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
{}


tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::
filmPyrolysisTemperatureCoupledFvPatchScalarField
(
	const filmPyrolysisTemperatureCoupledFvPatchScalarField& fptpsf
)
	:
	fixedValueFvPatchScalarField(fptpsf),
	filmRegionName_(fptpsf.filmRegionName_),
	pyrolysisRegionName_(fptpsf.pyrolysisRegionName_),
	phiName_(fptpsf.phiName_),
	rhoName_(fptpsf.rhoName_)
{}


tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::
filmPyrolysisTemperatureCoupledFvPatchScalarField
(
	const filmPyrolysisTemperatureCoupledFvPatchScalarField& fptpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(fptpsf, iF),
	filmRegionName_(fptpsf.filmRegionName_),
	pyrolysisRegionName_(fptpsf.pyrolysisRegionName_),
	phiName_(fptpsf.phiName_),
	rhoName_(fptpsf.rhoName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	typedef regionModels::surfaceFilmModels::surfaceFilmRegionModel
		filmModelType;

	typedef regionModels::pyrolysisModels::pyrolysisModel pyrModelType;

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	bool filmOk = db().time().foundObject<filmModelType>(filmRegionName_);


	bool pyrOk = db().time().foundObject<pyrModelType>(pyrolysisRegionName_);

	if (!filmOk || !pyrOk)
	{
		// Do nothing on construction - film model doesn't exist yet
		return;
	}

	scalarField& Tp = *this;

	const label patchi = patch().index();

	// Retrieve film model
	const filmModelType& filmModel =
		db().time().lookupObject<filmModelType>(filmRegionName_);

	const label filmPatchi = filmModel.regionPatchID(patchi);

	scalarField alphaFilm = filmModel.alpha().boundaryField()[filmPatchi];
	filmModel.toPrimary(filmPatchi, alphaFilm);

	scalarField TFilm = filmModel.Ts().boundaryField()[filmPatchi];
	filmModel.toPrimary(filmPatchi, TFilm);

	// Retrieve pyrolysis model
	const pyrModelType& pyrModel =
		db().time().lookupObject<pyrModelType>(pyrolysisRegionName_);

	const label pyrPatchi = pyrModel.regionPatchID(patchi);

	scalarField TPyr = pyrModel.T().boundaryField()[pyrPatchi];
	pyrModel.toPrimary(pyrPatchi, TPyr);


	// Evaluate temperature
	Tp = alphaFilm * TFilm + (1.0 - alphaFilm)*TPyr;

	// Restore tag
	UPstream::msgType() = oldTag;

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::filmPyrolysisTemperatureCoupledFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>
		(
			os,
			"filmRegion",
			"surfaceFilmProperties",
			filmRegionName_
			);
	writeEntryIfDifferent<word>
		(
			os,
			"pyrolysisRegion",
			"pyrolysisProperties",
			pyrolysisRegionName_
			);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		filmPyrolysisTemperatureCoupledFvPatchScalarField
	);
}


// ************************************************************************* //