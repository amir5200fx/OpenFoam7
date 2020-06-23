#include <wallPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(wallPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, wallPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, wallPolyPatch, dictionary);
}

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::wallPolyPatch::wallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, size, start, index, bm, patchType)
{
	//  wall is not constraint type so add wall group explicitly
	if (findIndex(inGroups(), typeName) == -1)
	{
		inGroups().append(typeName);
	}
}


tnbLib::wallPolyPatch::wallPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType)
{
	//  wall is not constraint type so add wall group explicitly
	if (findIndex(inGroups(), typeName) == -1)
	{
		inGroups().append(typeName);
	}
}


tnbLib::wallPolyPatch::wallPolyPatch
(
	const wallPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm)
{}


tnbLib::wallPolyPatch::wallPolyPatch
(
	const wallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart)
{}


tnbLib::wallPolyPatch::wallPolyPatch
(
	const wallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart)
{}


// ************************************************************************* //