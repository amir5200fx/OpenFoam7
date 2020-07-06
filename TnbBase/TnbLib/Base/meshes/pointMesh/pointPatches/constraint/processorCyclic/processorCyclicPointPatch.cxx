#include <processorCyclicPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(processorCyclicPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		processorCyclicPointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	processorCyclicPointPatch::processorCyclicPointPatch
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
		:
		processorPointPatch(patch, bm),
		procCycPolyPatch_(refCast<const processorCyclicPolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	processorCyclicPointPatch::~processorCyclicPointPatch()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //