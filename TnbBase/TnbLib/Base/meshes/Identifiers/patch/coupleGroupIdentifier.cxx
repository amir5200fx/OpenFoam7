#include <coupleGroupIdentifier.hxx>

#include <polyMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::coupleGroupIdentifier::findOtherPatchID
(
	const polyMesh& mesh,
	const polyPatch& thisPatch
) const
{
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	if (!valid())
	{
		FatalErrorInFunction
			<< "Invalid coupleGroup patch group"
			<< " on patch " << thisPatch.name()
			<< " in region " << pbm.mesh().name()
			<< exit(FatalError);
	}

	HashTable<labelList, word>::const_iterator fnd =
		pbm.groupPatchIDs().find(name());

	if (fnd == pbm.groupPatchIDs().end())
	{
		if (&mesh == &thisPatch.boundaryMesh().mesh())
		{
			// thisPatch should be in patchGroup
			FatalErrorInFunction
				<< "Patch " << thisPatch.name()
				<< " should be in patchGroup " << name()
				<< " in region " << pbm.mesh().name()
				<< exit(FatalError);
		}

		return -1;
	}

	// Mesh has patch group
	const labelList& patchIDs = fnd();

	if (&mesh == &thisPatch.boundaryMesh().mesh())
	{
		if (patchIDs.size() > 2 || patchIDs.size() == 0)
		{
			FatalErrorInFunction
				<< "Couple patchGroup " << name()
				<< " with contents " << patchIDs
				<< " not of size < 2"
				<< " on patch " << thisPatch.name()
				<< " region " << thisPatch.boundaryMesh().mesh().name()
				<< exit(FatalError);

			return -1;
		}

		label index = findIndex(patchIDs, thisPatch.index());

		if (index == -1)
		{
			FatalErrorInFunction
				<< "Couple patchGroup " << name()
				<< " with contents " << patchIDs
				<< " does not contain patch " << thisPatch.name()
				<< " in region " << pbm.mesh().name()
				<< exit(FatalError);

			return -1;
		}


		if (patchIDs.size() == 2)
		{
			// Return the other patch
			return patchIDs[1 - index];
		}
		else    // size == 1
		{
			return -1;
		}
	}
	else
	{
		if (patchIDs.size() != 1)
		{
			FatalErrorInFunction
				<< "Couple patchGroup " << name()
				<< " with contents " << patchIDs
				<< " in region " << mesh.name()
				<< " should only contain a single patch"
				<< " when matching patch " << thisPatch.name()
				<< " in region " << pbm.mesh().name()
				<< exit(FatalError);
		}

		return patchIDs[0];
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coupleGroupIdentifier::coupleGroupIdentifier()
	:
	name_()
{}


tnbLib::coupleGroupIdentifier::coupleGroupIdentifier(const word& name)
	:
	name_(name)
{}


tnbLib::coupleGroupIdentifier::coupleGroupIdentifier(const dictionary& dict)
	:
	name_(dict.lookupOrDefault<word>("coupleGroup", ""))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::coupleGroupIdentifier::findOtherPatchID
(
	const polyPatch& thisPatch
) const
{
	const polyBoundaryMesh& pbm = thisPatch.boundaryMesh();

	return findOtherPatchID(pbm.mesh(), thisPatch);
}


tnbLib::label tnbLib::coupleGroupIdentifier::findOtherPatchID
(
	const polyPatch& thisPatch,
	word& otherRegion
) const
{
	const polyBoundaryMesh& pbm = thisPatch.boundaryMesh();
	const polyMesh& thisMesh = pbm.mesh();
	const Time& runTime = thisMesh.time();


	// Loop over all regions to find other patch in coupleGroup
	HashTable<const polyMesh*> meshSet = runTime.lookupClass<polyMesh>();

	label otherPatchID = -1;

	forAllConstIter(HashTable<const polyMesh*>, meshSet, iter)
	{
		const polyMesh& mesh = *iter();

		label patchID = findOtherPatchID(mesh, thisPatch);

		if (patchID != -1)
		{
			if (otherPatchID != -1)
			{
				FatalErrorInFunction
					<< "Couple patchGroup " << name()
					<< " should be present on only two patches"
					<< " in any of the meshes in " << meshSet.sortedToc()
					<< endl
					<< "    It seems to be present on patch "
					<< thisPatch.name()
					<< " in region " << thisMesh.name()
					<< ", on patch " << otherPatchID
					<< " in region " << otherRegion
					<< " and on patch " << patchID
					<< " in region " << mesh.name()
					<< exit(FatalError);
			}
			otherPatchID = patchID;
			otherRegion = mesh.name();
		}
	}

	if (otherPatchID == -1)
	{
		FatalErrorInFunction
			<< "Couple patchGroup " << name()
			<< " not found in any of the other meshes " << meshSet.sortedToc()
			<< " on patch " << thisPatch.name()
			<< " region " << thisMesh.name()
			<< exit(FatalError);
	}

	return otherPatchID;
}


void tnbLib::coupleGroupIdentifier::write(Ostream& os) const
{
	if (valid())
	{
		writeEntry(os, "coupleGroup", name());
	}
}


// * * * * * * * * * * * * * * Friend Operators * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const coupleGroupIdentifier& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& os, const coupleGroupIdentifier& p");
	return os;
}


// ************************************************************************* //