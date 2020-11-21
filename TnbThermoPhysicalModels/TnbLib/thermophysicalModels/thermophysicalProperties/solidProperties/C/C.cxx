#include <C.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C, 0);
	addToRunTimeSelectionTable(solidProperties, C, );
	addToRunTimeSelectionTable(solidProperties, C, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C::C()
	:
	solidProperties(2010, 710, 0.04, 0.0, 1.0)
{
	if (debug)
	{
		WarningInFunction
			<< "Properties of graphite need to be checked!!!"
			<< endl;
	}
}


tnbLib::C::C(const dictionary& dict)
	:
	C()
{
	readIfPresent(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C::writeData(Ostream& os) const
{
	solidProperties::writeData(os);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C& s)
{
	s.writeData(os);
	return os;
}


// ************************************************************************* //