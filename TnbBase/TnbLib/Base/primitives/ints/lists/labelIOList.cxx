#include <labelIOList.hxx>

#include <token.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<label>, labelList);
	addCompoundToRunTimeSelectionTable(List<label>, labelList);

	defineTemplateTypeNameAndDebugWithName(labelIOList, "labelList", 0);
}

// ************************************************************************* //