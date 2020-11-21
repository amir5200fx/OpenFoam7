#define FoamNamedEnum_EXPORT_DEFINE
#include <faceToPoint.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceToPoint::faceAction,
		1
		>::names[] =
	{
		"all"
	};
}