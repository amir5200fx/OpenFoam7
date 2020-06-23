#include <facePointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <demandDrivenData.hxx>
#include <boolList.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(facePointPatch, 0);
	defineRunTimeSelectionTable(facePointPatch, polyPatch);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		facePointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

	void facePointPatch::initGeometry(PstreamBuffers&)
	{}


	void facePointPatch::calcGeometry(PstreamBuffers&)
	{}


	void facePointPatch::initMovePoints(PstreamBuffers&, const pointField&)
	{}


	void facePointPatch::movePoints(PstreamBuffers&, const pointField&)
	{}


	void facePointPatch::initUpdateMesh(PstreamBuffers& pBufs)
	{
		facePointPatch::initGeometry(pBufs);
	}


	void facePointPatch::updateMesh(PstreamBuffers&)
	{}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	facePointPatch::facePointPatch
	(
		const polyPatch& p,
		const pointBoundaryMesh& bm
	)
		:
		pointPatch(bm),
		polyPatch_(p)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //