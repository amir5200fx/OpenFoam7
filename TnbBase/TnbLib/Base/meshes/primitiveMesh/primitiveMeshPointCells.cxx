#include <primitiveMesh.hxx>

#include <cell.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcPointCells() const
{
	// Loop through cells and mark up points

	if (debug)
	{
		Pout << "primitiveMesh::calcPointCells() : "
			<< "calculating pointCells"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorInFunction
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate pointCells
	// if the pointer is already set
	if (pcPtr_)
	{
		FatalErrorInFunction
			<< "pointCells already calculated"
			<< abort(FatalError);
	}
	else
	{
		const cellList& cf = cells();

		// Count number of cells per point

		labelList npc(nPoints(), 0);

		forAll(cf, celli)
		{
			const labelList curPoints = cf[celli].labels(faces());

			forAll(curPoints, pointi)
			{
				label ptI = curPoints[pointi];

				npc[ptI]++;
			}
		}


		// Size and fill cells per point

		pcPtr_ = new labelListList(npc.size());
		labelListList& pointCellAddr = *pcPtr_;

		forAll(pointCellAddr, pointi)
		{
			pointCellAddr[pointi].setSize(npc[pointi]);
		}
		npc = 0;


		forAll(cf, celli)
		{
			const labelList curPoints = cf[celli].labels(faces());

			forAll(curPoints, pointi)
			{
				label ptI = curPoints[pointi];

				pointCellAddr[ptI][npc[ptI]++] = celli;
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::pointCells() const
{
	if (!pcPtr_)
	{
		calcPointCells();
	}

	return *pcPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointCells
(
	const label pointi,
	DynamicList<label>& storage
) const
{
	if (hasPointCells())
	{
		return pointCells()[pointi];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const labelList& pFaces = pointFaces()[pointi];

		storage.clear();

		forAll(pFaces, i)
		{
			const label facei = pFaces[i];

			// Append owner
			storage.append(own[facei]);

			// Append neighbour
			if (facei < nInternalFaces())
			{
				storage.append(nei[facei]);
			}
		}

		// Filter duplicates
		if (storage.size() > 1)
		{
			sort(storage);

			label n = 1;
			for (label i = 1; i < storage.size(); i++)
			{
				if (storage[i - 1] != storage[i])
				{
					storage[n++] = storage[i];
				}
			}

			// truncate addressed list
			storage.setSize(n);
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointCells(const label pointi) const
{
	return pointCells(pointi, labels_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //