#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <thermalBaffle1DFvPatchScalarFields.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTemplateTypeNameAndDebugWithName
(
	tnbLib::compressible::constSolid_thermalBaffle1DFvPatchScalarField,
	"compressible::thermalBaffle1D<hConstSolidThermoPhysics>",
	0
);

defineTemplateTypeNameAndDebugWithName
(
	tnbLib::compressible::expoSolid_thermalBaffle1DFvPatchScalarField,
	"compressible::thermalBaffle1D<hPowerSolidThermoPhysics>",
	0
);

namespace tnbLib
{
	namespace compressible
	{
		addToPatchFieldRunTimeSelection
		(
			fvPatchScalarField,
			constSolid_thermalBaffle1DFvPatchScalarField
		);

		addToPatchFieldRunTimeSelection
		(
			fvPatchScalarField,
			expoSolid_thermalBaffle1DFvPatchScalarField
		);
	}
}


// ************************************************************************* //