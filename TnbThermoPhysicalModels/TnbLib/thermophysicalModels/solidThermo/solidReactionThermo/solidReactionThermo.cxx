#include <solidReactionThermo.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solidReactionThermo, 0);
	defineRunTimeSelectionTable(solidReactionThermo, fvMesh);
	defineRunTimeSelectionTable(solidReactionThermo, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidReactionThermo::solidReactionThermo
(
	const fvMesh& mesh,
	const word& phaseName
)
	:
	solidThermo(mesh, phaseName)
{}


tnbLib::solidReactionThermo::solidReactionThermo
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
	:
	solidThermo(mesh, dict, phaseName)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::solidReactionThermo> tnbLib::solidReactionThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<solidReactionThermo>(mesh, phaseName);
}


tnbLib::autoPtr<tnbLib::solidReactionThermo> tnbLib::solidReactionThermo::New
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
{
	return basicThermo::New<solidReactionThermo>(mesh, dict, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidReactionThermo::~solidReactionThermo()
{}


// ************************************************************************* //