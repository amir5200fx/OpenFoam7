#define FoamNamedEnum_EXPORT_DEFINE
#include <indexedVertexEnum.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char*
tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexType, 15>::names[] =
{
	"Unassigned",
	"Internal",
	"InternalNearBoundary",
	"InternalSurface",
	"InternalSurfaceBaffle",
	"ExternalSurfaceBaffle",
	"InternalFeatureEdge",
	"InternalFeatureEdgeBaffle",
	"ExternalFeatureEdgeBaffle",
	"InternalFeaturePoint",
	"ExternalSurface",
	"ExternalFeatureEdge",
	"ExternalFeaturePoint",
	"Far",
	"Constrained"
};

const tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexType, 15>
tnbLib::indexedVertexEnum::vertexTypeNames_;

template<>
const char*
tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexMotion, 2>::names[] =
{
	"fixed",
	"movable"
};

const tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexMotion, 2>
vertexMotionNames_;