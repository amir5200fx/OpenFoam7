#define FoamNamedEnum_EXPORT_DEFINE
#include <conformalVoronoiMesh.hxx>

namespace tnbLib
{

	template<>
	const char* NamedEnum
		<
		conformalVoronoiMesh::dualMeshPointType,
		5
		>::names[] =
	{
		"internal",
		"surface",
		"featureEdge",
		"featurePoint",
		"constrained"
	};
}

const tnbLib::NamedEnum<tnbLib::conformalVoronoiMesh::dualMeshPointType, 5>
tnbLib::conformalVoronoiMesh::dualMeshPointTypeNames_;