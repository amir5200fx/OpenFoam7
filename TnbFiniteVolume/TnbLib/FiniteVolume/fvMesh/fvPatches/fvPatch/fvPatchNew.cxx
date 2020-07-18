#include <fvPatch.hxx>

#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::fvPatch> tnbLib::fvPatch::New
(
	const polyPatch& patch,
	const fvBoundaryMesh& bm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing fvPatch" << endl;
	}

	polyPatchConstructorTable::iterator cstrIter =
		polyPatchConstructorTablePtr_->find(patch.type());

	if (cstrIter == polyPatchConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown fvPatch type " << patch.type() << nl
			<< "Valid fvPatch types are :"
			<< polyPatchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<fvPatch>(cstrIter()(patch, bm));
}


// ************************************************************************* //