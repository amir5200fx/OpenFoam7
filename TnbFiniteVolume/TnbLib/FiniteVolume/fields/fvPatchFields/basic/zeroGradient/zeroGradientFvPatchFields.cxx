#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <zeroGradientFvPatchFields.hxx>

#include <fvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePatchFields(zeroGradient);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //