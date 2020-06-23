#include <primitiveMesh.hxx>

#include <DynamicList.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCellEdges() const
{
	// Loop through all faces and mark up cells with edges of the face.
	// Check for duplicates

	if (debug)
	{
		Pout << "primitiveMesh::calcCellEdges() : "
			<< "calculating cellEdges"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorInFunction
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate cellEdges
	// if the pointer is already set
	if (cePtr_)
	{
		FatalErrorInFunction
			<< "cellEdges already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Set up temporary storage
		List<DynamicList<label, edgesPerCell_>> ce(nCells());


		// Get reference to faceCells and faceEdges
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const labelListList& fe = faceEdges();

		// loop through the list again and add edges; checking for duplicates
		forAll(own, facei)
		{
			DynamicList<label, edgesPerCell_>& curCellEdges = ce[own[facei]];

			const labelList& curEdges = fe[facei];

			forAll(curEdges, edgeI)
			{
				if (findIndex(curCellEdges, curEdges[edgeI]) == -1)
				{
					// Add the edge
					curCellEdges.append(curEdges[edgeI]);
				}
			}
		}

		forAll(nei, facei)
		{
			DynamicList<label, edgesPerCell_>& curCellEdges = ce[nei[facei]];

			const labelList& curEdges = fe[facei];

			forAll(curEdges, edgeI)
			{
				if (findIndex(curCellEdges, curEdges[edgeI]) == -1)
				{
					// add the edge
					curCellEdges.append(curEdges[edgeI]);
				}
			}
		}

		cePtr_ = new labelListList(ce.size());
		labelListList& cellEdgeAddr = *cePtr_;

		// reset the size
		forAll(ce, celli)
		{
			cellEdgeAddr[celli].transfer(ce[celli]);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::cellEdges() const
{
	if (!cePtr_)
	{
		calcCellEdges();
	}

	return *cePtr_;
}


// ************************************************************************* //