#include <enrichedPatch.hxx>

#include <primitiveMesh.hxx>
#include <demandDrivenData.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::label tnbLib::enrichedPatch::nFaceHits_ = 4;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::enrichedPatch::calcMasterPointFaces() const
{
	if (masterPointFacesPtr_)
	{
		FatalErrorInFunction
			<< "Master point face addressing already calculated."
			<< abort(FatalError);
	}

	// Note:
	// Master point face addressing lists the master faces for all points
	// in the enriched patch support (if there are no master faces, which is
	// normal, the list will be empty).  The index represents the index of
	// the master face rather than the index from the enriched patch
	// Master face points lists the points of the enriched master face plus
	// points projected into the master face

	Map<DynamicList<label>> mpf(meshPoints().size());

	const faceList& ef = enrichedFaces();

	// Add the original face points
	forAll(masterPatch_, facei)
	{
		const face& curFace = ef[facei + slavePatch_.size()];
		//         Pout<< "Cur face in pfAddr: " << curFace << endl;
		forAll(curFace, pointi)
		{
			Map<DynamicList<label>>::iterator mpfIter =
				mpf.find(curFace[pointi]);

			if (mpfIter == mpf.end())
			{
				// Not found, add new dynamic list
				mpf.insert
				(
					curFace[pointi],
					DynamicList<label>(primitiveMesh::facesPerPoint_)
				);

				// Iterator is invalidated - have to find again
				mpf.find(curFace[pointi])().append(facei);
			}
			else
			{
				mpfIter().append(facei);
			}
		}
	}

	// Add the projected points which hit the face
	const labelList& slaveMeshPoints = slavePatch_.meshPoints();

	forAll(slavePointFaceHits_, pointi)
	{
		if
			(
				slavePointPointHits_[pointi] < 0
				&& slavePointEdgeHits_[pointi] < 0
				&& slavePointFaceHits_[pointi].hit()
				)
		{
			// Get the index of projected point corresponding to this slave
			// point
			const label mergedSmp =
				pointMergeMap().find(slaveMeshPoints[pointi])();

			Map<DynamicList<label>>::iterator mpfIter =
				mpf.find(mergedSmp);

			if (mpfIter == mpf.end())
			{
				// Not found, add new dynamic list
				mpf.insert
				(
					mergedSmp,
					DynamicList<label>(primitiveMesh::facesPerPoint_)
				);

				// Iterator is invalidated - have to find again
				mpf.find(mergedSmp)().append
				(
					slavePointFaceHits_[pointi].hitObject()
				);
			}
			else
			{
				mpfIter().append(slavePointFaceHits_[pointi].hitObject());
			}
		}
	}

	// Re-pack dynamic lists into normal lists
	const labelList mpfToc = mpf.toc();

	masterPointFacesPtr_ = new Map<labelList>(2 * mpfToc.size());
	Map<labelList>& masterPointFaceAddr = *masterPointFacesPtr_;

	forAll(mpfToc, mpfTocI)
	{
		labelList l;
		l.transfer(mpf.find(mpfToc[mpfTocI])());

		masterPointFaceAddr.insert(mpfToc[mpfTocI], l);
	}
	// Pout<< "masterPointFaceAddr: " << masterPointFaceAddr << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::Map<tnbLib::labelList>& tnbLib::enrichedPatch::masterPointFaces() const
{
	if (!masterPointFacesPtr_)
	{
		calcMasterPointFaces();
	}

	return *masterPointFacesPtr_;
}


// ************************************************************************* //