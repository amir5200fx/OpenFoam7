#include <cellMatcher.hxx>

#include <primitiveMesh.hxx>
#include <Map.hxx>
#include <faceList.hxx>
#include <labelList.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellMatcher::cellMatcher
(
	const label vertPerCell,
	const label facePerCell,
	const label maxVertPerFace,
	const word& cellModelName
)
	:
	localPoint_(100),
	localFaces_(facePerCell),
	faceSize_(facePerCell, -1),
	pointMap_(vertPerCell),
	faceMap_(facePerCell),
	edgeFaces_(2 * vertPerCell*vertPerCell),
	pointFaceIndex_(vertPerCell),
	vertLabels_(vertPerCell),
	faceLabels_(facePerCell),
	cellModelName_(cellModelName),
	cellModelPtr_(nullptr)
{
	forAll(localFaces_, facei)
	{
		face& f = localFaces_[facei];

		f.setSize(maxVertPerFace);
	}

	forAll(pointFaceIndex_, vertI)
	{
		pointFaceIndex_[vertI].setSize(facePerCell);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::cellMatcher::calcLocalFaces
(
	const faceList& faces,
	const labelList& myFaces
)
{
	// Clear map from global to cell numbering
	localPoint_.clear();

	// Renumber face vertices and insert directly into localFaces_
	label newVertI = 0;
	forAll(myFaces, myFacei)
	{
		label facei = myFaces[myFacei];

		const face& f = faces[facei];
		face& localFace = localFaces_[myFacei];

		// Size of localFace
		faceSize_[myFacei] = f.size();

		forAll(f, localVertI)
		{
			label vertI = f[localVertI];

			Map<label>::iterator iter = localPoint_.find(vertI);
			if (iter == localPoint_.end())
			{
				// Not found. Assign local vertex number.

				if (newVertI >= pointMap_.size())
				{
					// Illegal face: more unique vertices than vertPerCell
					return -1;
				}

				localFace[localVertI] = newVertI;
				localPoint_.insert(vertI, newVertI);
				newVertI++;
			}
			else
			{
				// Reuse local vertex number.
				localFace[localVertI] = *iter;
			}
		}

		// Create face from localvertex labels
		faceMap_[myFacei] = facei;
	}

	// Create local to global vertex mapping
	forAllConstIter(Map<label>, localPoint_, iter)
	{
		const label fp = iter();
		pointMap_[fp] = iter.key();
	}

	////debug
	// write(Info);

	return newVertI;
}


void tnbLib::cellMatcher::calcEdgeAddressing(const label numVert)
{
	edgeFaces_ = -1;

	forAll(localFaces_, localFacei)
	{
		const face& f = localFaces_[localFacei];

		label prevVertI = faceSize_[localFacei] - 1;
		// forAll(f, fp)
		for
			(
				label fp = 0;
				fp < faceSize_[localFacei];
				fp++
				)
		{
			label start = f[prevVertI];
			label end = f[fp];

			label key1 = edgeKey(numVert, start, end);
			label key2 = edgeKey(numVert, end, start);

			if (edgeFaces_[key1] == -1)
			{
				// Entry key1 unoccupied. Store both permutations.
				edgeFaces_[key1] = localFacei;
				edgeFaces_[key2] = localFacei;
			}
			else if (edgeFaces_[key1 + 1] == -1)
			{
				// Entry key1+1 unoccupied
				edgeFaces_[key1 + 1] = localFacei;
				edgeFaces_[key2 + 1] = localFacei;
			}
			else
			{
				FatalErrorInFunction
					<< "edgeFaces_ full at entry:" << key1
					<< " for edge " << start << " " << end
					<< abort(FatalError);
			}

			prevVertI = fp;
		}
	}
}


void tnbLib::cellMatcher::calcPointFaceIndex()
{
	// Fill pointFaceIndex_ with -1
	forAll(pointFaceIndex_, i)
	{
		labelList& faceIndices = pointFaceIndex_[i];

		faceIndices = -1;
	}

	forAll(localFaces_, localFacei)
	{
		const face& f = localFaces_[localFacei];

		for
			(
				label fp = 0;
				fp < faceSize_[localFacei];
				fp++
				)
		{
			label vert = f[fp];
			pointFaceIndex_[vert][localFacei] = fp;
		}
	}
}


tnbLib::label tnbLib::cellMatcher::otherFace
(
	const label numVert,
	const label v0,
	const label v1,
	const label localFacei
) const
{
	label key = edgeKey(numVert, v0, v1);

	if (edgeFaces_[key] == localFacei)
	{
		return edgeFaces_[key + 1];
	}
	else if (edgeFaces_[key + 1] == localFacei)
	{
		return edgeFaces_[key];
	}
	else
	{
		FatalErrorInFunction
			<< "edgeFaces_ does not contain:" << localFacei
			<< " for edge " << v0 << " " << v1 << " at key " << key
			<< " edgeFaces_[key, key+1]:" << edgeFaces_[key]
			<< " , " << edgeFaces_[key + 1]
			<< abort(FatalError);

		return -1;
	}
}


void tnbLib::cellMatcher::write(tnbLib::Ostream& os) const
{
	os << "Faces:" << endl;

	forAll(localFaces_, facei)
	{
		os << "    ";

		for (label fp = 0; fp < faceSize_[facei]; fp++)
		{
			os << ' ' << localFaces_[facei][fp];
		}
		os << endl;
	}

	os << "Face map  : " << faceMap_ << endl;
	os << "Point map : " << pointMap_ << endl;
}


// ************************************************************************* //