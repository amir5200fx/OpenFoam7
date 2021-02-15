#include <Airy.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace waveModels
	{
		defineTypeNameAndDebug(Airy, 0);
		addToRunTimeSelectionTable(waveModel, Airy, objectRegistry);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::waveModels::Airy::k() const
{
	return 2 * tnbLib::constant::mathematical::pi / length_;
}


tnbLib::scalar tnbLib::waveModels::Airy::celerity() const
{
	return sqrt(g() / k()*tanh(k()*depth()));
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::Airy::angle
(
	const scalar t,
	const scalarField& x
) const
{
	return phase_ + k()*(x - celerity()*t);
}


bool tnbLib::waveModels::Airy::deep() const
{
	return k()*depth() > log(great);
}


tnbLib::tmp<tnbLib::vector2DField> tnbLib::waveModels::Airy::vi
(
	const label i,
	const scalar t,
	const vector2DField& xz
) const
{
	const scalarField x(xz.component(0));
	const scalarField z(xz.component(1));

	const scalarField phi(angle(t, x));
	const scalarField kz(k()*z);

	if (deep())
	{
		return i * exp(kz)*zip(cos(i*phi), sin(i*phi));
	}
	else
	{
		const scalar kd = k()*depth();
		const scalarField kdz(max(scalar(0), kd + kz));
		return i * zip(cosh(i*kdz)*cos(i*phi), sinh(i*kdz)*sin(i*phi)) / sinh(kd);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveModels::Airy::Airy(const Airy& wave)
	:
	waveModel(wave),
	length_(wave.length_),
	phase_(wave.phase_),
	depth_(wave.depth_)
{}


tnbLib::waveModels::Airy::Airy
(
	const objectRegistry& db,
	const dictionary& dict
)
	:
	waveModel(db, dict),
	length_(readScalar(dict.lookup("length"))),
	phase_(readScalar(dict.lookup("phase"))),
	depth_(dict.lookupOrDefault<scalar>("depth", log(2 * great) / k()))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::waveModels::Airy::~Airy()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::Airy::elevation
(
	const scalar t,
	const scalarField& x
) const
{
	return amplitude(t)*cos(angle(t, x));
}


tnbLib::tmp<tnbLib::vector2DField> tnbLib::waveModels::Airy::velocity
(
	const scalar t,
	const vector2DField& xz
) const
{
	const scalar ka = k()*amplitude(t);

	return celerity()*ka*vi(1, t, xz);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::waveModels::Airy::pressure
(
	const scalar t,
	const vector2DField& xz
) const
{
	// It is a fluke of the formulation that the time derivative of the velocity
	// potential equals the x-derivative multiplied by the celerity. This allows
	// for this shortcut in evaluating the unsteady pressure.
	return celerity()*velocity(t, xz)->component(0);
}


void tnbLib::waveModels::Airy::write(Ostream& os) const
{
	waveModel::write(os);

	writeEntry(os, "length", length_);
	writeEntry(os, "phase", phase_);
	if (!deep())
	{
		writeEntry(os, "depth", depth_);
	}
}


// ************************************************************************* //