#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcPointPoints() const
{
	if (debug)
	{
		Pout << "primitiveMesh::calcPointPoints() : "
			<< "calculating pointPoints"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorInFunction
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate pointPoints
	// if the pointer is already set
	if (ppPtr_)
	{
		FatalErrorInFunction
			<< "pointPoints already calculated"
			<< abort(FatalError);
	}
	else
	{
		const edgeList& e = edges();
		const labelListList& pe = pointEdges();

		ppPtr_ = new labelListList(pe.size());
		labelListList& pp = *ppPtr_;

		forAll(pe, pointi)
		{
			pp[pointi].setSize(pe[pointi].size());

			forAll(pe[pointi], ppi)
			{
				if (e[pe[pointi][ppi]].start() == pointi)
				{
					pp[pointi][ppi] = e[pe[pointi][ppi]].end();
				}
				else if (e[pe[pointi][ppi]].end() == pointi)
				{
					pp[pointi][ppi] = e[pe[pointi][ppi]].start();
				}
				else
				{
					FatalErrorInFunction
						<< "something wrong with edges"
						<< abort(FatalError);
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::pointPoints() const
{
	if (!ppPtr_)
	{
		calcPointPoints();
	}

	return *ppPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointPoints
(
	const label pointi,
	DynamicList<label>& storage
) const
{
	if (hasPointPoints())
	{
		return pointPoints()[pointi];
	}
	else
	{
		const edgeList& edges = this->edges();
		const labelList& pEdges = pointEdges()[pointi];

		storage.clear();

		if (pEdges.size() > storage.capacity())
		{
			storage.setCapacity(pEdges.size());
		}

		forAll(pEdges, i)
		{
			storage.append(edges[pEdges[i]].otherVertex(pointi));
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointPoints
(
	const label pointi
) const
{
	return pointPoints(pointi, labels_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //