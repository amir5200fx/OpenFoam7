#include <ash.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ash, 0);
	addToRunTimeSelectionTable(solidProperties, ash, );
	addToRunTimeSelectionTable(solidProperties, ash, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ash::ash()
	:
	solidProperties(2010, 710, 0.04, 0.0, 1.0)
{
	if (debug)
	{
		WarningInFunction
			<< "Properties of ash need to be checked!!!"
			<< endl;
	}
}


tnbLib::ash::ash(const dictionary& dict)
	:
	ash()
{
	readIfPresent(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ash::writeData(Ostream& os) const
{
	solidProperties::writeData(os);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const ash& s)
{
	s.writeData(os);
	return os;
}


// ************************************************************************* //