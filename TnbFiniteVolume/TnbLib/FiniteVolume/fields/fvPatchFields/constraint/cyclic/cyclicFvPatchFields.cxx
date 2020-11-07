#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <cyclicFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePatchFields(cyclic);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //