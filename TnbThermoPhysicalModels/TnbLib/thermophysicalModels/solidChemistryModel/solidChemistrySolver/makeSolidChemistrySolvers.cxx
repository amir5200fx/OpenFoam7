#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeSolidChemistrySolverType.hxx>

#include <solidThermoPhysicsTypes.hxx>
#include <thermoPhysicsTypes.hxx>
 
#include <pyrolysisChemistryModel.hxx>
#include <basicSolidChemistryModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    makeSolidChemistrySolverTypes
    (
        pyrolysisChemistryModel,
        basicSolidChemistryModel,
        hConstSolidThermoPhysics,
        gasHThermoPhysics
    )

    makeSolidChemistrySolverTypes
    (
        pyrolysisChemistryModel,
        basicSolidChemistryModel,
        hPowerSolidThermoPhysics,
        gasHThermoPhysics
    )

    makeSolidChemistrySolverTypes
    (
        pyrolysisChemistryModel,
        basicSolidChemistryModel,
        hExpKappaConstSolidThermoPhysics,
        gasHThermoPhysics
    )
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
