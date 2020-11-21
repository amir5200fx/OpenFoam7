#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <vtkSetWriter.hxx>

#include <writers.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSetWriters(vtkSetWriter);
}

// ************************************************************************* //