#include <fvBoundaryMesh.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fvBoundaryMesh::addPatches(const polyBoundaryMesh& basicBdry)
{
	setSize(basicBdry.size());

	// Set boundary patches
	fvPatchList& Patches = *this;

	forAll(Patches, patchi)
	{
		Patches.set(patchi, fvPatch::New(basicBdry[patchi], *this));
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvBoundaryMesh::fvBoundaryMesh
(
	const fvMesh& m
)
	:
	fvPatchList(0),
	mesh_(m)
{}


tnbLib::fvBoundaryMesh::fvBoundaryMesh
(
	const fvMesh& m,
	const polyBoundaryMesh& basicBdry
)
	:
	fvPatchList(basicBdry.size()),
	mesh_(m)
{
	addPatches(basicBdry);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::fvBoundaryMesh::findPatchID(const word& patchName) const
{
	const fvPatchList& patches = *this;

	forAll(patches, patchi)
	{
		if (patches[patchi].name() == patchName)
		{
			return patchi;
		}
	}

	// Not found, return -1
	return -1;
}


tnbLib::labelList tnbLib::fvBoundaryMesh::findIndices
(
	const keyType& key,
	const bool usePatchGroups
) const
{
	return mesh().boundaryMesh().findIndices(key, usePatchGroups);
}


void tnbLib::fvBoundaryMesh::movePoints()
{
	forAll(*this, patchi)
	{
		operator[](patchi).initMovePoints();
	}

	forAll(*this, patchi)
	{
		operator[](patchi).movePoints();
	}
}


void tnbLib::fvBoundaryMesh::shuffle
(
	const labelUList& newToOld,
	const bool validBoundary
)
{
	fvPatchList& patches = *this;
	patches.shuffle(newToOld);
}


tnbLib::lduInterfacePtrsList tnbLib::fvBoundaryMesh::interfaces() const
{
	lduInterfacePtrsList interfaces(size());

	forAll(interfaces, patchi)
	{
		if (isA<lduInterface>(this->operator[](patchi)))
		{
			interfaces.set
			(
				patchi,
				&refCast<const lduInterface>(this->operator[](patchi))
			);
		}
	}

	return interfaces;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fvBoundaryMesh::readUpdate(const polyBoundaryMesh& basicBdry)
{
	clear();
	addPatches(basicBdry);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

const tnbLib::fvPatch& tnbLib::fvBoundaryMesh::operator[]
(
	const word& patchName
	) const
{
	const label patchi = findPatchID(patchName);

	if (patchi < 0)
	{
		FatalErrorInFunction
			<< "Patch named " << patchName << " not found." << nl
			<< abort(FatalError);
	}

	return operator[](patchi);
}


tnbLib::fvPatch& tnbLib::fvBoundaryMesh::operator[]
(
	const word& patchName
	)
{
	const label patchi = findPatchID(patchName);

	if (patchi < 0)
	{
		FatalErrorInFunction
			<< "Patch named " << patchName << " not found." << nl
			<< abort(FatalError);
	}

	return operator[](patchi);
}


// ************************************************************************* //