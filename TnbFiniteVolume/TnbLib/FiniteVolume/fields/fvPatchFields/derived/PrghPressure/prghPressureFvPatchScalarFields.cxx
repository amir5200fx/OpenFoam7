#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <PrghPressureFvPatchScalarField.hxx>

#include <pressureFvPatchScalarField.hxx>
#include <totalPressureFvPatchScalarField.hxx>
#include <uniformDensityHydrostaticPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePrghPatchScalarField(pressure, prghPressure)

		makePrghPatchScalarField(totalPressure, prghTotalPressure)

		makePrghPatchScalarField
		(
			uniformDensityHydrostaticPressure,
			prghUniformDensityHydrostaticPressure
		)
}

// ************************************************************************* //