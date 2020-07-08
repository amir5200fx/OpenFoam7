#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector()
{}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector(const tnbLib::zero)
	:
	SpatialVector::vsType(Zero)
{}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector
(
	const typename SpatialVector::vsType& vs
)
	:
	SpatialVector::vsType(vs)
{}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector
(
	const Vector<Cmpt>& w,
	const Vector<Cmpt>& l
)
{
	this->v_[0] = w.x();
	this->v_[1] = w.y();
	this->v_[2] = w.z();
	this->v_[3] = l.x();
	this->v_[4] = l.y();
	this->v_[5] = l.z();
}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector
(
	const Cmpt& v0,
	const Cmpt& v1,
	const Cmpt& v2,
	const Cmpt& v3,
	const Cmpt& v4,
	const Cmpt& v5
)
{
	this->v_[0] = v0;
	this->v_[1] = v1;
	this->v_[2] = v2;
	this->v_[3] = v3;
	this->v_[4] = v4;
	this->v_[5] = v5;
}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::SpatialVector(Istream& is)
	:
	SpatialVector::vsType(is)
{}


template<class Cmpt>
inline tnbLib::SpatialVector<Cmpt>::dual::dual(const SpatialVector& v)
	:
	v_(v)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::wx() const
{
	return this->v_[WX];
}


template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::wy() const
{
	return this->v_[WY];
}


template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::wz() const
{
	return this->v_[WZ];
}


template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::lx() const
{
	return this->v_[LX];
}


template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::ly() const
{
	return this->v_[LY];
}


template<class Cmpt>
inline const Cmpt& tnbLib::SpatialVector<Cmpt>::lz() const
{
	return this->v_[LZ];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::wx()
{
	return this->v_[WX];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::wy()
{
	return this->v_[WY];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::wz()
{
	return this->v_[WZ];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::lx()
{
	return this->v_[LX];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::ly()
{
	return this->v_[LY];
}


template<class Cmpt>
inline Cmpt& tnbLib::SpatialVector<Cmpt>::lz()
{
	return this->v_[LZ];
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::SpatialVector<Cmpt>::w() const
{
	return Vector<Cmpt>(this->v_[0], this->v_[1], this->v_[2]);
}

template<class Cmpt>
inline tnbLib::Vector<Cmpt> tnbLib::SpatialVector<Cmpt>::l() const
{
	return Vector<Cmpt>(this->v_[3], this->v_[4], this->v_[5]);
}


template<class Cmpt>
const tnbLib::SpatialVector<Cmpt>& tnbLib::SpatialVector<Cmpt>::dual::v() const
{
	return v_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Cmpt>
inline typename tnbLib::SpatialVector<Cmpt>::dual
tnbLib::SpatialVector<Cmpt>::operator*() const
{
	return dual(*this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	//- Return the cross-product between two spatial vectors
	template<class Cmpt>
	inline SpatialVector<Cmpt> operator^
		(
			const SpatialVector<Cmpt>& u,
			const SpatialVector<Cmpt>& v
			)
	{
		return SpatialVector<Cmpt>
			(
				-u.wz()*v.wy() + u.wy()*v.wz(),
				u.wz()*v.wx() - u.wx()*v.wz(),
				-u.wy()*v.wx() + u.wx()*v.wy(),
				-u.lz()*v.wy() + u.ly()*v.wz() - u.wz()*v.ly() + u.wy()*v.lz(),
				u.lz()*v.wx() - u.lx()*v.wz() + u.wz()*v.lx() - u.wx()*v.lz(),
				-u.ly()*v.wx() + u.lx()*v.wy() - u.wy()*v.lx() + u.wx()*v.ly()
				);
	}


	//- Return the dual cross-product between two spatial vectors
	template<class Cmpt>
	inline SpatialVector<Cmpt> operator^
		(
			const SpatialVector<Cmpt>& v,
			const typename SpatialVector<Cmpt>::dual& df
			)
	{
		const SpatialVector<Cmpt>& f = df.v();

		return SpatialVector<Cmpt>
			(
				-v.wz()*f.wy() + v.wy()*f.wz() - v.lz()*f.ly() + v.ly()*f.lz(),
				v.wz()*f.wx() - v.wx()*f.wz() + v.lz()*f.lx() - v.lx()*f.lz(),
				-v.wy()*f.wx() + v.wx()*f.wy() - v.ly()*f.lx() + v.lx()*f.ly(),
				-v.wz()*f.ly() + v.wy()*f.lz(),
				v.wz()*f.lx() - v.wx()*f.lz(),
				-v.wy()*f.lx() + v.wx()*f.ly()
				);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //