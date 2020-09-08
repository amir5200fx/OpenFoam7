#pragma once
inline tnbLib::scalar tnbLib::C14H30::rho(scalar p, scalar T) const
{
	return rho_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::pv(scalar p, scalar T) const
{
	return pv_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::hl(scalar p, scalar T) const
{
	return hl_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::Cp(scalar p, scalar T) const
{
	return Cp_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::h(scalar p, scalar T) const
{
	return h_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::Cpg(scalar p, scalar T) const
{
	return Cpg_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::B(scalar p, scalar T) const
{
	return B_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::mu(scalar p, scalar T) const
{
	return mu_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::mug(scalar p, scalar T) const
{
	return mug_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::kappa(scalar p, scalar T) const
{
	return kappa_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::kappag(scalar p, scalar T) const
{
	return kappag_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::sigma(scalar p, scalar T) const
{
	return sigma_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::D(scalar p, scalar T) const
{
	return D_.f(p, T);
}


inline tnbLib::scalar tnbLib::C14H30::D(scalar p, scalar T, scalar Wb) const
{
	return D_.f(p, T, Wb);
}


// ************************************************************************* //