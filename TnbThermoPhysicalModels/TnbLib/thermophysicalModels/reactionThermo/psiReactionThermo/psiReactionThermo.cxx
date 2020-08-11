#include <psiReactionThermo.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(psiReactionThermo, 0);
	defineRunTimeSelectionTable(psiReactionThermo, fvMesh);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::psiReactionThermo::psiReactionThermo
(
	const fvMesh& mesh,
	const word& phaseName
)
	:
	psiThermo(mesh, phaseName)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::psiReactionThermo> tnbLib::psiReactionThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<psiReactionThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::psiReactionThermo::~psiReactionThermo()
{}


// ************************************************************************* //