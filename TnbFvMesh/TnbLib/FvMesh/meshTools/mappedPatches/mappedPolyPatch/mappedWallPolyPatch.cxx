#include <mappedWallPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <mappedPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedWallPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, mappedWallPolyPatch, word);
	addToRunTimeSelectionTable
	(
		polyPatch,
		mappedWallPolyPatch,
		dictionary
	);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	wallPolyPatch(name, size, start, index, bm, patchType),
	mappedPatchBase(static_cast<const polyPatch&>(*this))
{
	//  mapped is not constraint type so add mapped group explicitly
	if (findIndex(inGroups(), mappedPolyPatch::typeName) == -1)
	{
		inGroups().append(mappedPolyPatch::typeName);
	}
}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const word& sampleRegion,
	const mappedPatchBase::sampleMode mode,
	const word& samplePatch,
	const vectorField& offset,
	const polyBoundaryMesh& bm
)
	:
	wallPolyPatch(name, size, start, index, bm, typeName),
	mappedPatchBase
	(
		static_cast<const polyPatch&>(*this),
		sampleRegion,
		mode,
		samplePatch,
		offset
	)
{}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const word& sampleRegion,
	const mappedPatchBase::sampleMode mode,
	const word& samplePatch,
	const vector& offset,
	const polyBoundaryMesh& bm
)
	:
	wallPolyPatch(name, size, start, index, bm, typeName),
	mappedPatchBase
	(
		static_cast<const polyPatch&>(*this),
		sampleRegion,
		mode,
		samplePatch,
		offset
	)
{}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	wallPolyPatch(name, dict, index, bm, patchType),
	mappedPatchBase(*this, dict)
{
	//  mapped is not constraint type so add mapped group explicitly
	if (findIndex(inGroups(), mappedPolyPatch::typeName) == -1)
	{
		inGroups().append(mappedPolyPatch::typeName);
	}
}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const mappedWallPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	wallPolyPatch(pp, bm),
	mappedPatchBase(*this, pp)
{}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const mappedWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	wallPolyPatch(pp, bm, index, newSize, newStart),
	mappedPatchBase(*this, pp)
{}


tnbLib::mappedWallPolyPatch::mappedWallPolyPatch
(
	const mappedWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	wallPolyPatch(pp, bm, index, mapAddressing, newStart),
	mappedPatchBase(*this, pp, mapAddressing)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mappedWallPolyPatch::~mappedWallPolyPatch()
{
	mappedPatchBase::clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedWallPolyPatch::initGeometry(PstreamBuffers& pBufs)
{
	wallPolyPatch::initGeometry(pBufs);
}


void tnbLib::mappedWallPolyPatch::calcGeometry(PstreamBuffers& pBufs)
{
	wallPolyPatch::calcGeometry(pBufs);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedWallPolyPatch::initMovePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	wallPolyPatch::initMovePoints(pBufs, p);
}


void tnbLib::mappedWallPolyPatch::movePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	wallPolyPatch::movePoints(pBufs, p);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedWallPolyPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	wallPolyPatch::initUpdateMesh(pBufs);
}


void tnbLib::mappedWallPolyPatch::updateMesh(PstreamBuffers& pBufs)
{
	wallPolyPatch::updateMesh(pBufs);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedWallPolyPatch::write(Ostream& os) const
{
	wallPolyPatch::write(os);
	mappedPatchBase::write(os);
}


// ************************************************************************* //