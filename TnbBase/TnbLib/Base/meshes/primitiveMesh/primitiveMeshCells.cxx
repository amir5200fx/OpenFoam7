#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCells
(
	cellList& cellFaceAddr,
	const labelUList& own,
	const labelUList& nei,
	const label inNCells
)
{
	label nCells = inNCells;

	if (nCells == -1)
	{
		nCells = -1;

		forAll(own, facei)
		{
			nCells = max(nCells, own[facei]);
		}
		nCells++;
	}

	// 1. Count number of faces per cell

	labelList ncf(nCells, 0);

	forAll(own, facei)
	{
		ncf[own[facei]]++;
	}

	forAll(nei, facei)
	{
		if (nei[facei] >= 0)
		{
			ncf[nei[facei]]++;
		}
	}

	// Create the storage
	cellFaceAddr.setSize(ncf.size());


	// 2. Size and fill cellFaceAddr

	forAll(cellFaceAddr, celli)
	{
		cellFaceAddr[celli].setSize(ncf[celli]);
	}
	ncf = 0;

	forAll(own, facei)
	{
		label celli = own[facei];

		cellFaceAddr[celli][ncf[celli]++] = facei;
	}

	forAll(nei, facei)
	{
		label celli = nei[facei];

		if (celli >= 0)
		{
			cellFaceAddr[celli][ncf[celli]++] = facei;
		}
	}
}


void tnbLib::primitiveMesh::calcCells() const
{
	// Loop through faceCells and mark up neighbours

	if (debug)
	{
		Pout << "primitiveMesh::calcCells() : calculating cells"
			<< endl;
	}

	// It is an error to attempt to recalculate cells
	// if the pointer is already set
	if (cfPtr_)
	{
		FatalErrorInFunction
			<< "cells already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Create the storage
		cfPtr_ = new cellList(nCells());
		cellList& cellFaceAddr = *cfPtr_;

		calcCells
		(
			cellFaceAddr,
			faceOwner(),
			faceNeighbour(),
			nCells()
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::cellList& tnbLib::primitiveMesh::cells() const
{
	if (!cfPtr_)
	{
		calcCells();
	}

	return *cfPtr_;
}


// ************************************************************************* //