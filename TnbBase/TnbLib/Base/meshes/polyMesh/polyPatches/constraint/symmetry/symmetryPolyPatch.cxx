#include <symmetryPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(symmetryPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, symmetryPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, symmetryPolyPatch, dictionary);
}

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::symmetryPolyPatch::symmetryPolyPatch
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
{}


tnbLib::symmetryPolyPatch::symmetryPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType)
{}


tnbLib::symmetryPolyPatch::symmetryPolyPatch
(
	const symmetryPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm)
{}


tnbLib::symmetryPolyPatch::symmetryPolyPatch
(
	const symmetryPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart)
{}


tnbLib::symmetryPolyPatch::symmetryPolyPatch
(
	const symmetryPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart)
{}


// ************************************************************************* //