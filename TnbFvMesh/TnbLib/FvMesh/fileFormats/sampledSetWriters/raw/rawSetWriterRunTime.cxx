#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <rawSetWriter.hxx>

#include <writers.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSetWriters(rawSetWriter);
}

// ************************************************************************* //