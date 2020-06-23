#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCellCells() const
{
	// Loop through faceCells and mark up neighbours

	if (debug)
	{
		Pout << "primitiveMesh::calcCellCells() : calculating cellCells"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorInFunction
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate cellCells
	// if the pointer is already set
	if (ccPtr_)
	{
		FatalErrorInFunction
			<< "cellCells already calculated"
			<< abort(FatalError);
	}
	else
	{
		// 1. Count number of internal faces per cell

		labelList ncc(nCells(), 0);

		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();

		forAll(nei, facei)
		{
			ncc[own[facei]]++;
			ncc[nei[facei]]++;
		}

		// Create the storage
		ccPtr_ = new labelListList(ncc.size());
		labelListList& cellCellAddr = *ccPtr_;



		// 2. Size and fill cellFaceAddr

		forAll(cellCellAddr, celli)
		{
			cellCellAddr[celli].setSize(ncc[celli]);
		}
		ncc = 0;

		forAll(nei, facei)
		{
			label ownCelli = own[facei];
			label neiCelli = nei[facei];

			cellCellAddr[ownCelli][ncc[ownCelli]++] = neiCelli;
			cellCellAddr[neiCelli][ncc[neiCelli]++] = ownCelli;
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::cellCells() const
{
	if (!ccPtr_)
	{
		calcCellCells();
	}

	return *ccPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellCells
(
	const label celli,
	DynamicList<label>& storage
) const
{
	if (hasCellCells())
	{
		return cellCells()[celli];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const cell& cFaces = cells()[celli];

		storage.clear();

		forAll(cFaces, i)
		{
			label facei = cFaces[i];

			if (facei < nInternalFaces())
			{
				if (own[facei] == celli)
				{
					storage.append(nei[facei]);
				}
				else
				{
					storage.append(own[facei]);
				}
			}
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellCells(const label celli) const
{
	return cellCells(celli, labels_);
}


// ************************************************************************* //