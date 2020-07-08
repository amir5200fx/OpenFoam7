#pragma once
#include <Istream.hxx>
#include <cell.hxx>
#include <cellModeller.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::cellShape::cellShape()
	:
	m(nullptr)
{}


inline tnbLib::cellShape::cellShape
(
	const cellModel& M,
	const labelList& l,
	const bool doCollapse
)
	:
	labelList(l),
	m(&M)
{
	if (doCollapse)
	{
		collapse();
	}
}


inline tnbLib::cellShape::cellShape
(
	const word& model,
	const labelList& l,
	const bool doCollapse
)
	:
	labelList(l),
	m(cellModeller::lookup(model))
{
	if (doCollapse)
	{
		collapse();
	}
}


inline tnbLib::cellShape::cellShape(Istream& is)
{
	is >> *this;
}


inline tnbLib::autoPtr<tnbLib::cellShape> tnbLib::cellShape::clone() const
{
	return autoPtr<cellShape>(new cellShape(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::pointField tnbLib::cellShape::points
(
	const pointField& meshPoints
) const
{
	// There are as many points as there labels for them
	pointField p(size());

	// For each point in list, set it to the point in 'pnts' addressed
	// by 'labs'
	forAll(p, i)
	{
		p[i] = meshPoints[operator[](i)];
	}

	// Return list
	return p;
}


inline const tnbLib::cellModel& tnbLib::cellShape::model() const
{
	return *m;
}


inline tnbLib::labelList tnbLib::cellShape::meshFaces
(
	const faceList& allFaces,
	const cell& cFaces
) const
{
	// Faces in model order
	faceList localFaces(faces());

	// Do linear match (usually cell shape is low complexity)

	labelList modelToMesh(localFaces.size(), -1);

	forAll(localFaces, i)
	{
		const face& localF = localFaces[i];

		forAll(cFaces, j)
		{
			label meshFacei = cFaces[j];

			if (allFaces[meshFacei] == localF)
			{
				modelToMesh[i] = meshFacei;

				break;
			}
		}
	}

	return modelToMesh;
}


inline tnbLib::labelList tnbLib::cellShape::meshEdges
(
	const edgeList& allEdges,
	const labelList& cEdges
) const
{
	// Edges in model order
	edgeList localEdges(edges());

	// Do linear match (usually cell shape is low complexity)

	labelList modelToMesh(localEdges.size(), -1);

	forAll(localEdges, i)
	{
		const edge& e = localEdges[i];

		forAll(cEdges, j)
		{
			label edgeI = cEdges[j];

			if (allEdges[edgeI] == e)
			{
				modelToMesh[i] = edgeI;

				break;
			}
		}
	}

	return modelToMesh;
}


inline tnbLib::faceList tnbLib::cellShape::faces() const
{
	return m->faces(*this);
}


inline tnbLib::faceList tnbLib::cellShape::collapsedFaces() const
{
	faceList oldFaces(faces());

	faceList newFaces(oldFaces.size());
	label newFacei = 0;

	forAll(oldFaces, oldFacei)
	{
		const face& f = oldFaces[oldFacei];

		face& newF = newFaces[newFacei];

		newF.setSize(f.size());

		label newFp = 0;
		label prevVertI = -1;

		forAll(f, fp)
		{
			label vertI = f[fp];

			if (vertI != prevVertI)
			{
				newF[newFp++] = vertI;

				prevVertI = vertI;
			}
		}

		if ((newFp > 1) && (newF[newFp - 1] == newF[0]))
		{
			--newFp;
		}

		if (newFp > 2)
		{
			// Size face and go to next one
			newF.setSize(newFp);

			newFacei++;
		}
	}
	newFaces.setSize(newFacei);

	return newFaces;
}


inline tnbLib::label tnbLib::cellShape::nFaces() const
{
	return m->nFaces();
}


inline tnbLib::edgeList tnbLib::cellShape::edges() const
{
	return m->edges(*this);
}


inline tnbLib::label tnbLib::cellShape::nEdges() const
{
	return m->nEdges();
}


inline tnbLib::label tnbLib::cellShape::nPoints() const
{
	return size();
}


inline tnbLib::point tnbLib::cellShape::centre(const pointField& points) const
{
	return m->centre(*this, points);
}


inline tnbLib::scalar tnbLib::cellShape::mag(const pointField& points) const
{
	return m->mag(*this, points);
}


// ************************************************************************* //