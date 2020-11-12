#include <thermoParcelInjectionData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::thermoParcelInjectionData::thermoParcelInjectionData(Istream& is)
	:
	kinematicParcelInjectionData(is)
{
	is.check("reading T");
	is >> T_;

	is.check("reading Cp");
	is >> Cp_;

	is.check("thermoParcelInjectionData(Istream& is)");
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const thermoParcelInjectionData& data
	)
{
	os << static_cast<const kinematicParcelInjectionData&>(data);

	os << data.T_ << data.Cp_;

	return os;
}


FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, thermoParcelInjectionData& data)
{
	is >> static_cast<kinematicParcelInjectionData&>(data);

	is.check("reading T");
	is >> data.T_;

	is.check("reading Cp");
	is >> data.Cp_;

	is.check("operator(Istream&, thermoParcelInjectionData&)");

	return is;
}


// ************************************************************************* //