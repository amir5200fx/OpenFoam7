#pragma once
inline tnbLib::scalar tnbLib::MB::rho(scalar p, scalar T) const
{
	return rho_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::pv(scalar p, scalar T) const
{
	return pv_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::hl(scalar p, scalar T) const
{
	return hl_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::Cp(scalar p, scalar T) const
{
	return Cp_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::h(scalar p, scalar T) const
{
	return h_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::Cpg(scalar p, scalar T) const
{
	return Cpg_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::B(scalar p, scalar T) const
{
	return B_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::mu(scalar p, scalar T) const
{
	return mu_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::mug(scalar p, scalar T) const
{
	return mug_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::kappa(scalar p, scalar T) const
{
	return kappa_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::kappag(scalar p, scalar T) const
{
	return kappag_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::sigma(scalar p, scalar T) const
{
	return sigma_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::D(scalar p, scalar T) const
{
	return D_.f(p, T);
}


inline tnbLib::scalar tnbLib::MB::D(scalar p, scalar T, scalar Wb) const
{
	return D_.f(p, T, Wb);
}


// ************************************************************************* //