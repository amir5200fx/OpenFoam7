#include <stringIOList.hxx>

#include <token.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<string>, stringList);
	addCompoundToRunTimeSelectionTable(List<string>, stringList);

	defineTemplateTypeNameAndDebugWithName(stringIOList, "stringList", 0);
	defineTemplateTypeNameAndDebugWithName
	(
		stringListIOList,
		"stringListList",
		0
	);
}

// ************************************************************************* //