#include <primitiveMesh.hxx>

#include <ListOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::edgeCells() const
{
	if (!ecPtr_)
	{
		if (debug)
		{
			Pout << "primitiveMesh::edgeCells() : calculating edgeCells" << endl;

			if (debug == -1)
			{
				// For checking calls:abort so we can quickly hunt down
				// origin of call
				FatalErrorInFunction
					<< abort(FatalError);
			}
		}
		// Invert cellEdges
		ecPtr_ = new labelListList(nEdges());
		invertManyToMany(nEdges(), cellEdges(), *ecPtr_);
	}

	return *ecPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::edgeCells
(
	const label edgeI,
	DynamicList<label>& storage
) const
{
	if (hasEdgeCells())
	{
		return edgeCells()[edgeI];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();

		// Construct edgeFaces
		DynamicList<label> eFacesStorage;
		const labelList& eFaces = edgeFaces(edgeI, eFacesStorage);

		storage.clear();

		// Do quadratic insertion.
		forAll(eFaces, i)
		{
			label facei = eFaces[i];

			{
				label ownCelli = own[facei];

				// Check if not already in storage
				forAll(storage, j)
				{
					if (storage[j] == ownCelli)
					{
						ownCelli = -1;
						break;
					}
				}

				if (ownCelli != -1)
				{
					storage.append(ownCelli);
				}
			}

			if (isInternalFace(facei))
			{
				label neiCelli = nei[facei];

				forAll(storage, j)
				{
					if (storage[j] == neiCelli)
					{
						neiCelli = -1;
						break;
					}
				}

				if (neiCelli != -1)
				{
					storage.append(neiCelli);
				}
			}
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::edgeCells(const label edgeI) const
{
	return edgeCells(edgeI, labels_);
}


// ************************************************************************* //