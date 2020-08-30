#include <reactingMultiphaseParcelInjectionData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(reactingMultiphaseParcelInjectionData, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::reactingMultiphaseParcelInjectionData::
reactingMultiphaseParcelInjectionData()
	:
	reactingParcelInjectionData(),
	YGas_(),
	YLiquid_(),
	YSolid_()
{}


tnbLib::reactingMultiphaseParcelInjectionData::
reactingMultiphaseParcelInjectionData
(
	const dictionary& dict
)
	:
	reactingParcelInjectionData(dict),
	YGas_(dict.lookup("YGas")),
	YLiquid_(dict.lookup("YLiquid")),
	YSolid_(dict.lookup("YSolid"))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::reactingMultiphaseParcelInjectionData::
~reactingMultiphaseParcelInjectionData()
{}


// ************************************************************************* //