#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::tetCell::tetCell()
{}


inline tnbLib::tetCell::tetCell
(
	const label a,
	const label b,
	const label c,
	const label d
)
{
	operator[](0) = a;
	operator[](1) = b;
	operator[](2) = c;
	operator[](3) = d;
}


inline tnbLib::tetCell::tetCell(const FixedList<label, 4>& lst)
	:
	FixedList<label, 4>(lst)
{}


inline tnbLib::tetCell::tetCell(Istream& is)
	:
	FixedList<label, 4>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::triFace tnbLib::tetCell::face(const label facei) const
{
	// Warning. Ordering of faces needs to be the same for a tetrahedron
	// class, a tetrahedron cell shape model and a tetCell
	static const label a[] = { 1, 0, 0, 0 };
	static const label b[] = { 2, 3, 1, 2 };
	static const label c[] = { 3, 2, 3, 1 };

#ifdef FULLDEBUG
	if (facei >= 4)
	{
		FatalErrorInFunction
			<< "index out of range 0 -> 3. facei = " << facei
			<< abort(FatalError);
	}
#endif

	return triFace
	(
		operator[](a[facei]),
		operator[](b[facei]),
		operator[](c[facei])
	);
}


inline tnbLib::label tnbLib::tetCell::edgeFace(const label edgeI) const
{
	// Warning. Ordering of faces needs to be the same for a tetrahedron
	// class, a tetrahedron cell shape model and a tetCell
	// static const label edgeFaces[6] = {2, 1, 1, 0, 0, 0};
	static const label edgeFaces[6] = { 2, 3, 1, 0, 0, 1 };

#ifdef FULLDEBUG
	if (edgeI >= 6)
	{
		FatalErrorInFunction
			<< "edge index out of range 0 -> 5. edgeI = " << edgeI
			<< abort(FatalError);
	}
#endif

	return edgeFaces[edgeI];
}


inline tnbLib::label tnbLib::tetCell::edgeAdjacentFace
(
	const label edgeI,
	const label facei
) const
{
	// Warning. Ordering of faces needs to be the same for a tetrahedron
	// class, a tetrahedron cell shape model and a tetCell
	static const label adjacentFace[6][4] =
	{
		{-1, -1, 3, 2},
		{-1, 3, -1, 1},
		{-1, 2, 1, -1},
		{2, -1, 0, -1},
		{3, -1, -1, 0},
		{1, 0, -1, -1}
	};

#ifdef FULLDEBUG
	if (facei >= 4)
	{
		FatalErrorInFunction
			<< "face index out of range 0 -> 3. facei = " << facei
			<< abort(FatalError);
	}

	if (edgeI >= 6)
	{
		FatalErrorInFunction
			<< "edge index out of range 0 -> 5. edgeI = " << edgeI
			<< abort(FatalError);
	}
#endif

	return adjacentFace[edgeI][facei];
}


inline tnbLib::edge tnbLib::tetCell::tetEdge(const label edgeI) const
{
	// Warning. Ordering of edges needs to be the same for a tetrahedron
	// class, a tetrahedron cell shape model and a tetCell
	//
	static const label start[] = { 0, 0, 0, 3, 1, 3 };
	static const label end[] = { 1, 2, 3, 1, 2, 2 };

#ifdef FULLDEBUG
	if (edgeI >= 6)
	{
		FatalErrorInFunction
			<< "index out of range 0 -> 5. edgeI = " << edgeI
			<< abort(FatalError);
	}
#endif

	return edge(operator[](start[edgeI]), operator[](end[edgeI]));
}


inline tnbLib::tetPointRef tnbLib::tetCell::tet(const pointField& points) const
{
	return tetPointRef
	(
		points[operator[](0)],
		points[operator[](1)],
		points[operator[](2)],
		points[operator[](3)]
	);
}


// ************************************************************************* //