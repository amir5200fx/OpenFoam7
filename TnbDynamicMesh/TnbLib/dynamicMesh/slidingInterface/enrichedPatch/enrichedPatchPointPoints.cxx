#include <enrichedPatch.hxx>

#include <primitiveMesh.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::enrichedPatch::calcPointPoints() const
{
	// Calculate point-point addressing
	if (pointPointsPtr_)
	{
		FatalErrorInFunction
			<< "Point-point addressing already calculated."
			<< abort(FatalError);
	}

	// Algorithm:
	// Go through all faces and add the previous and next point as the
	// neighbour for each point. While inserting points, reject the
	// duplicates (as every internal edge will be visited twice).
	List<DynamicList<label, primitiveMesh::edgesPerPoint_>>
		pp(meshPoints().size());

	const faceList& lf = localFaces();

	bool found = false;

	forAll(lf, facei)
	{
		const face& curFace = lf[facei];

		forAll(curFace, pointi)
		{
			DynamicList<label, primitiveMesh::edgesPerPoint_>&
				curPp = pp[curFace[pointi]];

			// Do next label
			label next = curFace.nextLabel(pointi);

			found = false;

			forAll(curPp, i)
			{
				if (curPp[i] == next)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				curPp.append(next);
			}

			// Do previous label
			label prev = curFace.prevLabel(pointi);
			found = false;

			forAll(curPp, i)
			{
				if (curPp[i] == prev)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				curPp.append(prev);
			}
		}
	}

	// Re-pack the list
	pointPointsPtr_ = new labelListList(pp.size());
	labelListList& ppAddr = *pointPointsPtr_;

	forAll(pp, pointi)
	{
		ppAddr[pointi].transfer(pp[pointi]);
	}
}


// ************************************************************************* //