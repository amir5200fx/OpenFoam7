#include <analytical.hxx>

#include <addToRunTimeSelectionTable.hxx>
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace integrationSchemes
	{
		defineTypeNameAndDebug(analytical, 0);
		addToRunTimeSelectionTable(integrationScheme, analytical, word);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::integrationSchemes::analytical::analytical()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::integrationSchemes::analytical::~analytical()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::integrationSchemes::analytical::dtEff
(
	const scalar dt,
	const scalar Beta
) const
{
	return
		mag(Beta*dt) > small
		? (1 - exp(-Beta * dt)) / Beta
		: dt;
}


tnbLib::scalar tnbLib::integrationSchemes::analytical::sumDtEff
(
	const scalar dt,
	const scalar Beta
) const
{
	return
		mag(Beta*dt) > small
		? dt / Beta - (1 - exp(-Beta * dt)) / sqr(Beta)
		: sqr(dt);
}


// ************************************************************************* //
