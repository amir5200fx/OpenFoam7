#pragma once
#include <specie.hxx>

// ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::solidProperties::rho() const
{
	return rho_;
}


inline tnbLib::scalar tnbLib::solidProperties::Cp() const
{
	return Cp_;
}


inline tnbLib::scalar tnbLib::solidProperties::kappa() const
{
	return kappa_;
}


inline tnbLib::scalar tnbLib::solidProperties::Hf() const
{
	return Hf_;
}


inline tnbLib::scalar tnbLib::solidProperties::Hs(const scalar T) const
{
	return Cp_ * (T - Tstd);
}


inline tnbLib::scalar tnbLib::solidProperties::emissivity() const
{
	return emissivity_;
}


// ************************************************************************* //