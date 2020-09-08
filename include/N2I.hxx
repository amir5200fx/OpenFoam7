#pragma once
inline tnbLib::scalar tnbLib::N2::rho(scalar p, scalar T) const
{
	return rho_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::pv(scalar p, scalar T) const
{
	return pv_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::hl(scalar p, scalar T) const
{
	return hl_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::Cp(scalar p, scalar T) const
{
	return Cp_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::h(scalar p, scalar T) const
{
	return h_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::Cpg(scalar p, scalar T) const
{
	return Cpg_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::B(scalar p, scalar T) const
{
	return B_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::mu(scalar p, scalar T) const
{
	return mu_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::mug(scalar p, scalar T) const
{
	return mug_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::kappa(scalar p, scalar T) const
{
	return kappa_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::kappag(scalar p, scalar T) const
{
	return kappag_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::sigma(scalar p, scalar T) const
{
	return sigma_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::D(scalar p, scalar T) const
{
	return D_.f(p, T);
}


inline tnbLib::scalar tnbLib::N2::D(scalar p, scalar T, scalar Wb) const
{
	return D_.f(p, T, Wb);
}


// ************************************************************************* //