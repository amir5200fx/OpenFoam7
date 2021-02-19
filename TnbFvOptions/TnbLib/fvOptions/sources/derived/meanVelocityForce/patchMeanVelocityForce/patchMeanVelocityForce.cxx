#include <patchMeanVelocityForce.hxx>

#include <processorCyclicPolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(patchMeanVelocityForce, 0);

		addToRunTimeSelectionTable
		(
			option,
			patchMeanVelocityForce,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::patchMeanVelocityForce::patchMeanVelocityForce
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	meanVelocityForce(sourceName, modelType, dict, mesh),
	patch_(coeffs_.lookup("patch")),
	patchi_(mesh.boundaryMesh().findPatchID(patch_))
{
	if (patchi_ < 0)
	{
		FatalErrorInFunction
			<< "Cannot find patch " << patch_
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::fv::patchMeanVelocityForce::magUbarAve
(
	const volVectorField& U
) const
{
	vector2D sumAmagUsumA
	(
		sum
		(
		(flowDir_ & U.boundaryField()[patchi_])
			*mesh_.boundary()[patchi_].magSf()
		),
		sum(mesh_.boundary()[patchi_].magSf())
	);


	// If the mean velocity force is applied to a cyclic patch
	// for parallel runs include contributions from processorCyclic patches
	// generated from the decomposition of the cyclic patch
	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	if (Pstream::parRun() && isA<cyclicPolyPatch>(patches[patchi_]))
	{
		labelList processorCyclicPatches
		(
			processorCyclicPolyPatch::patchIDs(patch_, patches)
		);

		forAll(processorCyclicPatches, pcpi)
		{
			const label patchi = processorCyclicPatches[pcpi];

			sumAmagUsumA.x() +=
				sum
				(
				(flowDir_ & U.boundaryField()[patchi])
					*mesh_.boundary()[patchi].magSf()
				);

			sumAmagUsumA.y() += sum(mesh_.boundary()[patchi].magSf());
		}
	}

	mesh_.reduce(sumAmagUsumA, sumOp<vector2D>());

	return sumAmagUsumA.x() / sumAmagUsumA.y();
}


// ************************************************************************* //