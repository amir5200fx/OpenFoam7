#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::pointField& tnbLib::blockDescriptor::vertices() const
{
	return vertices_;
}


inline const tnbLib::blockFaceList& tnbLib::blockDescriptor::faces() const
{
	return faces_;
}


inline const tnbLib::cellShape& tnbLib::blockDescriptor::blockShape() const
{
	return blockShape_;
}


inline const tnbLib::Vector<tnbLib::label>& tnbLib::blockDescriptor::density() const
{
	return density_;
}


inline const tnbLib::word& tnbLib::blockDescriptor::zoneName() const
{
	return zoneName_;
}


inline tnbLib::label tnbLib::blockDescriptor::nPoints() const
{
	return
		(
		(density_.x() + 1)
			* (density_.y() + 1)
			* (density_.z() + 1)
			);
}


inline tnbLib::label tnbLib::blockDescriptor::nCells() const
{
	return
		(
			density_.x()
			* density_.y()
			* density_.z()
			);
}


inline const tnbLib::FixedList<tnbLib::label, 6>&
tnbLib::blockDescriptor::curvedFaces() const
{
	return curvedFaces_;
}


inline tnbLib::label tnbLib::blockDescriptor::nCurvedFaces() const
{
	return nCurvedFaces_;
}


inline const tnbLib::point& tnbLib::blockDescriptor::blockPoint(const label i) const
{
	return vertices_[blockShape_[i]];
}


inline tnbLib::label tnbLib::blockDescriptor::pointLabel
(
	const label i,
	const label j,
	const label k
) const
{
	return
		(
			i
			+ j * (density_.x() + 1)
			+ k * (density_.x() + 1)*(density_.y() + 1)
			);
}


inline tnbLib::label tnbLib::blockDescriptor::facePointLabel
(
	const label facei,
	const label i,
	const label j
) const
{
	if (facei == 0 || facei == 1)
	{
		return
			(
				i
				+ j * (density_.y() + 1)
				);
	}
	else if (facei == 2 || facei == 3)
	{
		return
			(
				i
				+ j * (density_.x() + 1)
				);
	}
	else
	{
		return
			(
				i
				+ j * (density_.x() + 1)
				);
	}
}


inline bool tnbLib::blockDescriptor::vertex
(
	const label i, const label j, const label k
) const
{
	bool iEnd = (i == 0 || i == density_.x());
	bool jEnd = (j == 0 || j == density_.y());
	bool kEnd = (k == 0 || k == density_.z());

	return (iEnd && jEnd && kEnd);
}


inline bool tnbLib::blockDescriptor::edge
(
	const label i, const label j, const label k
) const
{
	bool iEnd = (i == 0 || i == density_.x());
	bool jEnd = (j == 0 || j == density_.y());
	bool kEnd = (k == 0 || k == density_.z());

	return (iEnd && jEnd) || (iEnd && kEnd) || (jEnd && kEnd);
}


inline bool tnbLib::blockDescriptor::flatFaceOrEdge
(
	const label i, const label j, const label k
) const
{
	if (i == 0 && curvedFaces_[0] == -1) return true;
	if (i == density_.x() && curvedFaces_[1] == -1) return true;
	if (j == 0 && curvedFaces_[2] == -1) return true;
	if (j == density_.y() && curvedFaces_[3] == -1) return true;
	if (k == 0 && curvedFaces_[4] == -1) return true;
	if (k == density_.z() && curvedFaces_[5] == -1) return true;

	bool iEnd = (i == 0 || i == density_.x());
	bool jEnd = (j == 0 || j == density_.y());
	bool kEnd = (k == 0 || k == density_.z());

	return (iEnd && jEnd) || (iEnd && kEnd) || (jEnd && kEnd);
}


// ************************************************************************* //