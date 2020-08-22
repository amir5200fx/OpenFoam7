#include <patchInteractionDataList.hxx>

#include <stringListOps.hxx>
#include <emptyPolyPatch.hxx>
#include <cyclicAMIPointPatch.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::patchInteractionDataList::patchInteractionDataList()
	:
	List<patchInteractionData>(),
	patchGroupIDs_()
{}


tnbLib::patchInteractionDataList::patchInteractionDataList
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	List<patchInteractionData>(dict.lookup("patches")),
	patchGroupIDs_(this->size())
{
	const polyBoundaryMesh& bMesh = mesh.boundaryMesh();
	const wordList allPatchNames = bMesh.names();

	const List<patchInteractionData>& items = *this;
	forAllReverse(items, i)
	{
		const word& patchName = items[i].patchName();
		labelList patchIDs = findStrings(patchName, allPatchNames);

		if (patchIDs.empty())
		{
			WarningInFunction
				<< "Cannot find any patch names matching " << patchName
				<< endl;
		}

		patchGroupIDs_[i].transfer(patchIDs);
	}

	// Check that all patches are specified
	DynamicList<word> badPatches;
	forAll(bMesh, patchi)
	{
		const polyPatch& pp = bMesh[patchi];
		if
			(
				!pp.coupled()
				&& !isA<emptyPolyPatch>(pp)
				&& applyToPatch(pp.index()) < 0
				)
		{
			badPatches.append(pp.name());
		}
	}

	if (badPatches.size() > 0)
	{
		FatalErrorInFunction
			<< "All patches must be specified when employing local patch "
			<< "interaction. Please specify data for patches:" << nl
			<< badPatches << nl << exit(FatalError);
	}
}


tnbLib::patchInteractionDataList::patchInteractionDataList
(
	const patchInteractionDataList& pidl
)
	:
	List<patchInteractionData>(pidl),
	patchGroupIDs_(pidl.patchGroupIDs_)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::patchInteractionDataList::applyToPatch(const label id) const
{
	forAll(patchGroupIDs_, groupI)
	{
		const labelList& patchIDs = patchGroupIDs_[groupI];
		forAll(patchIDs, patchi)
		{
			if (patchIDs[patchi] == id)
			{
				return groupI;
			}
		}
	}

	return -1;
}


// ************************************************************************* //