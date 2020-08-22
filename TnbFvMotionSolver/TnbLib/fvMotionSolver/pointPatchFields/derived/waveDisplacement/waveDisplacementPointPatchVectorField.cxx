#include <waveDisplacementPointPatchVectorField.hxx>

#include <pointPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx>
#include <polyMesh.hxx>
#include <OneConstant.hxx>

#include <pointMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveDisplacementPointPatchVectorField::
waveDisplacementPointPatchVectorField
(
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF
)
	:
	fixedValuePointPatchField<vector>(p, iF),
	amplitude_(Zero),
	omega_(0.0),
	waveNumber_(Zero)
{}


tnbLib::waveDisplacementPointPatchVectorField::
waveDisplacementPointPatchVectorField
(
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF,
	const dictionary& dict
)
	:
	fixedValuePointPatchField<vector>(p, iF, dict),
	amplitude_(dict.lookup("amplitude")),
	omega_(readScalar(dict.lookup("omega"))),
	waveNumber_(dict.lookupOrDefault<vector>("waveNumber", Zero)),
	startRamp_
	(
		dict.found("startRamp")
		? Function1<scalar>::New("startRamp", dict)
		: autoPtr<Function1<scalar>>
		(
			new Function1Types::OneConstant<scalar>("startRamp")
			)
	),
	endRamp_
	(
		dict.found("endRamp")
		? Function1<scalar>::New("endRamp", dict)
		: autoPtr<Function1<scalar>>
		(
			new Function1Types::OneConstant<scalar>("endRamp")
			)
	),
	timeRamp_
	(
		dict.found("timeRamp")
		? Function1<scalar>::New("timeRamp", dict)
		: autoPtr<Function1<scalar>>
		(
			new Function1Types::OneConstant<scalar>("timeRamp")
			)
	)
{
	if (!dict.found("value"))
	{
		updateCoeffs();
	}
}


tnbLib::waveDisplacementPointPatchVectorField::
waveDisplacementPointPatchVectorField
(
	const waveDisplacementPointPatchVectorField& ptf,
	const pointPatch& p,
	const DimensionedField<vector, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
	amplitude_(ptf.amplitude_),
	omega_(ptf.omega_),
	waveNumber_(ptf.waveNumber_)
{}


tnbLib::waveDisplacementPointPatchVectorField::
waveDisplacementPointPatchVectorField
(
	const waveDisplacementPointPatchVectorField& ptf,
	const DimensionedField<vector, pointMesh>& iF
)
	:
	fixedValuePointPatchField<vector>(ptf, iF),
	amplitude_(ptf.amplitude_),
	omega_(ptf.omega_),
	waveNumber_(ptf.waveNumber_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::waveDisplacementPointPatchVectorField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const polyMesh& mesh = this->internalField().mesh()();
	const Time& t = mesh.time();

	const scalarField points(waveNumber_ & patch().localPoints());

	const scalar timeRamp = timeRamp_->value(t.value());

	const scalarField startRamp(startRamp_->value(points));

	const scalarField endRamp
	(
		endRamp_->value(points[points.size() - 1] - points)
	);

	Field<vector>::operator=
		(
			timeRamp*startRamp*endRamp*amplitude_*cos(omega_*t.value() - points)
			);

	fixedValuePointPatchField<vector>::updateCoeffs();
}


void tnbLib::waveDisplacementPointPatchVectorField::write(Ostream& os) const
{
	pointPatchField<vector>::write(os);
	writeEntry(os, "amplitude", amplitude_);
	writeEntry(os, "omega", omega_);
	writeEntry(os, "waveNumber", waveNumber_);

	if (!isType<Function1Types::OneConstant<scalar>>(startRamp_()))
	{
		writeEntry(os, startRamp_());
	}

	if (!isType<Function1Types::OneConstant<scalar>>(endRamp_()))
	{
		writeEntry(os, endRamp_());
	}

	if (!isType<Function1Types::OneConstant<scalar>>(timeRamp_()))
	{
		writeEntry(os, timeRamp_());
	}

	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePointPatchTypeField
	(
		pointPatchVectorField,
		waveDisplacementPointPatchVectorField
	);
}

// ************************************************************************* //