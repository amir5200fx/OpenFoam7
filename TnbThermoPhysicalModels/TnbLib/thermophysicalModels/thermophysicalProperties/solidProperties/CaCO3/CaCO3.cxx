#include <CaCO3.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(CaCO3, 0);
	addToRunTimeSelectionTable(solidProperties, CaCO3, );
	addToRunTimeSelectionTable(solidProperties, CaCO3, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CaCO3::CaCO3()
	:
	solidProperties(2710, 850, 1.3, 0.0, 1.0)
{
	if (debug)
	{
		WarningInFunction
			<< "Properties of CaCO3 need to be checked!!!"
			<< endl;
	}
}


tnbLib::CaCO3::CaCO3(const dictionary& dict)
	:
	CaCO3()
{
	readIfPresent(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::CaCO3::writeData(Ostream& os) const
{
	solidProperties::writeData(os);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CaCO3& s)
{
	s.writeData(os);
	return os;
}


// ************************************************************************* //