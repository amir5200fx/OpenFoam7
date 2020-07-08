#pragma once
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	inline const word& cellModel::name() const
	{
		return name_;
	}


	inline label cellModel::index() const
	{
		return index_;
	}


	inline label cellModel::nPoints() const
	{
		return nPoints_;
	}


	inline label cellModel::nEdges() const
	{
		return edges_.size();
	}


	inline label cellModel::nFaces() const
	{
		return faces_.size();
	}


	//  Return the faces of a cellModel by untangling the geometry
	//  supplied in terms of the face labels
	inline edgeList cellModel::edges(const labelList& pointLabels) const
	{
		edgeList e(edges_.size());

		// Translate model lebels into global labels
		forAll(edges_, edgeI)
		{
			e[edgeI] =
				edge
				(
					pointLabels[edges_[edgeI].start()],
					pointLabels[edges_[edgeI].end()]
				);
		}

		return e;
	}


	// Return a raw list of model faces
	inline const faceList& cellModel::modelFaces() const
	{
		return faces_;
	}

	//  Return the faces of a cellModel by untangling the geometry
	//  supplied in terms of the face labels
	inline faceList cellModel::faces(const labelList& pointLabels) const
	{
		faceList f(faces_.size());

		// Translate model lebels into global labels
		forAll(faces_, facei)
		{
			const labelList& curModelLabels = faces_[facei];

			face& curFace = f[facei];

			curFace.setSize(curModelLabels.size());

			forAll(curModelLabels, labelI)
			{
				curFace[labelI] = pointLabels[curModelLabels[labelI]];
			}
		}

		return f;
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	// Equality operator: true => ptr to models are equal !
	inline bool operator==(const cellModel& m1, const cellModel& m2)
	{
		return (&m1 == &m2);
	}

	// Inequality operator: true => ptr to models are not equal !
	inline bool operator!=(const cellModel& m1, const cellModel& m2)
	{
		return (&m1 != &m2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //