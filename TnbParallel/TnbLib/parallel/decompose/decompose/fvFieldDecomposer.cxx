#include <fvFieldDecomposer.hxx>

#include <processorLduInterface.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::fvFieldDecomposer::patchFieldDecomposer::alignAddressing
(
	const labelUList& addressingSlice,
	const label addressingOffset
) const
{
	labelList addressing(addressingSlice.size());

	forAll(addressing, i)
	{
		// Subtract one to align addressing.
		addressing[i] = addressingSlice[i] - (addressingOffset + 1);
	}

	return addressing;
}


tnbLib::fvFieldDecomposer::patchFieldDecomposer::patchFieldDecomposer
(
	const labelUList& addressingSlice,
	const label addressingOffset
)
	:
	labelList(alignAddressing(addressingSlice, addressingOffset)),
	directFvPatchFieldMapper(static_cast<const labelList&>(*this))
{}


tnbLib::labelList tnbLib::fvFieldDecomposer::processorVolPatchFieldDecomposer::
alignAddressing
(
	const fvMesh& mesh,
	const labelUList& addressingSlice
) const
{
	labelList addressing(addressingSlice.size());

	const labelList& own = mesh.faceOwner();
	const labelList& neighb = mesh.faceNeighbour();

	forAll(addressing, i)
	{
		// Subtract one to align addressing.
		label ai = mag(addressingSlice[i]) - 1;

		if (ai < neighb.size())
		{
			// This is a regular face. it has been an internal face
			// of the original mesh and now it has become a face
			// on the parallel boundary.
			// Give face the value of the neighbour.

			if (addressingSlice[i] >= 0)
			{
				// I have the owner so use the neighbour value
				addressing[i] = neighb[ai];
			}
			else
			{
				addressing[i] = own[ai];
			}
		}
		else
		{
			// This is a face that used to be on a cyclic boundary
			// but has now become a parallel patch face. I cannot
			// do the interpolation properly (I would need to look
			// up the different (face) list of data), so I will
			// just grab the value from the owner cell

			addressing[i] = own[ai];
		}
	}

	return addressing;
}


tnbLib::fvFieldDecomposer::processorVolPatchFieldDecomposer::
processorVolPatchFieldDecomposer
(
	const fvMesh& mesh,
	const labelUList& addressingSlice
)
	:
	labelList(alignAddressing(mesh, addressingSlice)),
	directFvPatchFieldMapper(static_cast<const labelList&>(*this))
{}


tnbLib::fvFieldDecomposer::fvFieldDecomposer
(
	const fvMesh& completeMesh,
	const fvMesh& procMesh,
	const labelList& faceAddressing,
	const labelList& cellAddressing,
	const labelList& boundaryAddressing
)
	:
	completeMesh_(completeMesh),
	procMesh_(procMesh),
	faceAddressing_(faceAddressing),
	cellAddressing_(cellAddressing),
	boundaryAddressing_(boundaryAddressing),
	patchFieldDecomposerPtrs_
	(
		procMesh_.boundary().size(),
		static_cast<patchFieldDecomposer*>(nullptr)
	),
	processorVolPatchFieldDecomposerPtrs_
	(
		procMesh_.boundary().size(),
		static_cast<processorVolPatchFieldDecomposer*>(nullptr)
	)
{
	forAll(boundaryAddressing_, patchi)
	{
		if
			(
				boundaryAddressing_[patchi] >= 0
				&& !isA<processorLduInterface>(procMesh.boundary()[patchi])
				)
		{
			patchFieldDecomposerPtrs_[patchi] = new patchFieldDecomposer
			(
				procMesh_.boundary()[patchi].patchSlice(faceAddressing_),
				completeMesh_.boundaryMesh()
				[
					boundaryAddressing_[patchi]
				].start()
			);
		}
		else
		{
			processorVolPatchFieldDecomposerPtrs_[patchi] =
				new processorVolPatchFieldDecomposer
				(
					completeMesh_,
					procMesh_.boundary()[patchi].patchSlice(faceAddressing_)
				);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fvFieldDecomposer::~fvFieldDecomposer()
{
	forAll(patchFieldDecomposerPtrs_, patchi)
	{
		if (patchFieldDecomposerPtrs_[patchi])
		{
			delete patchFieldDecomposerPtrs_[patchi];
		}
	}

	forAll(processorVolPatchFieldDecomposerPtrs_, patchi)
	{
		if (processorVolPatchFieldDecomposerPtrs_[patchi])
		{
			delete processorVolPatchFieldDecomposerPtrs_[patchi];
		}
	}
}

// ************************************************************************* //