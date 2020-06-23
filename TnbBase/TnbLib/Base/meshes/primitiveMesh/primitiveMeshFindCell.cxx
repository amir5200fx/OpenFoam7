#include <primitiveMesh.hxx>

#include <cell.hxx>
#include <boundBox.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::primitiveMesh::pointInCellBB
(
	const point& p,
	label celli,
	scalar inflationFraction
) const
{
	boundBox bb
	(
		cells()[celli].points
		(
			faces(),
			points()
		),
		false
	);

	if (inflationFraction > small)
	{
		vector inflation = inflationFraction * vector::one*mag(bb.span());
		bb = boundBox(bb.min() - inflation, bb.max() + inflation);
	}

	return bb.contains(p);
}


bool tnbLib::primitiveMesh::pointInCell(const point& p, label celli) const
{
	const labelList& f = cells()[celli];
	const labelList& owner = this->faceOwner();
	const vectorField& cf = faceCentres();
	const vectorField& Sf = faceAreas();

	forAll(f, facei)
	{
		label nFace = f[facei];
		vector proj = p - cf[nFace];
		vector normal = Sf[nFace];
		if (owner[nFace] != celli)
		{
			normal = -normal;
		}

		if ((normal & proj) > 0)
		{
			return false;
		}
	}

	return true;
}


tnbLib::label tnbLib::primitiveMesh::findNearestCell(const point& location) const
{
	const vectorField& centres = cellCentres();

	label nearestCelli = 0;
	scalar minProximity = magSqr(centres[0] - location);

	for (label celli = 1; celli < centres.size(); celli++)
	{
		scalar proximity = magSqr(centres[celli] - location);

		if (proximity < minProximity)
		{
			nearestCelli = celli;
			minProximity = proximity;
		}
	}

	return nearestCelli;
}


tnbLib::label tnbLib::primitiveMesh::findCell(const point& location) const
{
	if (nCells() == 0)
	{
		return -1;
	}

	// Find the nearest cell centre to this location
	label celli = findNearestCell(location);

	// If point is in the nearest cell return
	if (pointInCell(location, celli))
	{
		return celli;
	}
	else // point is not in the nearest cell so search all cells
	{
		bool cellFound = false;
		label n = 0;

		while ((!cellFound) && (n < nCells()))
		{
			if (pointInCell(location, n))
			{
				cellFound = true;
				celli = n;
			}
			else
			{
				n++;
			}
		}
		if (cellFound)
		{
			return celli;
		}
		else
		{
			return -1;
		}
	}
}


// ************************************************************************* //