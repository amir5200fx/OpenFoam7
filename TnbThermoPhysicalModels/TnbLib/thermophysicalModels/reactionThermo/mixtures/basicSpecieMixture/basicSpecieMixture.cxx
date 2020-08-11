#include <basicSpecieMixture.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(basicSpecieMixture, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicSpecieMixture::basicSpecieMixture
(
	const dictionary& thermoDict,
	const wordList& specieNames,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicMultiComponentMixture(thermoDict, specieNames, mesh, phaseName)
{}


// ************************************************************************* //