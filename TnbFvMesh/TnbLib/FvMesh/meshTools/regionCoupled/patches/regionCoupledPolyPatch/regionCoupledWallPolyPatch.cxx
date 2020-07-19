#include <regionCoupledWallPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <polyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledWallPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, regionCoupledWallPolyPatch, word);
	addToRunTimeSelectionTable
	(
		polyPatch,
		regionCoupledWallPolyPatch,
		dictionary
	);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::regionCoupledWallPolyPatch::regionCoupledWallPolyPatch
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
	regionCoupledBase(static_cast<const polyPatch&>(*this))
{}


tnbLib::regionCoupledWallPolyPatch::regionCoupledWallPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	wallPolyPatch(name, dict, index, bm, patchType),
	regionCoupledBase(static_cast<const polyPatch&>(*this), dict)
{}


tnbLib::regionCoupledWallPolyPatch::regionCoupledWallPolyPatch
(
	const regionCoupledWallPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	wallPolyPatch(pp, bm),
	regionCoupledBase(*this, pp)
{}


tnbLib::regionCoupledWallPolyPatch::regionCoupledWallPolyPatch
(
	const regionCoupledWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	wallPolyPatch(pp, bm, index, newSize, newStart),
	regionCoupledBase(*this, pp)
{}


tnbLib::regionCoupledWallPolyPatch::regionCoupledWallPolyPatch
(
	const regionCoupledWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	wallPolyPatch(pp, bm, index, mapAddressing, newStart),
	regionCoupledBase(*this, pp)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupledWallPolyPatch::~regionCoupledWallPolyPatch()
{
	regionCoupledBase::clearGeom();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionCoupledWallPolyPatch::initGeometry(PstreamBuffers& pBufs)
{
	wallPolyPatch::initGeometry(pBufs);
}


void tnbLib::regionCoupledWallPolyPatch::calcGeometry(PstreamBuffers& pBufs)
{
	wallPolyPatch::calcGeometry(pBufs);
	regionCoupledBase::clearGeom();
}


void tnbLib::regionCoupledWallPolyPatch::initMovePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	wallPolyPatch::initMovePoints(pBufs, p);
}


void tnbLib::regionCoupledWallPolyPatch::movePoints
(
	PstreamBuffers& pBufs,
	const pointField& p
)
{
	wallPolyPatch::movePoints(pBufs, p);
	regionCoupledBase::clearGeom();
}


void tnbLib::regionCoupledWallPolyPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
	wallPolyPatch::initUpdateMesh(pBufs);
}


void tnbLib::regionCoupledWallPolyPatch::updateMesh(PstreamBuffers& pBufs)
{
	wallPolyPatch::updateMesh(pBufs);
	regionCoupledBase::clearGeom();
}


void tnbLib::regionCoupledWallPolyPatch::write(Ostream& os) const
{
	wallPolyPatch::write(os);
	regionCoupledBase::write(os);
}


// ************************************************************************* //