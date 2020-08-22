#include <pairPotential.hxx>

#include <energyScalingFunction.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pairPotential, 0);
	defineRunTimeSelectionTable(pairPotential, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::pairPotential::scaleEnergy(scalar& e, const scalar r) const
{
	if (!esfPtr_)
	{
		esfPtr_ = energyScalingFunction::New
		(
			name_, pairPotentialProperties_, *this
		).ptr();
	}

	esfPtr_->scaleEnergy(e, r);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pairPotential::pairPotential
(
	const word& name,
	const dictionary& pairPotentialProperties
)
	:
	name_(name),
	pairPotentialProperties_(pairPotentialProperties),
	rCut_(readScalar(pairPotentialProperties_.lookup("rCut"))),
	rCutSqr_(rCut_*rCut_),
	rMin_(readScalar(pairPotentialProperties_.lookup("rMin"))),
	dr_(readScalar(pairPotentialProperties_.lookup("dr"))),
	forceLookup_(0),
	energyLookup_(0),
	esfPtr_(nullptr),
	writeTables_(Switch(pairPotentialProperties_.lookup("writeTables")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::pairPotential::setLookupTables()
{
	label N = label((rCut_ - rMin_) / dr_) + 1;

	forceLookup_.setSize(N);

	energyLookup_.setSize(N);

	forAll(forceLookup_, k)
	{
		energyLookup_[k] = scaledEnergy(k*dr_ + rMin_);

		forceLookup_[k] = -energyDerivative((k*dr_ + rMin_), true);
	}
}


tnbLib::scalar tnbLib::pairPotential::force(const scalar r) const
{
	scalar k_rIJ = (r - rMin_) / dr_;

	label k = label(k_rIJ);

	if (k < 0)
	{
		FatalErrorInFunction
			<< "r less than rMin in pair potential " << name_ << nl
			<< abort(FatalError);
	}

	scalar f =
		(k_rIJ - k)*forceLookup_[k + 1]
		+ (k + 1 - k_rIJ)*forceLookup_[k];

	return f;
}


tnbLib::List<tnbLib::Pair<tnbLib::scalar>>
tnbLib::pairPotential::forceTable() const
{
	List<Pair<scalar>> forceTab(forceLookup_.size());

	forAll(forceLookup_, k)
	{
		forceTab[k].first() = rMin_ + k * dr_;

		forceTab[k].second() = forceLookup_[k];
	}

	return forceTab;
}


tnbLib::scalar tnbLib::pairPotential::energy(const scalar r) const
{
	scalar k_rIJ = (r - rMin_) / dr_;

	label k = label(k_rIJ);

	if (k < 0)
	{
		FatalErrorInFunction
			<< "r less than rMin in pair potential " << name_ << nl
			<< abort(FatalError);
	}

	scalar e =
		(k_rIJ - k)*energyLookup_[k + 1]
		+ (k + 1 - k_rIJ)*energyLookup_[k];

	return e;
}


tnbLib::List<tnbLib::Pair<tnbLib::scalar>>
tnbLib::pairPotential::energyTable() const
{
	List<Pair<scalar>> energyTab(energyLookup_.size());

	forAll(energyLookup_, k)
	{
		energyTab[k].first() = rMin_ + k * dr_;

		energyTab[k].second() = energyLookup_[k];
	}

	return energyTab;
}


tnbLib::scalar tnbLib::pairPotential::scaledEnergy(const scalar r) const
{
	scalar e = unscaledEnergy(r);

	scaleEnergy(e, r);

	return e;
}


tnbLib::scalar tnbLib::pairPotential::energyDerivative
(
	const scalar r,
	const bool scaledEnergyDerivative
) const
{
	// Local quadratic fit to energy: E = a0 + a1*r + a2*r^2
	// Differentiate to give f = -dE/dr = -a1 - 2*a2*r

	scalar ra = r - dr_;
	scalar rf = r;
	scalar rb = r + dr_;

	scalar Ea, Ef, Eb;

	if (scaledEnergyDerivative)
	{
		Ea = scaledEnergy(ra);
		Ef = scaledEnergy(rf);
		Eb = scaledEnergy(rb);
	}
	else
	{
		Ea = unscaledEnergy(ra);
		Ef = unscaledEnergy(rf);
		Eb = unscaledEnergy(rb);
	}

	scalar denominator = (ra - rf)*(ra - rb)*(rf - rb);

	scalar a1 =
		(
			rb*rb*(Ea - Ef) + ra * ra*(Ef - Eb) + rf * rf*(Eb - Ea)
			) / denominator;

	scalar a2 =
		(
			rb*(Ef - Ea) + rf * (Ea - Eb) + ra * (Eb - Ef)
			) / denominator;

	return a1 + 2.0*a2*r;
}


bool tnbLib::pairPotential::read(const dictionary& pairPotentialProperties)
{
	pairPotentialProperties_ = pairPotentialProperties;

	return true;
}


// ************************************************************************* //