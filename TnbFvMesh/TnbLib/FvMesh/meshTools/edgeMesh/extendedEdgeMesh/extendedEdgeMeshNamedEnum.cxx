#define FoamNamedEnum_EXPORT_DEFINE
#include <extendedEdgeMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::extendedEdgeMesh::pointStatus,
		4
		>::names[] =
	{
		"convex",
		"concave",
		"mixed",
		"nonFeature"
	};

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::extendedEdgeMesh::edgeStatus,
		6
		>::names[] =
	{
		"external",
		"internal",
		"flat",
		"open",
		"multiple",
		"none"
	};

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::extendedEdgeMesh::sideVolumeType,
		4
		>::names[] =
	{
		"inside",
		"outside",
		"both",
		"neither"
	};
}