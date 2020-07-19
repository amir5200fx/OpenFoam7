#include <regionCoupledPolyPatch.hxx>

#include <polyMesh.hxx>
#include <Time.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, regionCoupledPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, regionCoupledPolyPatch, dictionary);
}


// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

tnbLib::regionCoupledPolyPatch::regionCoupledPolyPatch
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
	regionCoupledBase(static_cast<const polyPatch&>(*this))
{}


tnbLib::regionCoupledPolyPatch::regionCoupledPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType),
	regionCoupledBase(*this, dict)
{}


tnbLib::regionCoupledPolyPatch::regionCoupledPolyPatch
(
	const regionCoupledPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	regionCoupledBase(*this, pp)
{}


tnbLib::regionCoupledPolyPatch::regionCoupledPolyPatch
(
	const regionCoupledPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	regionCoupledBase(*this, pp)
{}


tnbLib::regionCoupledPolyPatch::regionCoupledPolyPatch
(
	const regionCoupledPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart),
	regionCoupledBase(*this, pp)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupledPolyPatch::~regionCoupledPolyPatch()
{
	regionCoupledBase::clearGeom();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionCoupledPolyPatch::initGeometry(PstreamBuffers& pBufs)
{
	polyPatch::initGeometry(pBufs);
}


void tnbLib::regionCoupledPolyPatch::initMovePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	polyPatch::initMovePoints(pBufs, p);
}


void tnbLib::regionCoupledPolyPatch::movePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	polyPatch::movePoints(pBufs, p);
	regionCoupledBase::clearGeom();
}


void tnbLib::regionCoupledPolyPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	polyPatch::initUpdateMesh(pBufs);
}


void tnbLib::regionCoupledPolyPatch::updateMesh(PstreamBuffers& pBufs)
{
	polyPatch::updateMesh(pBufs);
	regionCoupledBase::clearGeom();
}


void tnbLib::regionCoupledPolyPatch::write(Ostream& os) const
{
	polyPatch::write(os);
	regionCoupledBase::write(os);
}


// ************************************************************************* //