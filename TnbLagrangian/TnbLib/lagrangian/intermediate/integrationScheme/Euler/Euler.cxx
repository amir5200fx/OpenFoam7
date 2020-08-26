#include <Euler.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace integrationSchemes
	{
		defineTypeNameAndDebug(Euler, 0);
		addToRunTimeSelectionTable(integrationScheme, Euler, word);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::integrationSchemes::Euler::Euler()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::integrationSchemes::Euler::~Euler()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::integrationSchemes::Euler::dtEff
(
	const scalar dt,
	const scalar Beta
) const
{
	return dt / (1 + Beta * dt);
}


tnbLib::scalar tnbLib::integrationSchemes::Euler::sumDtEff
(
	const scalar dt,
	const scalar Beta
) const
{
	return sqr(dt) / (1 + Beta * dt);
}


// ************************************************************************* //