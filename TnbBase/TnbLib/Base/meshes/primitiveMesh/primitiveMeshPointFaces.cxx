#include <primitiveMesh.hxx>

#include <ListOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::pointFaces() const
{
	if (!pfPtr_)
	{
		if (debug)
		{
			Pout << "primitiveMesh::pointFaces() : "
				<< "calculating pointFaces" << endl;
		}
		// Invert faces()
		pfPtr_ = new labelListList(nPoints());
		invertManyToMany(nPoints(), faces(), *pfPtr_);
	}

	return *pfPtr_;
}


// ************************************************************************* //