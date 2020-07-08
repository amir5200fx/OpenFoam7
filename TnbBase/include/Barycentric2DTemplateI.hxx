#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::Barycentric2D<Cmpt>::Barycentric2D()
{}


template<class Cmpt>
inline tnbLib::Barycentric2D<Cmpt>::Barycentric2D(const tnbLib::zero)
	:
	Barycentric2D::vsType(Zero)
{}


template<class Cmpt>
inline tnbLib::Barycentric2D<Cmpt>::Barycentric2D
(
	const Cmpt& va,
	const Cmpt& vb,
	const Cmpt& vc
)
{
	this->v_[A] = va;
	this->v_[B] = vb;
	this->v_[C] = vc;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric2D<Cmpt>::a() const
{
	return this->v_[A];
}


template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric2D<Cmpt>::b() const
{
	return this->v_[B];
}


template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric2D<Cmpt>::c() const
{
	return this->v_[C];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric2D<Cmpt>::a()
{
	return this->v_[A];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric2D<Cmpt>::b()
{
	return this->v_[B];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric2D<Cmpt>::c()
{
	return this->v_[C];
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	template<class Cmpt>
	inline Cmpt operator&
		(
			const Barycentric2D<Cmpt>& b1,
			const Barycentric2D<Cmpt>& b2
			)
	{
		return b1.a()*b2.a() + b1.b()*b2.b() + b1.c()*b2.c();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //