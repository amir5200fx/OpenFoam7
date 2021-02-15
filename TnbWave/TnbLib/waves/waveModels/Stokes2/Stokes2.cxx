#include <Stokes2.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace waveModels
	{
		defineTypeNameAndDebug(Stokes2, 0);
		addToRunTimeSelectionTable(waveModel, Stokes2, objectRegistry);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveModels::Stokes2::Stokes2
(
	const objectRegistry& db,
	const dictionary& dict
)
	:
	Airy(db, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::waveModels::Stokes2::~Stokes2()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::Stokes2::elevation
(
	const scalar t,
	const scalarField& x
) const
{
	const scalar kd = k()*depth(), ka = k()*amplitude(t);

	const scalar T = deep() ? 1 : tanh(kd);

	const scalar B22 = (3 / sqr(T) - 1) / T / 4;

	if (debug)
	{
		Info << "B22 = " << B22 << endl;
	}

	return
		Airy::elevation(t, x)
		+ (1 / k())*sqr(ka)*B22*cos(2 * angle(t, x));
}


tnbLib::tmp<tnbLib::vector2DField> tnbLib::waveModels::Stokes2::velocity
(
	const scalar t,
	const vector2DField& xz
) const
{
	const scalar kd = k()*depth(), ka = k()*amplitude(t);

	const scalar A22ByA11 = deep() ? 0 : 0.375 / pow3(sinh(kd));

	if (debug)
	{
		const scalar A11 = 1 / sinh(kd);
		Info << "A22 = " << A22ByA11 * A11 << endl;
	}

	return
		Airy::velocity(t, xz)
		+ celerity()*sqr(ka)*A22ByA11*vi(2, t, xz);
}


// ************************************************************************* //