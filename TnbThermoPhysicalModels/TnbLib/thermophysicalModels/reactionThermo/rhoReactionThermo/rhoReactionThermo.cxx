#include <rhoReactionThermo.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(rhoReactionThermo, 0);
	defineRunTimeSelectionTable(rhoReactionThermo, fvMesh);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rhoReactionThermo::rhoReactionThermo
(
	const fvMesh& mesh,
	const word& phaseName
)
	:
	rhoThermo(mesh, phaseName)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::rhoReactionThermo> tnbLib::rhoReactionThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<rhoReactionThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::rhoReactionThermo::~rhoReactionThermo()
{}


// ************************************************************************* //