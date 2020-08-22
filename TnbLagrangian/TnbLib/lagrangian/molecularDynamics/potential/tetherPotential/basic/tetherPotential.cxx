#include <tetherPotential.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(tetherPotential, 0);
	defineRunTimeSelectionTable(tetherPotential, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tetherPotential::tetherPotential
(
	const word& name,
	const dictionary& tetherPotentialProperties
)
	:
	name_(name),
	tetherPotentialProperties_(tetherPotentialProperties)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


bool tnbLib::tetherPotential::read(const dictionary& tetherPotentialProperties)
{
	tetherPotentialProperties_ = tetherPotentialProperties;

	return true;
}


// ************************************************************************* //