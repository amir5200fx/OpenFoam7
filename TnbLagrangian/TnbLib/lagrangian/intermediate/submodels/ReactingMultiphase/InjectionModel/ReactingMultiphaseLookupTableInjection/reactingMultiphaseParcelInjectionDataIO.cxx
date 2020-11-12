#include <reactingMultiphaseParcelInjectionData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::reactingMultiphaseParcelInjectionData::
reactingMultiphaseParcelInjectionData(Istream& is)
	:
	reactingParcelInjectionData(is)
{
	is.check("reading YGas's");
	is >> YGas_;

	is.check("reading YLiquid's");
	is >> YLiquid_;

	is.check("reading YSolid's");
	is >> YSolid_;

	is.check("reactingMultiphaseParcelInjectionData(Istream& is)");
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const reactingMultiphaseParcelInjectionData& data
	)
{
	os << static_cast<const reactingParcelInjectionData&>(data);

	os << data.YGas_ << data.YLiquid_ << data.YSolid_;

	return os;
}


FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	reactingMultiphaseParcelInjectionData& data
	)
{
	is >> static_cast<reactingParcelInjectionData&>(data);

	is.check("reading YGas's");
	is >> data.YGas_;

	is.check("reading YLiquid's");
	is >> data.YLiquid_;

	is.check("reading YSolid's");
	is >> data.YSolid_;

	is.check("operator(Istream&, reactingMultiphaseParcelInjectionData&)");

	return is;
}


// ************************************************************************* //