#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::point& tnbLib::kinematicParcelInjectionData::x() const
{
	return x_;
}


inline const tnbLib::vector& tnbLib::kinematicParcelInjectionData::U() const
{
	return U_;
}


inline tnbLib::scalar tnbLib::kinematicParcelInjectionData::d() const
{
	return d_;
}


inline tnbLib::scalar tnbLib::kinematicParcelInjectionData::rho() const
{
	return rho_;
}


inline tnbLib::scalar tnbLib::kinematicParcelInjectionData::mDot() const
{
	return mDot_;
}


inline tnbLib::point& tnbLib::kinematicParcelInjectionData::x()
{
	return x_;
}


inline tnbLib::vector& tnbLib::kinematicParcelInjectionData::U()
{
	return U_;
}


inline tnbLib::scalar& tnbLib::kinematicParcelInjectionData::d()
{
	return d_;
}


inline tnbLib::scalar& tnbLib::kinematicParcelInjectionData::rho()
{
	return rho_;
}


inline tnbLib::scalar& tnbLib::kinematicParcelInjectionData::mDot()
{
	return mDot_;
}


// ************************************************************************* //