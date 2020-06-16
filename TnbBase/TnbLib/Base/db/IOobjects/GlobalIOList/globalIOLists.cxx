#include <globalIOLists.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameWithName(labelGlobalIOList, "labelList");
	defineTemplateTypeNameWithName(scalarGlobalIOList, "scalarList");
	defineTemplateTypeNameWithName(vectorGlobalIOList, "vectorList");
	defineTemplateTypeNameWithName
	(
		sphericalTensorGlobalIOList,
		"sphericalTensorList"
	);
	defineTemplateTypeNameWithName(symmTensorGlobalIOList, "symmTensorList");
	defineTemplateTypeNameWithName(tensorGlobalIOList, "tensorList");
}

// ************************************************************************* //