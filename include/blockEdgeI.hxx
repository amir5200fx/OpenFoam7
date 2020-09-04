#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::blockEdge::start() const
{
	return start_;
}


inline tnbLib::label tnbLib::blockEdge::end() const
{
	return end_;
}


inline int tnbLib::blockEdge::compare(const label start, const label end) const
{
	if (start_ == start && end_ == end)
	{
		return 1;
	}
	else if (start_ == end && end_ == start)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


inline int tnbLib::blockEdge::compare(const blockEdge& e) const
{
	return tnbLib::blockEdge::compare(e.start(), e.end());
}


inline int tnbLib::blockEdge::compare(const edge& e) const
{
	return tnbLib::blockEdge::compare(e.start(), e.end());
}


// ************************************************************************* //