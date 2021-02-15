#include <solitary.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace waveModels
	{
		defineTypeNameAndDebug(solitary, 0);
		addToRunTimeSelectionTable(waveModel, solitary, objectRegistry);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::waveModels::solitary::k(const scalar t) const
{
	return sqrt(0.75*amplitude(t) / pow3(depth()));
}


tnbLib::scalar tnbLib::waveModels::solitary::alpha(const scalar t) const
{
	return amplitude(t) / depth();
}


tnbLib::scalar tnbLib::waveModels::solitary::celerity(const scalar t) const
{
	return sqrt(g()*depth() / (1 - alpha(t)));
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::solitary::parameter
(
	const scalar t,
	const scalarField& x
) const
{
	return k(t)*(x - offset_ - celerity(t)*t);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::solitary::Pi
(
	const scalar t,
	const scalarField& x
) const
{
	const scalar clip = log(great);

	return 1 / sqr(cosh(max(-clip, min(clip, parameter(t, x)))));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveModels::solitary::solitary(const solitary& wave)
	:
	waveModel(wave),
	offset_(wave.offset_),
	depth_(wave.depth_)
{}


tnbLib::waveModels::solitary::solitary
(
	const objectRegistry& db,
	const dictionary& dict
)
	:
	waveModel(db, dict),
	offset_(readScalar(dict.lookup("offset"))),
	depth_(readScalar(dict.lookup("depth")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::waveModels::solitary::~solitary()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::solitary::elevation
(
	const scalar t,
	const scalarField& x
) const
{
	return amplitude(t)*Pi(t, x);
}


tnbLib::tmp<tnbLib::vector2DField> tnbLib::waveModels::solitary::velocity
(
	const scalar t,
	const vector2DField& xz
) const
{
	const scalar A = alpha(t);
	const scalarField Z(max(scalar(0), 1 + xz.component(1) / depth()));
	const scalarField P(Pi(t, xz.component(0)));

	return
		celerity(t)
		*zip
		(
			A / 4
			* (
			(4 + 2 * A - 6 * A*sqr(Z))*P
				+ (-7 * A + 9 * A*sqr(Z))*sqr(P)
				),
			A*Z*depth()*k(t)*tanh(parameter(t, xz.component(0)))
			*(
			(2 + A - A * sqr(Z))*P
				+ (-7 * A + 3 * A*sqr(Z))*sqr(P)
				)
		);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::solitary::pressure
(
	const scalar t,
	const vector2DField& xz
) const
{
	NotImplemented;
	return tmp<scalarField>(nullptr);
}


void tnbLib::waveModels::solitary::write(Ostream& os) const
{
	waveModel::write(os);

	writeEntry(os, "offset", offset_);
	writeEntry(os, "depth", depth_);
}


// ************************************************************************* //