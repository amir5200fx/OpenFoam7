#include <reconstructLagrangian.hxx>

#include <labelIOList.hxx>
#include <passiveParticleCloud.hxx>

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

void tnbLib::reconstructLagrangianPositions
(
	const polyMesh& mesh,
	const word& cloudName,
	const PtrList<fvMesh>& meshes,
	const PtrList<labelIOList>& faceProcAddressing,
	const PtrList<labelIOList>& cellProcAddressing
)
{
	passiveParticleCloud lagrangianPositions
	(
		mesh,
		cloudName,
		IDLList<passiveParticle>()
	);

	forAll(meshes, i)
	{
		const labelList& cellMap = cellProcAddressing[i];
		const labelList& faceMap = faceProcAddressing[i];

		Cloud<passiveParticle> lpi(meshes[i], cloudName, false);

		forAllConstIter(Cloud<passiveParticle>, lpi, iter)
		{
			const passiveParticle& ppi = iter();

			const label mappedCell = cellMap[ppi.cell()];

			// Inverting sign if necessary and subtracting 1 from
			// faceProcAddressing
			label mappedTetFace = mag(faceMap[ppi.tetFace()]) - 1;

			lagrangianPositions.append
			(
				new passiveParticle
				(
					mesh,
					ppi.coordinates(),
					mappedCell,
					mappedTetFace,
					ppi.procTetPt(mesh, mappedCell, mappedTetFace)
				)
			);
		}
	}

	IOPosition<Cloud<passiveParticle>>(lagrangianPositions).write();
}


// ************************************************************************* //