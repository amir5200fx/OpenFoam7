#include <edgeIOList.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineCompoundTypeName(List<edge>, edgeList);
	addCompoundToRunTimeSelectionTable(List<edge>, edgeList);

	defineTemplateTypeNameAndDebugWithName(edgeIOList, "edgeList", 0);
	defineTemplateTypeNameAndDebugWithName(edgeCompactIOList, "edgeCompactList", 0);
}

// ************************************************************************* //