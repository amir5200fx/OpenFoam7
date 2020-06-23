#include <primitiveMesh.hxx>

#include <degenerateMatcher.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCellShapes() const
{
	if (debug)
	{
		Pout << "primitiveMesh::calcCellShapes() : calculating cellShapes"
			<< endl;
	}

	// It is an error to attempt to recalculate faceCells
	// if the pointer is already set
	if (cellShapesPtr_)
	{
		FatalErrorInFunction
			<< "cellShapes already calculated"
			<< abort(FatalError);
	}
	else
	{
		cellShapesPtr_ = new cellShapeList(nCells());
		cellShapeList& cellShapes = *cellShapesPtr_;

		forAll(cellShapes, celli)
		{
			cellShapes[celli] = degenerateMatcher::match(*this, celli);
		}
	}
}


// ************************************************************************* //