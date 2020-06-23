#include <facePointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::facePointPatch> tnbLib::facePointPatch::New
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing facePointPatch" << endl;
	}

	polyPatchConstructorTable::iterator cstrIter =
		polyPatchConstructorTablePtr_->find(patch.type());

	if (cstrIter == polyPatchConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown facePointPatch type "
			<< patch.type()
			<< nl << nl
			<< "Valid facePointPatch types are :" << endl
			<< polyPatchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<facePointPatch>(cstrIter()(patch, bm));
}


// ************************************************************************* //
