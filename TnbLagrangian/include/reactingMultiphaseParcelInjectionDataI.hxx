#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::scalarList&
tnbLib::reactingMultiphaseParcelInjectionData::YGas() const
{
	return YGas_;
}


inline const tnbLib::scalarList&
tnbLib::reactingMultiphaseParcelInjectionData::YLiquid() const
{
	return YLiquid_;
}


inline const tnbLib::scalarList&
tnbLib::reactingMultiphaseParcelInjectionData::YSolid() const
{
	return YSolid_;
}


inline tnbLib::scalarList& tnbLib::reactingMultiphaseParcelInjectionData::YGas()
{
	return YGas_;
}


inline tnbLib::scalarList& tnbLib::reactingMultiphaseParcelInjectionData::YLiquid()
{
	return YLiquid_;
}


inline tnbLib::scalarList& tnbLib::reactingMultiphaseParcelInjectionData::YSolid()
{
	return YSolid_;
}


// ************************************************************************* //