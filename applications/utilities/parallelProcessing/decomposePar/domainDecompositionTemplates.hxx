#pragma once

// .cxx

#include <cyclicPolyPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class BinaryOp>
void tnbLib::domainDecomposition::processInterCyclics
(
    const polyBoundaryMesh& patches,
    List<DynamicList<DynamicList<label>>>& interPatchFaces,
    List<Map<label>>& procNbrToInterPatch,
    List<labelListList>& subPatchIDs,
    List<labelListList>& subPatchStarts,
    bool owner,
    BinaryOp bop
) const
{
    // Processor boundaries from split cyclics
    forAll(patches, patchi)
    {
        if (isA<cyclicPolyPatch>(patches[patchi]))
        {
            const cyclicPolyPatch& pp = refCast<const cyclicPolyPatch>
                (
                    patches[patchi]
                    );

            if (pp.owner() != owner)
            {
                continue;
            }

            // cyclic: check opposite side on this processor
            const labelUList& patchFaceCells = pp.faceCells();
            const labelUList& nbrPatchFaceCells =
                pp.neighbPatch().faceCells();

            // Store old sizes. Used to detect which inter-proc patches
            // have been added to.
            labelListList oldInterfaceSizes(nProcs_);
            forAll(oldInterfaceSizes, proci)
            {
                labelList& curOldSizes = oldInterfaceSizes[proci];

                curOldSizes.setSize(interPatchFaces[proci].size());
                forAll(curOldSizes, interI)
                {
                    curOldSizes[interI] =
                        interPatchFaces[proci][interI].size();
                }
            }

            // Add faces with different owner and neighbour processors
            forAll(patchFaceCells, facei)
            {
                const label ownerProc = cellToProc_[patchFaceCells[facei]];
                const label nbrProc = cellToProc_[nbrPatchFaceCells[facei]];
                if (bop(ownerProc, nbrProc))
                {
                    // inter - processor patch face found.
                    addInterProcFace
                    (
                        pp.start() + facei,
                        ownerProc,
                        nbrProc,
                        procNbrToInterPatch,
                        interPatchFaces
                    );
                }
            }

            // 1. Check if any faces added to existing interfaces
            forAll(oldInterfaceSizes, proci)
            {
                const labelList& curOldSizes = oldInterfaceSizes[proci];

                forAll(curOldSizes, interI)
                {
                    label oldSz = curOldSizes[interI];
                    if (interPatchFaces[proci][interI].size() > oldSz)
                    {
                        // Added faces to this interface. Add an entry
                        append(subPatchIDs[proci][interI], patchi);
                        append(subPatchStarts[proci][interI], oldSz);
                    }
                }
            }

            // 2. Any new interfaces
            forAll(subPatchIDs, proci)
            {
                label nIntfcs = interPatchFaces[proci].size();
                subPatchIDs[proci].setSize(nIntfcs, labelList(1, patchi));
                subPatchStarts[proci].setSize(nIntfcs, labelList(1, label(0)));
            }
        }
    }
}


// ************************************************************************* //
