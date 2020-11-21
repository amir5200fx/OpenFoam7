#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <gnuplotSetWriter.hxx>

#include <writers.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSetWriters(gnuplotSetWriter);
}

// ************************************************************************* //