#include <inclinedFilmNusseltInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <kinematicSingleLayer.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::
inclinedFilmNusseltInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(p, iF),
	GammaMean_(),
	a_(),
	omega_()
{}


tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::
inclinedFilmNusseltInletVelocityFvPatchVectorField
(
	const inclinedFilmNusseltInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchVectorField(ptf, p, iF, mapper),
	GammaMean_(ptf.GammaMean_().clone().ptr()),
	a_(ptf.a_().clone().ptr()),
	omega_(ptf.omega_().clone().ptr())
{}


tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::
inclinedFilmNusseltInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchVectorField(p, iF, dict),
	GammaMean_(Function1<scalar>::New("GammaMean", dict)),
	a_(Function1<scalar>::New("a", dict)),
	omega_(Function1<scalar>::New("omega", dict))
{}


tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::
inclinedFilmNusseltInletVelocityFvPatchVectorField
(
	const inclinedFilmNusseltInletVelocityFvPatchVectorField& fmfrpvf
)
	:
	fixedValueFvPatchVectorField(fmfrpvf),
	GammaMean_(fmfrpvf.GammaMean_().clone().ptr()),
	a_(fmfrpvf.a_().clone().ptr()),
	omega_(fmfrpvf.omega_().clone().ptr())
{}


tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::
inclinedFilmNusseltInletVelocityFvPatchVectorField
(
	const inclinedFilmNusseltInletVelocityFvPatchVectorField& fmfrpvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchVectorField(fmfrpvf, iF),
	GammaMean_(fmfrpvf.GammaMean_().clone().ptr()),
	a_(fmfrpvf.a_().clone().ptr()),
	omega_(fmfrpvf.omega_().clone().ptr())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const label patchi = patch().index();

	// retrieve the film region from the database

	const regionModels::regionModel& region =
		db().time().lookupObject<regionModels::regionModel>
		(
			"surfaceFilmProperties"
			);

	const regionModels::surfaceFilmModels::kinematicSingleLayer& film =
		dynamic_cast
		<
		const regionModels::surfaceFilmModels::kinematicSingleLayer&
		>(region);

	// calculate the vector tangential to the patch
	// note: normal pointing into the domain
	const vectorField n(-patch().nf());

	// TODO: currently re-evaluating the entire gTan field to return this patch
	const scalarField gTan(film.gTan()().boundaryField()[patchi] & n);

	if (patch().size() && (max(mag(gTan)) < small))
	{
		WarningInFunction
			<< "is designed to operate on patches inclined with respect to "
			<< "gravity"
			<< endl;
	}

	const volVectorField& nHat = film.nHat();

	const vectorField nHatp(nHat.boundaryField()[patchi].patchInternalField());

	vectorField nTan(nHatp ^ n);
	nTan /= mag(nTan) + rootVSmall;

	// calculate distance in patch tangential direction

	const vectorField& Cf = patch().Cf();
	scalarField d(nTan & Cf);

	// calculate the wavy film height

	const scalar t = db().time().timeOutputValue();

	const scalar GMean = GammaMean_->value(t);
	const scalar a = a_->value(t);
	const scalar omega = omega_->value(t);

	const scalarField G(GMean + a * sin(omega*constant::mathematical::twoPi*d));

	const volScalarField& mu = film.mu();
	const scalarField mup(mu.boundaryField()[patchi].patchInternalField());

	const volScalarField& rho = film.rho();
	const scalarField rhop(rho.boundaryField()[patchi].patchInternalField());

	const scalarField Re(max(G, scalar(0)) / mup);

	operator==(n*pow(gTan*mup / (3 * rhop), 1.0 / 3.0)*pow(Re, 2.0 / 3.0));

	fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	fvPatchVectorField::write(os);
	writeEntry(os, GammaMean_());
	writeEntry(os, a_());
	writeEntry(os, omega_());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		inclinedFilmNusseltInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //