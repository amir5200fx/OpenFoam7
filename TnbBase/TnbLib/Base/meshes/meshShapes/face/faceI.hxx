#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Edge to the right of face vertex i
inline tnbLib::label tnbLib::face::right(const label i) const
{
	return i;
}


// Edge to the left of face vertex i
inline tnbLib::label tnbLib::face::left(const label i) const
{
	return rcIndex(i);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::face::face()
{}


inline tnbLib::face::face(label s)
	:
	labelList(s, -1)
{}


inline tnbLib::face::face(const labelUList& lst)
	:
	labelList(lst)
{}


inline tnbLib::face::face(const labelList& lst)
	:
	labelList(lst)
{}


inline tnbLib::face::face(labelList&& lst)
	:
	labelList(move(lst))
{}


inline tnbLib::face::face(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::pointField tnbLib::face::points(const pointField& meshPoints) const
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


inline tnbLib::scalar tnbLib::face::mag(const pointField& points) const
{
	return ::tnbLib::mag(area(points));
}


inline tnbLib::label tnbLib::face::nEdges() const
{
	// for a closed polygon a number of edges is the same as number of points
	return size();
}


inline tnbLib::edge tnbLib::face::faceEdge(const label n) const
{
	return edge(operator[](n), operator[](fcIndex(n)));
}


// Next vertex on face
inline tnbLib::label tnbLib::face::nextLabel(const label i) const
{
	return operator[](fcIndex(i));
}


// Previous vertex on face
inline tnbLib::label tnbLib::face::prevLabel(const label i) const
{
	return operator[](rcIndex(i));
}

// Number of triangles directly known from number of vertices
inline tnbLib::label tnbLib::face::nTriangles() const
{
	return size() - 2;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::face::operator=(labelList&& l)
{
	labelList::operator=(move(l));
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline bool tnbLib::operator==(const face& a, const face& b)
{
	return face::compare(a, b) != 0;
}


inline bool tnbLib::operator!=(const face& a, const face& b)
{
	return face::compare(a, b) == 0;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

inline tnbLib::Istream& tnbLib::operator>>(Istream& is, face& f)
{
	if (is.version() == IOstream::originalVersion)
	{
		// Read starting (
		is.readBegin("face");

		// Read the 'name' token for the face
		token t(is);

		// Read labels
		is >> static_cast<labelList&>(f);

		// Read end)
		is.readEnd("face");
	}
	else
	{
		is >> static_cast<labelList&>(f);
	}

	// Check state of Ostream
	is.check("Istream& operator>>(Istream&, face&)");

	return is;
}

// ************************************************************************* //