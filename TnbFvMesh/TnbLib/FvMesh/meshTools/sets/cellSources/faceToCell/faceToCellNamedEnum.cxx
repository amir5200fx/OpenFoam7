#define FoamNamedEnum_EXPORT_DEFINE
#include <faceToCell.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceToCell::faceAction,
		4
		>::names[] =
	{
		"neighbour",
		"owner",
		"any",
		"all"
	};
}