#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <jplotSetWriter.hxx>

#include <writers.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSetWriters(jplotSetWriter);
}

// ************************************************************************* //