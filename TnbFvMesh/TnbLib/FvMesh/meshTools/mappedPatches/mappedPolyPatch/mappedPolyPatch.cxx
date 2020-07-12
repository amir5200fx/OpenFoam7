#include <mappedPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, mappedPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, mappedPolyPatch, dictionary);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::mappedPolyPatch::mappedPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, size, start, index, bm, patchType),
	mappedPatchBase(static_cast<const polyPatch&>(*this))
{
	//  mapped is not constraint type so add mapped group explicitly
	if (findIndex(inGroups(), typeName) == -1)
	{
		inGroups().append(typeName);
	}
}


tnbLib::mappedPolyPatch::mappedPolyPatch
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
	polyPatch(name, size, start, index, bm, typeName),
	mappedPatchBase
	(
		static_cast<const polyPatch&>(*this),
		sampleRegion,
		mode,
		samplePatch,
		offset
	)
{}


tnbLib::mappedPolyPatch::mappedPolyPatch
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
	polyPatch(name, size, start, index, bm, typeName),
	mappedPatchBase
	(
		static_cast<const polyPatch&>(*this),
		sampleRegion,
		mode,
		samplePatch,
		offset
	)
{}


tnbLib::mappedPolyPatch::mappedPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType),
	mappedPatchBase(*this, dict)
{
	//  mapped is not constraint type so add mapped group explicitly
	if (findIndex(inGroups(), typeName) == -1)
	{
		inGroups().append(typeName);
	}
}


tnbLib::mappedPolyPatch::mappedPolyPatch
(
	const mappedPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	mappedPatchBase(*this, pp)
{}


tnbLib::mappedPolyPatch::mappedPolyPatch
(
	const mappedPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	mappedPatchBase(*this, pp)
{}


tnbLib::mappedPolyPatch::mappedPolyPatch
(
	const mappedPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart),
	mappedPatchBase(*this, pp, mapAddressing)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mappedPolyPatch::~mappedPolyPatch()
{
	mappedPatchBase::clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedPolyPatch::initGeometry(PstreamBuffers& pBufs)
{
	polyPatch::initGeometry(pBufs);
}


void tnbLib::mappedPolyPatch::calcGeometry(PstreamBuffers& pBufs)
{
	polyPatch::calcGeometry(pBufs);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedPolyPatch::initMovePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	polyPatch::initMovePoints(pBufs, p);
}


void tnbLib::mappedPolyPatch::movePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	polyPatch::movePoints(pBufs, p);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedPolyPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	polyPatch::initUpdateMesh(pBufs);
}


void tnbLib::mappedPolyPatch::updateMesh(PstreamBuffers& pBufs)
{
	polyPatch::updateMesh(pBufs);
	mappedPatchBase::clearOut();
}


void tnbLib::mappedPolyPatch::write(Ostream& os) const
{
	polyPatch::write(os);
	mappedPatchBase::write(os);
}


// ************************************************************************* //