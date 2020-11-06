#define FoamNamedEnum_EXPORT_DEFINE
#include <topoSetSource.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::topoSetSource::setAction,
		8
		>::names[] =
	{
		"clear",
		"new",
		"invert",
		"add",
		"delete",
		"subset",
		"list",
		"remove"
	};
}