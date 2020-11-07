#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <fvsPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeFvsPatchField(fvsPatchTypeField)                                   \
                                                                               \
defineNamedTemplateTypeNameAndDebug(fvsPatchTypeField, 0);                     \
template<>                                                                     \
int fvsPatchTypeField::disallowGenericFvsPatchField                            \
(                                                                              \
    debug::debugSwitch("disallowGenericFvsPatchField", 0)                      \
);                                                                             \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, patch);                 \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, patchMapper);           \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, dictionary);

	makeFvsPatchField(fvsPatchScalarField)
		makeFvsPatchField(fvsPatchVectorField)
		makeFvsPatchField(fvsPatchSphericalTensorField)
		makeFvsPatchField(fvsPatchSymmTensorField)
		makeFvsPatchField(fvsPatchTensorField)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //