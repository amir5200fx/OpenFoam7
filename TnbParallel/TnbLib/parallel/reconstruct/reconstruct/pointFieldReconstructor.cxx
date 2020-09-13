#include <pointFieldReconstructor.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointFieldReconstructor::pointFieldReconstructor
(
	const pointMesh& mesh,
	const PtrList<pointMesh>& procMeshes,
	const PtrList<labelIOList>& pointProcAddressing,
	const PtrList<labelIOList>& boundaryProcAddressing
)
	:
	mesh_(mesh),
	procMeshes_(procMeshes),
	pointProcAddressing_(pointProcAddressing),
	boundaryProcAddressing_(boundaryProcAddressing),
	patchPointAddressing_(procMeshes.size()),
	nReconstructed_(0)
{
	// Inverse-addressing of the patch point labels.
	labelList pointMap(mesh_.size(), -1);

	// Create the pointPatch addressing
	forAll(procMeshes_, proci)
	{
		const pointMesh& procMesh = procMeshes_[proci];

		patchPointAddressing_[proci].setSize(procMesh.boundary().size());

		forAll(procMesh.boundary(), patchi)
		{
			if (boundaryProcAddressing_[proci][patchi] >= 0)
			{
				labelList& procPatchAddr = patchPointAddressing_[proci][patchi];
				procPatchAddr.setSize(procMesh.boundary()[patchi].size(), -1);

				const labelList& patchPointLabels =
					mesh_.boundary()[boundaryProcAddressing_[proci][patchi]]
					.meshPoints();

				// Create the inverse-addressing of the patch point labels.
				forAll(patchPointLabels, pointi)
				{
					pointMap[patchPointLabels[pointi]] = pointi;
				}

				const labelList& procPatchPoints =
					procMesh.boundary()[patchi].meshPoints();

				forAll(procPatchPoints, pointi)
				{
					procPatchAddr[pointi] =
						pointMap
						[
							pointProcAddressing_[proci][procPatchPoints[pointi]]
						];
				}

				if (procPatchAddr.size() && min(procPatchAddr) < 0)
				{
					FatalErrorInFunction
						<< "Incomplete patch point addressing"
						<< abort(FatalError);
				}
			}
		}
	}
}


// ************************************************************************* //