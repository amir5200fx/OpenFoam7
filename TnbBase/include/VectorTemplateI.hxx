#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::Vector<Cmpt>::Vector()
{}


template<class Cmpt>
inline tnbLib::Vector<Cmpt>::Vector(const tnbLib::zero)
	:
	Vector::vsType(Zero)
{}


template<class Cmpt>
template<class Cmpt2>
inline tnbLib::Vector<Cmpt>::Vector
(
	const VectorSpace<Vector<Cmpt2>, Cmpt2, 3>& vs
)
	:
	Vector::vsType(vs)
{}


template<class Cmpt>
inline tnbLib::Vector<Cmpt>::Vector
(
	const Cmpt& vx,
	const Cmpt& vy,
	const Cmpt& vz
)
{
	this->v_[X] = vx;
	this->v_[Y] = vy;
	this->v_[Z] = vz;
}


template<class Cmpt>
inline tnbLib::Vector<Cmpt>::Vector(Istream& is)
	:
	Vector::vsType(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const Cmpt& tnbLib::Vector<Cmpt>::x() const
{
	return this->v_[X];
}

template<class Cmpt>
inline const Cmpt& tnbLib::Vector<Cmpt>::y() const
{
	return this->v_[Y];
}

template<class Cmpt>
inline const Cmpt& tnbLib::Vector<Cmpt>::z() const
{
	return this->v_[Z];
}


template<class Cmpt>
inline Cmpt& tnbLib::Vector<Cmpt>::x()
{
	return this->v_[X];
}

template<class Cmpt>
inline Cmpt& tnbLib::Vector<Cmpt>::y()
{
	return this->v_[Y];
}

template<class Cmpt>
inline Cmpt& tnbLib::Vector<Cmpt>::z()
{
	return this->v_[Z];
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const tnbLib::Vector<Cmpt>& tnbLib::Vector<Cmpt>::centre
(
	const tnbLib::List<Vector<Cmpt>>&
)const
{
	return *this;
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Dummy innerProduct for scalar to allow the construction of vtables for
	//  virtual member functions involving the inner-products of fields
	//  for which a "NotImplemented" specialization for scalar is provided.
	template<class Cmpt>
	class innerProduct<Vector<Cmpt>, scalar>
	{
	public:

		typedef scalar type;
	};


	template<class Cmpt>
	inline typename innerProduct<Vector<Cmpt>, Vector<Cmpt>>::type
		operator&(const Vector<Cmpt>& v1, const Vector<Cmpt>& v2)
	{
		return Cmpt(v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z());
	}


	template<class Cmpt>
	inline Vector<Cmpt> operator^(const Vector<Cmpt>& v1, const Vector<Cmpt>& v2)
	{
		return Vector<Cmpt>
			(
			(v1.y()*v2.z() - v1.z()*v2.y()),
				(v1.z()*v2.x() - v1.x()*v2.z()),
				(v1.x()*v2.y() - v1.y()*v2.x())
				);
	}


	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	template<class Cmpt>
	inline Vector<Cmpt> perpendicular(const Vector<Cmpt>& v)
	{
		Vector<Cmpt> u(Zero);
		u[findMin(cmptMag(v))] = 1;
		return u ^ v;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //