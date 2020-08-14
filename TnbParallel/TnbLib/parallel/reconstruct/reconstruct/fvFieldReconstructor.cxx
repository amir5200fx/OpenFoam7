#include <fvFieldReconstructor.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvFieldReconstructor::fvFieldReconstructor
(
	fvMesh& mesh,
	const PtrList<fvMesh>& procMeshes,
	const PtrList<labelIOList>& faceProcAddressing,
	const PtrList<labelIOList>& cellProcAddressing,
	const PtrList<labelIOList>& boundaryProcAddressing
)
	:
	mesh_(mesh),
	procMeshes_(procMeshes),
	faceProcAddressing_(faceProcAddressing),
	cellProcAddressing_(cellProcAddressing),
	boundaryProcAddressing_(boundaryProcAddressing),
	nReconstructed_(0)
{
	forAll(procMeshes_, proci)
	{
		const fvMesh& procMesh = procMeshes_[proci];
		if
			(
				faceProcAddressing[proci].size() != procMesh.nFaces()
				|| cellProcAddressing[proci].size() != procMesh.nCells()
				|| boundaryProcAddressing[proci].size() != procMesh.boundary().size()
				)
		{
			FatalErrorInFunction
				<< "Size of maps does not correspond to size of mesh"
				<< " for processor " << proci << endl
				<< "faceProcAddressing : " << faceProcAddressing[proci].size()
				<< " nFaces : " << procMesh.nFaces() << endl
				<< "cellProcAddressing : " << cellProcAddressing[proci].size()
				<< " nCell : " << procMesh.nCells() << endl
				<< "boundaryProcAddressing : "
				<< boundaryProcAddressing[proci].size()
				<< " nFaces : " << procMesh.boundary().size()
				<< exit(FatalError);
		}
	}
}


// ************************************************************************* //