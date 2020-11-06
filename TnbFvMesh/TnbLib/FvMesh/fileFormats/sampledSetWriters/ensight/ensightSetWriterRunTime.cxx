#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <ensightSetWriter.hxx>

#include <writers.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSetWriters(ensightSetWriter);
}

// ************************************************************************* //
