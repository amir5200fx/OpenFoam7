#include <Residuals.hxx>

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeResiduals(Type)                                                    \
    defineTemplateTypeNameAndDebug(Residuals<Type>, 0);

namespace tnbLib
{
	makeResiduals(scalar);
	makeResiduals(vector);
	makeResiduals(sphericalTensor);
	makeResiduals(symmTensor);
	makeResiduals(tensor);
}

// ************************************************************************* //