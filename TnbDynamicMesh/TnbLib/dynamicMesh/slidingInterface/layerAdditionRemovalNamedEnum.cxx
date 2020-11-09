#define FoamNamedEnum_EXPORT_DEFINE
#include <slidingInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
	defineTypeNameAndDebug(slidingInterface, 0);
	addToRunTimeSelectionTable
	(
		polyMeshModifier,
		slidingInterface,
		dictionary
	);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::slidingInterface::typeOfMatch,
		2
		>::names[] =
	{
		"integral",
		"partial"
	};
}


const tnbLib::NamedEnum<tnbLib::slidingInterface::typeOfMatch, 2>
tnbLib::slidingInterface::typeOfMatchNames_;