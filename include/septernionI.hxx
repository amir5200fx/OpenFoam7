#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::septernion::septernion()
{}

inline tnbLib::septernion::septernion(const vector& t, const quaternion& r)
	:
	t_(t),
	r_(r)
{}

inline tnbLib::septernion::septernion(const vector& t)
	:
	t_(t),
	r_(quaternion::I)
{}

inline tnbLib::septernion::septernion(const quaternion& r)
	:
	t_(Zero),
	r_(r)
{}

inline tnbLib::septernion::septernion(const spatialTransform& st)
	:
	t_(st.r()),
	r_(st.E())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::vector& tnbLib::septernion::t() const
{
	return t_;
}


inline const tnbLib::quaternion& tnbLib::septernion::r() const
{
	return r_;
}


inline tnbLib::vector& tnbLib::septernion::t()
{
	return t_;
}


inline tnbLib::quaternion& tnbLib::septernion::r()
{
	return r_;
}


inline tnbLib::vector tnbLib::septernion::transformPoint(const vector& v) const
{
	return r().transform(v - t());
}


inline tnbLib::vector tnbLib::septernion::invTransformPoint(const vector& v) const
{
	return t() + r().invTransform(v);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::septernion::operator*=(const septernion& tr)
{
	t_ = tr.t() + tr.r().invTransform(t_);
	r_ *= tr.r();
}


inline void tnbLib::septernion::operator=(const vector& t)
{
	t_ = t;
	r_ = quaternion::I;
}

inline void tnbLib::septernion::operator+=(const vector& t)
{
	t_ += t;
}

inline void tnbLib::septernion::operator-=(const vector& t)
{
	t_ -= t;
}


inline void tnbLib::septernion::operator=(const quaternion& r)
{
	t_ = Zero;
	r_ = r;
}

inline void tnbLib::septernion::operator*=(const quaternion& r)
{
	t_ = r.invTransform(t_);
	r_ *= r;
}

inline void tnbLib::septernion::operator/=(const quaternion& r)
{
	t_ = r.transform(t_);
	r_ /= r;
}


inline void tnbLib::septernion::operator*=(const scalar s)
{
	t_ *= s;
	r_ *= s;
}

inline void tnbLib::septernion::operator/=(const scalar s)
{
	t_ /= s;
	r_ /= s;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

inline tnbLib::septernion tnbLib::inv(const septernion& tr)
{
	return septernion(-tr.r().transform(tr.t()), conjugate(tr.r()));
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

inline bool tnbLib::operator==(const septernion& tr1, const septernion& tr2)
{
	return (tr1.t() == tr2.t() && tr1.r() == tr2.r());
}


inline bool tnbLib::operator!=(const septernion& tr1, const septernion& tr2)
{
	return !operator==(tr1, tr2);
}


inline tnbLib::septernion tnbLib::operator+
(
	const septernion& tr,
	const vector& t
	)
{
	return septernion(tr.t() + t, tr.r());
}


inline tnbLib::septernion tnbLib::operator+
(
	const vector& t,
	const septernion& tr
	)
{
	return septernion(t + tr.t(), tr.r());
}


inline tnbLib::septernion tnbLib::operator-
(
	const septernion& tr,
	const vector& t
	)
{
	return septernion(tr.t() - t, tr.r());
}


inline tnbLib::septernion tnbLib::operator*
(
	const quaternion& r,
	const septernion& tr
	)
{
	return septernion(tr.t(), r*tr.r());
}


inline tnbLib::septernion tnbLib::operator*
(
	const septernion& tr,
	const quaternion& r
	)
{
	return septernion(r.invTransform(tr.t()), tr.r()*r);
}


inline tnbLib::septernion tnbLib::operator/
(
	const septernion& tr,
	const quaternion& r
	)
{
	return septernion(r.transform(tr.t()), tr.r() / r);
}


inline tnbLib::septernion tnbLib::operator*
(
	const septernion& tr1,
	const septernion& tr2
	)
{
	return septernion
	(
		tr2.r().invTransform(tr1.t()) + tr2.t(),
		tr1.r().transform(tr2.r())
	);
}


inline tnbLib::septernion tnbLib::operator/
(
	const septernion& tr1,
	const septernion& tr2
	)
{
	return tr1 * inv(tr2);
}


inline tnbLib::septernion tnbLib::operator*(const scalar s, const septernion& tr)
{
	return septernion(s*tr.t(), s*tr.r());
}


inline tnbLib::septernion tnbLib::operator*(const septernion& tr, const scalar s)
{
	return septernion(s*tr.t(), s*tr.r());
}


inline tnbLib::septernion tnbLib::operator/(const septernion& tr, const scalar s)
{
	return septernion(tr.t() / s, tr.r() / s);
}


// ************************************************************************* //