#include <reactingParcelInjectionData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(reactingParcelInjectionData, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::reactingParcelInjectionData::reactingParcelInjectionData()
	:
	thermoParcelInjectionData(),
	Y_()
{}


tnbLib::reactingParcelInjectionData::reactingParcelInjectionData
(
	const dictionary& dict
)
	:
	thermoParcelInjectionData(dict),
	Y_(dict.lookup("Y"))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::reactingParcelInjectionData::~reactingParcelInjectionData()
{}


// ************************************************************************* //