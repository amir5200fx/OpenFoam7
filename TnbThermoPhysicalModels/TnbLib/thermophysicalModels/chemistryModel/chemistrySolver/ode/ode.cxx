#include <ode.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ChemistryModel>
tnbLib::ode<ChemistryModel>::ode(typename ChemistryModel::reactionThermo& thermo)
	:
	chemistrySolver<ChemistryModel>(thermo),
	coeffsDict_(this->subDict("odeCoeffs")),
	odeSolver_(ODESolver::New(*this, coeffsDict_)),
	cTp_(this->nEqns())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ChemistryModel>
tnbLib::ode<ChemistryModel>::~ode()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ChemistryModel>
void tnbLib::ode<ChemistryModel>::solve
(
	scalarField& c,
	scalar& T,
	scalar& p,
	scalar& deltaT,
	scalar& subDeltaT
) const
{
	// Reset the size of the ODE system to the simplified size when mechanism
	// reduction is active
	if (odeSolver_->resize())
	{
		odeSolver_->resizeField(cTp_);
	}

	const label nSpecie = this->nSpecie();

	// Copy the concentration, T and P to the total solve-vector
	for (int i = 0; i < nSpecie; i++)
	{
		cTp_[i] = c[i];
	}
	cTp_[nSpecie] = T;
	cTp_[nSpecie + 1] = p;

	odeSolver_->solve(0, deltaT, cTp_, subDeltaT);

	for (int i = 0; i < nSpecie; i++)
	{
		c[i] = max(0.0, cTp_[i]);
	}
	T = cTp_[nSpecie];
	p = cTp_[nSpecie + 1];
}


// ************************************************************************* //