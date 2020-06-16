#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::triad::triad()
	:
	Vector<vector>(triad::unset)
{}


inline tnbLib::triad::triad(const Vector<vector>& vv)
	:
	Vector<vector>(vv)
{}


inline tnbLib::triad::triad(const vector& x, const vector& y, const vector& z)
	:
	Vector<vector>(x, y, z)
{}


inline tnbLib::triad::triad(const vector& pa)
{
	operator=(triad::unset);
	operator[](primaryDirection(pa)) = pa;
}


inline tnbLib::triad::triad(Istream& is)
	:
	Vector<vector>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::triad::set(const direction d) const
{
	return operator[](d)[0] < great;
}


inline bool tnbLib::triad::set() const
{
	return set(0) && set(1) && set(2);
}


inline tnbLib::direction tnbLib::triad::primaryDirection(const vector& v)
{
	if (mag(v.x()) > mag(v.y()) && mag(v.x()) > mag(v.z()))
	{
		return triad::X;
	}
	else if (mag(v.y()) > mag(v.z()))
	{
		return triad::Y;
	}
	else
	{
		return triad::Z;
	}
}


inline tnbLib::vector tnbLib::triad::orthogonal
(
	const vector& v1,
	const vector& v2
)
{
	vector v3 = v1 ^ v2;

	scalar magV3 = mag(v3);

	if (magV3 > 0.5)
	{
		return v3 / magV3;
	}
	else
	{
		return triad::unset[0];
	}
}


inline void tnbLib::triad::normalize()
{
	if (set(0)) operator[](0) /= mag(operator[](0));
	if (set(1)) operator[](1) /= mag(operator[](1));
	if (set(2)) operator[](2) /= mag(operator[](2));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::triad::operator=(const Vector<vector>& vv)
{
	Vector<vector>::operator=(vv);
}


// * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * * //

inline tnbLib::Istream& tnbLib::operator>>(Istream& is, triad& t)
{
	is >> static_cast<Vector<vector>&>(t);
	return is;
}


inline tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const triad& t)
{
	os << static_cast<const Vector<vector>&>(t);
	return os;
}


// ************************************************************************* //