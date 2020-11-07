#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <fixedNormalSlipFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeTemplatePatchTypeField(vector, fixedNormalSlip);
	makeTemplatePatchTypeField(tensor, fixedNormalSlip);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //