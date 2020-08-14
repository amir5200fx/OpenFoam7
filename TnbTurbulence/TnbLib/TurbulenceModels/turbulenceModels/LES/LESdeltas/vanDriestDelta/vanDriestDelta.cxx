#include <vanDriestDelta.hxx>

#include <wallFvPatch.hxx>
#include <wallDistData.hxx>
#include <wallPointYPlus.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(vanDriestDelta, 0);
		addToRunTimeSelectionTable(LESdelta, vanDriestDelta, dictionary);
	}
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::vanDriestDelta::calcDelta()
{
	const fvMesh& mesh = turbulenceModel_.mesh();

	const volVectorField& U = turbulenceModel_.U();
	const tmp<volScalarField> tnu = turbulenceModel_.nu();
	const volScalarField& nu = tnu();
	tmp<volScalarField> nuSgs = turbulenceModel_.nut();

	volScalarField ystar
	(
		IOobject
		(
			"ystar",
			mesh.time().constant(),
			mesh
		),
		mesh,
		dimensionedScalar(dimLength, great)
	);

	const fvPatchList& patches = mesh.boundary();
	volScalarField::Boundary& ystarBf = ystar.boundaryFieldRef();

	forAll(patches, patchi)
	{
		if (isA<wallFvPatch>(patches[patchi]))
		{
			const fvPatchVectorField& Uw = U.boundaryField()[patchi];
			const scalarField& nuw = nu.boundaryField()[patchi];
			const scalarField& nuSgsw = nuSgs().boundaryField()[patchi];

			ystarBf[patchi] =
				nuw / sqrt((nuw + nuSgsw)*mag(Uw.snGrad()) + vSmall);
		}
	}

	scalar cutOff = wallPointYPlus::yPlusCutOff;
	wallPointYPlus::yPlusCutOff = 500;
	wallDistData<wallPointYPlus> y(mesh, ystar);
	wallPointYPlus::yPlusCutOff = cutOff;

	delta_ = min
	(
		static_cast<const volScalarField&>(geometricDelta_()),
		(kappa_ / Cdelta_)*((scalar(1) + small) - exp(-y / ystar / Aplus_))*y
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::vanDriestDelta::vanDriestDelta
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict
)
	:
	LESdelta(name, turbulence),
	geometricDelta_
	(
		LESdelta::New
		(
			IOobject::groupName("geometricDelta", turbulence.U().group()),
			turbulence,
			dict.optionalSubDict(type() + "Coeffs")
		)
	),
	kappa_(dict.lookupOrDefault<scalar>("kappa", 0.41)),
	Aplus_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<scalar>
		(
			"Aplus",
			26.0
			)
	),
	Cdelta_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<scalar>
		(
			"Cdelta",
			0.158
			)
	),
	calcInterval_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<label>
		(
			"calcInterval",
			1
			)
	)
{
	delta_ = geometricDelta_();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::LESModels::vanDriestDelta::read(const dictionary& dict)
{
	const dictionary& coeffsDict(dict.optionalSubDict(type() + "Coeffs"));

	geometricDelta_().read(coeffsDict);
	dict.readIfPresent<scalar>("kappa", kappa_);
	coeffsDict.readIfPresent<scalar>("Aplus", Aplus_);
	coeffsDict.readIfPresent<scalar>("Cdelta", Cdelta_);
	coeffsDict.readIfPresent<label>("calcInterval", calcInterval_);

	calcDelta();
}


void tnbLib::LESModels::vanDriestDelta::correct()
{
	if (turbulenceModel_.mesh().time().timeIndex() % calcInterval_ == 0)
	{
		geometricDelta_().correct();
		calcDelta();
	}
}


// ************************************************************************* //