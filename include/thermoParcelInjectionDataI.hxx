#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::thermoParcelInjectionData::T() const
{
	return T_;
}


inline tnbLib::scalar tnbLib::thermoParcelInjectionData::Cp() const
{
	return Cp_;
}


inline tnbLib::scalar& tnbLib::thermoParcelInjectionData::T()
{
	return T_;
}


inline tnbLib::scalar& tnbLib::thermoParcelInjectionData::Cp()
{
	return Cp_;
}


// ************************************************************************* //