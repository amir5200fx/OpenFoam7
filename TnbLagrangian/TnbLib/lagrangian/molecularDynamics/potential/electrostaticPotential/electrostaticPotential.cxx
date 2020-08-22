#include <electrostaticPotential.hxx>

#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::electrostaticPotential::electrostaticPotential()
	:
	prefactor(1.0 / (4.0*constant::mathematical::pi*8.854187817e-12))
{}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::electrostaticPotential::energy(const scalar r) const
{
	return prefactor / r;
}


tnbLib::scalar tnbLib::electrostaticPotential::force(const scalar r) const
{
	return prefactor / (r*r);
}


// ************************************************************************* //
