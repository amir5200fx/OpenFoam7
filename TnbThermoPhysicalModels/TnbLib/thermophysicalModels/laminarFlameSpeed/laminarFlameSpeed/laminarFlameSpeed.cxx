#include <laminarFlameSpeed.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(laminarFlameSpeed, 0);

	defineRunTimeSelectionTable(laminarFlameSpeed, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeed::laminarFlameSpeed
(
	const dictionary& dict,
	const psiuReactionThermo& ct
)
	:
	psiuReactionThermo_(ct),
	fuel_(dict.lookup("fuel")),
	equivalenceRatio_(0)
{
	if (!psiuReactionThermo_.composition().contains("ft"))
	{
		equivalenceRatio_ =
			dimensionedScalar(dict.lookup("equivalenceRatio")).value();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeed::~laminarFlameSpeed()
{}


// ************************************************************************* //