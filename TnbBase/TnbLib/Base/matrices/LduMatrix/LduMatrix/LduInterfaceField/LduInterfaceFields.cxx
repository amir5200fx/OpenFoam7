#include <LduInterfaceFieldTemplate.hxx>

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(LduInterfaceField<scalar>, 0);
	defineTemplateTypeNameAndDebug(LduInterfaceField<vector>, 0);
	defineTemplateTypeNameAndDebug
	(
		LduInterfaceField<sphericalTensor>,
		0
	);
	defineTemplateTypeNameAndDebug(LduInterfaceField<symmTensor>, 0);
	defineTemplateTypeNameAndDebug(LduInterfaceField<tensor>, 0);
}

// ************************************************************************* //