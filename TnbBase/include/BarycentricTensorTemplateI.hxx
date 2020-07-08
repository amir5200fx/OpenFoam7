#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::BarycentricTensor<Cmpt>::BarycentricTensor()
{}


template<class Cmpt>
inline tnbLib::BarycentricTensor<Cmpt>::BarycentricTensor(const tnbLib::zero)
	:
	BarycentricTensor::msType(Zero)
{}


template<class Cmpt>
inline tnbLib::BarycentricTensor<Cmpt>::BarycentricTensor
(
	const Barycentric<Cmpt>& x,
	const Barycentric<Cmpt>& y,
	const Barycentric<Cmpt>& z
)
{
	this->v_[XA] = x.a();
	this->v_[XB] = x.b();
	this->v_[XC] = x.c();
	this->v_[XD] = x.d();

	this->v_[YA] = y.a();
	this->v_[YB] = y.b();
	this->v_[YC] = y.c();
	this->v_[YD] = y.d();

	this->v_[ZA] = z.a();
	this->v_[ZB] = z.b();
	this->v_[ZC] = z.c();
	this->v_[ZD] = z.d();
}


template<class Cmpt>
inline tnbLib::BarycentricTensor<Cmpt>::BarycentricTensor
(
	const Vector<Cmpt>& a,
	const Vector<Cmpt>& b,
	const Vector<Cmpt>& c,
	const Vector<Cmpt>& d
)
{
	this->v_[XA] = a.x();
	this->v_[XB] = b.x();
	this->v_[XC] = c.x();
	this->v_[XD] = d.x();

	this->v_[YA] = a.y();
	this->v_[YB] = b.y();
	this->v_[YC] = c.y();
	this->v_[YD] = d.y();

	this->v_[ZA] = a.z();
	this->v_[ZB] = b.z();
	this->v_[ZC] = c.z();
	this->v_[ZD] = d.z();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::Barycentric<Cmpt> tnbLib::BarycentricTensor<Cmpt>::x() const
{
	return
		Barycentric<Cmpt>
		(
			this->v_[XA],
			this->v_[XB],
			this->v_[XC],
			this->v_[XD]
			);
}


template<class Cmpt>
inline tnbLib::Barycentric<Cmpt> tnbLib::BarycentricTensor<Cmpt>::y() const
{
	return
		Barycentric<Cmpt>
		(
			this->v_[YA],
			this->v_[YB],
			this->v_[YC],
			this->v_[YD]
			);
}


template<class Cmpt>
inline tnbLib::Barycentric<Cmpt> tnbLib::BarycentricTensor<Cmpt>::z() const
{
	return
		Barycentric<Cmpt>
		(
			this->v_[ZA],
			this->v_[ZB],
			this->v_[ZC],
			this->v_[ZD]
			);
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::BarycentricTensor<Cmpt>::a() const
{
	return Vector<Cmpt>(this->v_[XA], this->v_[YA], this->v_[ZA]);
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::BarycentricTensor<Cmpt>::b() const
{
	return Vector<Cmpt>(this->v_[XB], this->v_[YB], this->v_[ZB]);
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::BarycentricTensor<Cmpt>::c() const
{
	return Vector<Cmpt>(this->v_[XC], this->v_[YC], this->v_[ZC]);
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::BarycentricTensor<Cmpt>::d() const
{
	return Vector<Cmpt>(this->v_[XD], this->v_[YD], this->v_[ZD]);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	template<class Cmpt>
	inline Vector<Cmpt> operator&
		(
			const BarycentricTensor<Cmpt>& T,
			const Barycentric<Cmpt>& b
			)
	{
		return Vector<Cmpt>(T.x() & b, T.y() & b, T.z() & b);
	}


	template<class Cmpt>
	inline Barycentric<Cmpt> operator&
		(
			const Vector<Cmpt>& v,
			const BarycentricTensor<Cmpt>& T
			)
	{
		return Barycentric<Cmpt>(v & T.a(), v & T.b(), v & T.c(), v & T.d());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //