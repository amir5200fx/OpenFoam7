#include <basicCombustionMixture.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(basicCombustionMixture, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicCombustionMixture::basicCombustionMixture
(
	const dictionary& thermoDict,
	const wordList& specieNames,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicSpecieMixture(thermoDict, specieNames, mesh, phaseName)
{}


// ************************************************************************* //