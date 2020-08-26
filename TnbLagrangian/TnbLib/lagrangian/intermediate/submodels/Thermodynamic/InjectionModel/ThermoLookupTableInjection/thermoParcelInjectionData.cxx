#include <thermoParcelInjectionData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(thermoParcelInjectionData, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::thermoParcelInjectionData::thermoParcelInjectionData()
	:
	kinematicParcelInjectionData(),
	T_(0.0),
	Cp_(0.0)
{}


tnbLib::thermoParcelInjectionData::thermoParcelInjectionData
(
	const dictionary& dict
)
	:
	kinematicParcelInjectionData(dict),
	T_(readScalar(dict.lookup("T"))),
	Cp_(readScalar(dict.lookup("Cp")))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::thermoParcelInjectionData::~thermoParcelInjectionData()
{}


// ************************************************************************* //