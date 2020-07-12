#pragma once
#include <IOstreams.hxx>
#include <pointField.hxx>
#include <Swap.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// return
//  -  0: different
//  - +1: identical
//  - -1: same edge, but different orientation
inline int tnbLib::edge::compare(const edge& a, const edge& b)
{
	if (a[0] == b[0] && a[1] == b[1])
	{
		return 1;
	}
	else if (a[0] == b[1] && a[1] == b[0])
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::edge::edge()
{}


inline tnbLib::edge::edge(const label a, const label b)
{
	start() = a;
	end() = b;
}


inline tnbLib::edge::edge(const FixedList<label, 2>& a)
{
	start() = a[0];
	end() = a[1];
}


inline tnbLib::edge::edge(Istream& is)
	:
	FixedList<label, 2>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::edge::start() const
{
	return operator[](0);
}

inline tnbLib::label& tnbLib::edge::start()
{
	return operator[](0);
}


inline tnbLib::label tnbLib::edge::end() const
{
	return operator[](1);
}

inline tnbLib::label& tnbLib::edge::end()
{
	return operator[](1);
}


inline bool tnbLib::edge::connected(const edge& a) const
{
	if
		(
			start() == a.start()
			|| start() == a.end()
			|| end() == a.start()
			|| end() == a.end()
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}


inline tnbLib::label tnbLib::edge::commonVertex(const edge& a) const
{
	if (start() == a.start() || start() == a.end())
	{
		return start();
	}
	else if (end() == a.start() || end() == a.end())
	{
		return end();
	}
	else
	{
		// No shared vertex.
		return -1;
	}
}


inline tnbLib::label tnbLib::edge::otherVertex(const label a) const
{
	if (a == start())
	{
		return end();
	}
	else if (a == end())
	{
		return start();
	}
	else
	{
		// The given vertex is not on the edge in the first place.
		return -1;
	}
}

inline void tnbLib::edge::flip()
{
	Swap(operator[](0), operator[](1));
}


inline tnbLib::edge tnbLib::edge::reverseEdge() const
{
	return edge(end(), start());
}


inline tnbLib::point tnbLib::edge::centre(const pointField& p) const
{
	return 0.5*(p[start()] + p[end()]);
}


inline tnbLib::vector tnbLib::edge::vec(const pointField& p) const
{
	return p[end()] - p[start()];
}


inline tnbLib::scalar tnbLib::edge::mag(const pointField& p) const
{
	return ::tnbLib::mag(vec(p));
}


inline tnbLib::linePointRef tnbLib::edge::line(const pointField& p) const
{
	return linePointRef(p[start()], p[end()]);
}


// * * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * //

inline bool tnbLib::operator==(const edge& a, const edge& b)
{
	return edge::compare(a, b) != 0;
}


inline bool tnbLib::operator!=(const edge& a, const edge& b)
{
	return edge::compare(a, b) == 0;
}


// ************************************************************************* //