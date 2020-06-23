#include <pointPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makePointPatchField(pointPatchTypeField)                               \
                                                                               \
defineNamedTemplateTypeNameAndDebug(pointPatchTypeField, 0);                   \
template<>                                                                     \
int pointPatchTypeField::disallowGenericPointPatchField                        \
(                                                                              \
    debug::debugSwitch("disallowGenericPointPatchField", 0)                    \
);                                                                             \
defineTemplateRunTimeSelectionTable(pointPatchTypeField, pointPatch);          \
defineTemplateRunTimeSelectionTable(pointPatchTypeField, patchMapper);         \
defineTemplateRunTimeSelectionTable(pointPatchTypeField, dictionary);

	makePointPatchField(pointPatchScalarField)
		makePointPatchField(pointPatchVectorField)
		makePointPatchField(pointPatchSphericalTensorField)
		makePointPatchField(pointPatchSymmTensorField)
		makePointPatchField(pointPatchTensorField)


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
