#include <reactingParcelInjectionData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::reactingParcelInjectionData::reactingParcelInjectionData(Istream& is)
	:
	thermoParcelInjectionData(is)
{
	is.check("reading Y's");
	is >> Y_;

	is.check("reactingParcelInjectionData(Istream& is)");
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const reactingParcelInjectionData& data
	)
{
	os << static_cast<const thermoParcelInjectionData&>(data);

	os << data.Y_;

	return os;
}


FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, reactingParcelInjectionData& data)
{
	is >> static_cast<thermoParcelInjectionData&>(data);

	is.check("reading Y's");
	is >> data.Y_;

	is.check("operator(Istream&, reactingParcelInjectionData&)");

	return is;
}


// ************************************************************************* //