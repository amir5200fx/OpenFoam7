#include <cell.hxx>

#include <pyramidPointFaceRef.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::cell::typeName = "cell";

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::cell::labels(const faceUList& f) const
{
	// return the unordered list of vertex labels supporting the cell

	// count the maximum size of all vertices
	label maxVert = 0;

	const labelList& faces = *this;

	forAll(faces, facei)
	{
		maxVert += f[faces[facei]].size();
	}

	// set the fill-in list
	labelList p(maxVert);

	// in the first face there is no duplicates
	const labelList& first = f[faces[0]];

	forAll(first, pointi)
	{
		p[pointi] = first[pointi];
	}

	// re-use maxVert to count the real vertices
	maxVert = first.size();

	// go through the rest of the faces. For each vertex, check if the point is
	// already inserted (up to maxVert, which now carries the number of real
	// points. If not, add it at the end of the list.
	for (label facei = 1; facei < faces.size(); facei++)
	{
		const labelList& curFace = f[faces[facei]];

		forAll(curFace, pointi)
		{
			const label curPoint = curFace[pointi];

			bool found = false;

			for (label checkI = 0; checkI < maxVert; checkI++)
			{
				if (curPoint == p[checkI])
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				p[maxVert] = curPoint;

				maxVert++;
			}
		}
	}

	// reset the size of the list
	p.setSize(maxVert);

	return p;
}


tnbLib::pointField tnbLib::cell::points
(
	const faceUList& f,
	const pointField& meshPoints
) const
{
	labelList pointLabels = labels(f);

	pointField p(pointLabels.size());

	forAll(p, i)
	{
		p[i] = meshPoints[pointLabels[i]];
	}

	return p;
}


tnbLib::edgeList tnbLib::cell::edges(const faceUList& f) const
{
	// return the lisf of cell edges

	const labelList& curFaces = *this;

	// create a list of edges
	label maxNoEdges = 0;

	forAll(curFaces, facei)
	{
		maxNoEdges += f[curFaces[facei]].nEdges();
	}

	edgeList allEdges(maxNoEdges);
	label nEdges = 0;

	forAll(curFaces, facei)
	{
		const edgeList curFaceEdges = f[curFaces[facei]].edges();

		forAll(curFaceEdges, faceEdgeI)
		{
			const edge& curEdge = curFaceEdges[faceEdgeI];

			bool edgeFound = false;

			for (label addedEdgeI = 0; addedEdgeI < nEdges; addedEdgeI++)
			{
				if (allEdges[addedEdgeI] == curEdge)
				{
					edgeFound = true;

					break;
				}
			}

			if (!edgeFound)
			{
				// Add the new edge onto the list
				allEdges[nEdges] = curEdge;
				nEdges++;
			}
		}
	}

	allEdges.setSize(nEdges);

	return allEdges;
}


tnbLib::point tnbLib::cell::centre
(
	const pointField& p,
	const faceUList& f
) const
{
	// When one wants to access the cell centre and magnitude, the
	// functionality on the mesh level should be used in preference to the
	// functions provided here. They do not rely to the functionality
	// implemented here, provide additional checking and are more efficient.
	// The cell::centre and cell::mag functions may be removed in the future.

	// WARNING!
	// In the old version of the code, it was possible to establish whether any
	// of the pyramids had a negative volume, caused either by the poor
	// estimate of the cell centre or by the fact that the cell was defined
	// inside out. In the new description of the cell, this can only be
	// established with the reference to the owner-neighbour face-cell
	// relationship, which is not available on this level. Thus, all the
	// pyramids are believed to be positive with no checking.

	// first calculate the approximate cell centre as the average of all
	// face centres
	vector cEst = Zero;
	scalar sumArea = 0;

	const labelList& faces = *this;

	forAll(faces, facei)
	{
		scalar a = f[faces[facei]].mag(p);
		cEst += f[faces[facei]].centre(p)*a;
		sumArea += a;
	}

	cEst /= sumArea + vSmall;

	// Calculate the centre by breaking the cell into pyramids and
	// volume-weighted averaging their centres
	vector sumVc = Zero;

	scalar sumV = 0;

	forAll(faces, facei)
	{
		// calculate pyramid volume. If it is greater than zero, OK.
		// If not, the pyramid is inside-out. Create a face with the opposite
		// order and recalculate pyramid centre!
		scalar pyrVol = pyramidPointFaceRef(f[faces[facei]], cEst).mag(p);
		vector pyrCentre = pyramidPointFaceRef(f[faces[facei]], cEst).centre(p);

		// if pyramid inside-out because face points inwards invert
		// N.B. pyramid remains unchanged
		if (pyrVol < 0)
		{
			pyrVol = -pyrVol;
		}

		sumVc += pyrVol * pyrCentre;
		sumV += pyrVol;
	}

	return sumVc / (sumV + vSmall);
}


tnbLib::scalar tnbLib::cell::mag
(
	const pointField& p,
	const faceUList& f
) const
{
	// When one wants to access the cell centre and magnitude, the
	// functionality on the mesh level should be used in preference to the
	// functions provided here. They do not rely to the functionality
	// implemented here, provide additional checking and are more efficient.
	// The cell::centre and cell::mag functions may be removed in the future.

	// WARNING! See cell::centre

	// first calculate the approximate cell centre as the average of all
	// face centres
	vector cEst = Zero;
	scalar nCellFaces = 0;

	const labelList& faces = *this;

	forAll(faces, facei)
	{
		cEst += f[faces[facei]].centre(p);
		nCellFaces += 1;
	}

	cEst /= nCellFaces;

	// Calculate the magnitude by summing the mags of the pyramids
	scalar v = 0;

	forAll(faces, facei)
	{
		v += ::tnbLib::mag(pyramidPointFaceRef(f[faces[facei]], cEst).mag(p));
	}

	return v;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamBase_EXPORT bool tnbLib::operator==(const cell& a, const cell& b)
{
	// Trivial reject: faces are different size
	if (a.size() != b.size())
	{
		return false;
	}

	List<bool> fnd(a.size(), false);

	forAll(b, bI)
	{
		label curLabel = b[bI];

		bool found = false;

		forAll(a, aI)
		{
			if (a[aI] == curLabel)
			{
				found = true;
				fnd[aI] = true;
				break;
			}
		}

		if (!found)
		{
			return false;
		}
	}

	// check if all faces on a were marked
	bool result = true;

	forAll(fnd, aI)
	{
		result = (result && fnd[aI]);
	}

	return result;
}


// ************************************************************************* //