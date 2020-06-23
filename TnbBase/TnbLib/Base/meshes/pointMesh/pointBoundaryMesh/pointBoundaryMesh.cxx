#include <pointBoundaryMesh.hxx>

#include <polyBoundaryMesh.hxx>
#include <facePointPatch.hxx>
#include <pointMesh.hxx>
#include <PstreamBuffers.hxx>
#include <lduSchedule.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointBoundaryMesh::pointBoundaryMesh
(
	const pointMesh& m,
	const polyBoundaryMesh& basicBdry
)
	:
	pointPatchList(basicBdry.size()),
	mesh_(m)
{
	reset(basicBdry);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::pointBoundaryMesh::findPatchID(const word& patchName) const
{
	return mesh()().boundaryMesh().findPatchID(patchName);
}


tnbLib::labelList tnbLib::pointBoundaryMesh::findIndices
(
	const keyType& key,
	const bool usePatchGroups
) const
{
	return mesh()().boundaryMesh().findIndices(key, usePatchGroups);
}


void tnbLib::pointBoundaryMesh::calcGeometry()
{
	PstreamBuffers pBufs(Pstream::defaultCommsType);

	if
		(
			Pstream::defaultCommsType == Pstream::commsTypes::blocking
			|| Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking
			)
	{
		forAll(*this, patchi)
		{
			operator[](patchi).initGeometry(pBufs);
		}

		pBufs.finishedSends();

		forAll(*this, patchi)
		{
			operator[](patchi).calcGeometry(pBufs);
		}
	}
	else if (Pstream::defaultCommsType == Pstream::commsTypes::scheduled)
	{
		const lduSchedule& patchSchedule = mesh().globalData().patchSchedule();

		// Dummy.
		pBufs.finishedSends();

		forAll(patchSchedule, patchEvali)
		{
			label patchi = patchSchedule[patchEvali].patch;

			if (patchSchedule[patchEvali].init)
			{
				operator[](patchi).initGeometry(pBufs);
			}
			else
			{
				operator[](patchi).calcGeometry(pBufs);
			}
		}
	}
}


void tnbLib::pointBoundaryMesh::movePoints(const pointField& p)
{
	PstreamBuffers pBufs(Pstream::defaultCommsType);

	if
		(
			Pstream::defaultCommsType == Pstream::commsTypes::blocking
			|| Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking
			)
	{
		forAll(*this, patchi)
		{
			operator[](patchi).initMovePoints(pBufs, p);
		}

		pBufs.finishedSends();

		forAll(*this, patchi)
		{
			operator[](patchi).movePoints(pBufs, p);
		}
	}
	else if (Pstream::defaultCommsType == Pstream::commsTypes::scheduled)
	{
		const lduSchedule& patchSchedule = mesh().globalData().patchSchedule();

		// Dummy.
		pBufs.finishedSends();

		forAll(patchSchedule, patchEvali)
		{
			label patchi = patchSchedule[patchEvali].patch;

			if (patchSchedule[patchEvali].init)
			{
				operator[](patchi).initMovePoints(pBufs, p);
			}
			else
			{
				operator[](patchi).movePoints(pBufs, p);
			}
		}
	}
}


void tnbLib::pointBoundaryMesh::updateMesh()
{
	PstreamBuffers pBufs(Pstream::defaultCommsType);

	if
		(
			Pstream::defaultCommsType == Pstream::commsTypes::blocking
			|| Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking
			)
	{
		forAll(*this, patchi)
		{
			operator[](patchi).initUpdateMesh(pBufs);
		}

		pBufs.finishedSends();

		forAll(*this, patchi)
		{
			operator[](patchi).updateMesh(pBufs);
		}
	}
	else if (Pstream::defaultCommsType == Pstream::commsTypes::scheduled)
	{
		const lduSchedule& patchSchedule = mesh().globalData().patchSchedule();

		// Dummy.
		pBufs.finishedSends();

		forAll(patchSchedule, patchEvali)
		{
			label patchi = patchSchedule[patchEvali].patch;

			if (patchSchedule[patchEvali].init)
			{
				operator[](patchi).initUpdateMesh(pBufs);
			}
			else
			{
				operator[](patchi).updateMesh(pBufs);
			}
		}
	}
}


void tnbLib::pointBoundaryMesh::reset(const polyBoundaryMesh& basicBdry)
{
	// Set boundary patches
	pointPatchList& Patches = *this;

	forAll(Patches, patchi)
	{
		Patches.set
		(
			patchi,
			facePointPatch::New(basicBdry[patchi], *this).ptr()
		);
	}
}


void tnbLib::pointBoundaryMesh::shuffle
(
	const labelUList& newToOld,
	const bool validBoundary
)
{
	pointPatchList::shuffle(newToOld);
	if (validBoundary)
	{
		updateMesh();
	}
}


// ************************************************************************* //