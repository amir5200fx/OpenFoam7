#include <indexedVertexEnum.hxx>

#include <Pstream.hxx>

//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//template<>
//const char*
//tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexType, 15>::names[] =
//{
//	"Unassigned",
//	"Internal",
//	"InternalNearBoundary",
//	"InternalSurface",
//	"InternalSurfaceBaffle",
//	"ExternalSurfaceBaffle",
//	"InternalFeatureEdge",
//	"InternalFeatureEdgeBaffle",
//	"ExternalFeatureEdgeBaffle",
//	"InternalFeaturePoint",
//	"ExternalSurface",
//	"ExternalFeatureEdge",
//	"ExternalFeaturePoint",
//	"Far",
//	"Constrained"
//};
//
//const tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexType, 15>
//tnbLib::indexedVertexEnum::vertexTypeNames_;


//template<>
//const char*
//tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexMotion, 2>::names[] =
//{
//	"fixed",
//	"movable"
//};
//
//const tnbLib::NamedEnum<tnbLib::indexedVertexEnum::vertexMotion, 2>
//vertexMotionNames_;


FoamFoamyMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tnbLib::indexedVertexEnum::vertexType& v
	)
{
	os << static_cast<int>(v);

	return os;
}

FoamFoamyMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	tnbLib::indexedVertexEnum::vertexType& v
	)
{
	int type;
	is >> type;

	v = static_cast<tnbLib::indexedVertexEnum::vertexType>(type);

	return is;
}

// ************************************************************************* //