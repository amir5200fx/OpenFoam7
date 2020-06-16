#pragma once
#include <pointField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::boundBox::boundBox()
	:
	min_(Zero),
	max_(Zero)
{}


inline tnbLib::boundBox::boundBox(const point& min, const point& max)
	:
	min_(min),
	max_(max)
{}


inline tnbLib::boundBox::boundBox(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::boundBox::min() const
{
	return min_;
}


inline const tnbLib::point& tnbLib::boundBox::max() const
{
	return max_;
}


inline tnbLib::point& tnbLib::boundBox::min()
{
	return min_;
}


inline tnbLib::point& tnbLib::boundBox::max()
{
	return max_;
}


inline tnbLib::point tnbLib::boundBox::midpoint() const
{
	return 0.5 * (max_ + min_);
}


inline tnbLib::vector tnbLib::boundBox::span() const
{
	return (max_ - min_);
}


inline tnbLib::scalar tnbLib::boundBox::mag() const
{
	return ::tnbLib::mag(max_ - min_);
}


inline tnbLib::scalar tnbLib::boundBox::volume() const
{
	return cmptProduct(span());
}


inline tnbLib::scalar tnbLib::boundBox::minDim() const
{
	return cmptMin(span());
}


inline tnbLib::scalar tnbLib::boundBox::maxDim() const
{
	return cmptMax(span());
}


inline tnbLib::scalar tnbLib::boundBox::avgDim() const
{
	return cmptAv(span());
}


inline bool tnbLib::boundBox::overlaps(const boundBox& bb) const
{
	return
		(
			bb.max_.x() >= min_.x() && bb.min_.x() <= max_.x()
			&& bb.max_.y() >= min_.y() && bb.min_.y() <= max_.y()
			&& bb.max_.z() >= min_.z() && bb.min_.z() <= max_.z()
			);
}


inline bool tnbLib::boundBox::overlaps
(
	const point& centre,
	const scalar radiusSqr
) const
{
	// Find out where centre is in relation to bb.
	// Find nearest point on bb.
	scalar distSqr = 0;

	for (direction dir = 0; dir < vector::nComponents; dir++)
	{
		scalar d0 = min_[dir] - centre[dir];
		scalar d1 = max_[dir] - centre[dir];

		if ((d0 > 0) != (d1 > 0))
		{
			// centre inside both extrema. This component does not add any
			// distance.
		}
		else if (tnbLib::mag(d0) < tnbLib::mag(d1))
		{
			distSqr += d0 * d0;
		}
		else
		{
			distSqr += d1 * d1;
		}

		if (distSqr > radiusSqr)
		{
			return false;
		}
	}

	return true;
}


inline bool tnbLib::boundBox::contains(const point& pt) const
{
	return
		(
			pt.x() >= min_.x() && pt.x() <= max_.x()
			&& pt.y() >= min_.y() && pt.y() <= max_.y()
			&& pt.z() >= min_.z() && pt.z() <= max_.z()
			);
}


// this.bb fully contains bb
inline bool tnbLib::boundBox::contains(const boundBox& bb) const
{
	return contains(bb.min()) && contains(bb.max());
}


inline bool tnbLib::boundBox::containsInside(const point& pt) const
{
	return
		(
			pt.x() > min_.x() && pt.x() < max_.x()
			&& pt.y() > min_.y() && pt.y() < max_.y()
			&& pt.z() > min_.z() && pt.z() < max_.z()
			);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline bool tnbLib::operator==(const boundBox& a, const boundBox& b)
{
	return (a.min_ == b.min_) && (a.max_ == b.max_);
}


inline bool tnbLib::operator!=(const boundBox& a, const boundBox& b)
{
	return !(a == b);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //