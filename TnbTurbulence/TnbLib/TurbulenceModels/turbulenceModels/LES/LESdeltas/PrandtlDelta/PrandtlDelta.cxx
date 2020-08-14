#include <PrandtlDelta.hxx>

#include <wallDist.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(PrandtlDelta, 0);
		addToRunTimeSelectionTable(LESdelta, PrandtlDelta, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::PrandtlDelta::calcDelta()
{
	delta_ = min
	(
		static_cast<const volScalarField&>(geometricDelta_()),
		(kappa_ / Cdelta_)*wallDist::New(turbulenceModel_.mesh()).y()
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::PrandtlDelta::PrandtlDelta
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
			name,
			turbulence,
			dict.optionalSubDict(type() + "Coeffs")
		)
	),
	kappa_(dict.lookupOrDefault<scalar>("kappa", 0.41)),
	Cdelta_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<scalar>
		(
			"Cdelta",
			0.158
			)
	)
{
	calcDelta();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::LESModels::PrandtlDelta::read(const dictionary& dict)
{
	const dictionary& coeffDict(dict.optionalSubDict(type() + "Coeffs"));

	geometricDelta_().read(coeffDict);
	dict.readIfPresent<scalar>("kappa", kappa_);
	coeffDict.readIfPresent<scalar>("Cdelta", Cdelta_);
	calcDelta();
}


void tnbLib::LESModels::PrandtlDelta::correct()
{
	geometricDelta_().correct();

	if (turbulenceModel_.mesh().changing())
	{
		calcDelta();
	}
}


// ************************************************************************* //