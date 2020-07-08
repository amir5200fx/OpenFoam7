#pragma once
#include <transform.hxx> // added by amir
#include <token.hxx>  // added by amir
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tensor tnbLib::spatialTransform::Erx() const
{
	return E_ & *r_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::spatialTransform::spatialTransform()
	:
	E_(tensor::I),
	r_(Zero)
{}


inline tnbLib::spatialTransform::spatialTransform
(
	const tensor& E,
	const vector& r
)
	:
	E_(E),
	r_(r)
{}


inline tnbLib::spatialTransform::spatialTransform(Istream& is)
	:
	E_(is),
	r_(is)
{}


inline tnbLib::spatialTransform::transpose::transpose(const spatialTransform& X)
	:
	X_(X)
{}


inline tnbLib::spatialTransform::dual::dual(const spatialTransform& X)
	:
	X_(X)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::tensor& tnbLib::spatialTransform::E() const
{
	return E_;
}

inline tnbLib::tensor& tnbLib::spatialTransform::E()
{
	return E_;
}

inline const tnbLib::vector& tnbLib::spatialTransform::r() const
{
	return r_;
}

inline tnbLib::vector& tnbLib::spatialTransform::r()
{
	return r_;
}


inline tnbLib::spatialTransform::transpose tnbLib::spatialTransform::T() const
{
	return transpose(*this);
}


inline tnbLib::spatialTransform tnbLib::spatialTransform::inv() const
{
	return spatialTransform(E_.T(), -(E_ & r_));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline tnbLib::spatialTransform::dual tnbLib::spatialTransform::operator*() const
{
	return dual(*this);
}


inline tnbLib::spatialTransform::operator tnbLib::spatialTensor() const
{
	return spatialTensor
	(
		E_, Zero,
		-Erx(), E_
	);
}


inline void tnbLib::spatialTransform::operator&=(const spatialTransform& X)
{
	E_ &= X.E_;
	r_ = X.r_ + (r_ & X.E_);
}


inline tnbLib::spatialTransform tnbLib::spatialTransform::operator&
(
	const spatialTransform& X
	) const
{
	return spatialTransform(E_ & X.E_, X.r_ + (r_ & X.E_));
}


inline tnbLib::spatialVector tnbLib::spatialTransform::operator&
(
	const spatialVector& v
	) const
{
	return spatialVector
	(
		E_ & v.w(),
		E_ & (v.l() - (r_ ^ v.w()))
	);
}


inline tnbLib::spatialVector tnbLib::spatialTransform::operator&&
(
	const spatialVector& v
	) const
{
	return spatialVector
	(
		E_ & v.w(),
		E_ & (v.l() - r_)
	);
}


inline tnbLib::vector tnbLib::spatialTransform::transformPoint
(
	const vector& p
) const
{
	return E_ & (p - r_);
}


inline tnbLib::spatialTransform::transpose::operator tnbLib::spatialTensor() const
{
	return spatialTensor
	(
		X_.E().T(), -X_.Erx().T(),
		Zero, X_.E().T()
	);
}


inline tnbLib::spatialVector tnbLib::spatialTransform::transpose::operator&
(
	const spatialVector& f
	) const
{
	vector ETfl(X_.E().T() & f.l());

	return spatialVector
	(
		(X_.E().T() & f.w()) + (X_.r() ^ ETfl),
		ETfl
	);
}


inline tnbLib::spatialTransform::dual::operator tnbLib::spatialTensor() const
{
	return spatialTensor
	(
		X_.E(), -X_.Erx(),
		Zero, X_.E()
	);
}


inline tnbLib::spatialVector tnbLib::spatialTransform::dual::operator&
(
	const spatialVector& f
	) const
{
	return spatialVector
	(
		X_.E() & (f.w() - (X_.r() ^ f.l())),
		X_.E() & f.l()
	);
}


// * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * * //

inline tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, spatialTransform& X)
{
	is >> X.E() >> X.r();
	return is;
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const spatialTransform& X
	)
{
	os << X.E() << token::SPACE << X.r();
	return os;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Rotational spatial transformation tensor about the x-axis by omega radians
	inline spatialTransform Xrx(const scalar& omega)
	{
		return spatialTransform(Rx(omega), Zero);
	}

	//- Rotational spatial transformation tensor about the x-axis by omega radians
	inline spatialTransform Xry(const scalar& omega)
	{
		return spatialTransform(Ry(omega), Zero);
	}

	//- Rotational spatial transformation tensor about the z-axis by omega radians
	inline spatialTransform Xrz(const scalar& omega)
	{
		return spatialTransform(Rz(omega), Zero);
	}

	//- Rotational spatial transformation tensor about axis a by omega radians
	inline spatialTransform Xr(const vector& a, const scalar omega)
	{
		return spatialTransform(Ra(a, omega), Zero);
	}

	//- Translational spatial transformation tensor for translation r
	inline spatialTransform Xt(const vector& r)
	{
		return spatialTransform(tensor::I, r);
	}


	// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

	//- Write the spatial transformation as an entry
	inline void writeEntry(Ostream& os, const spatialTransform& st)
	{
		os << st;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //