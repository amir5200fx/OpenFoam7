#define FoamNamedEnum_EXPORT_DEFINE
#include <vtkUnstructuredReader.hxx>

namespace  tnbLib
{
	template<>
	const char*
		NamedEnum<vtkUnstructuredReader::vtkDataType, 8>::names[] =
	{
		"int",
		"unsigned_int",
		"long",
		"unsigned_long",
		"float",
		"double",
		"string",
		"vtkIdType"
	};


	template<>
	const char*
		NamedEnum<vtkUnstructuredReader::vtkDataSetType, 3>::names[] =
	{
		"FIELD",
		"SCALARS",
		"VECTORS"
	};


	template<>
	const char*
		NamedEnum<vtkUnstructuredReader::parseMode, 5>::names[] =
	{
		"NOMODE",
		"UNSTRUCTURED_GRID",
		"POLYDATA",
		"CELL_DATA",
		"POINT_DATA"
	};

}