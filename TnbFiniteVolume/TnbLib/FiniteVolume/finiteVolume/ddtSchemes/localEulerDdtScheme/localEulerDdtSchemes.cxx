#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <localEulerDdtScheme.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvDdtScheme(localEulerDdtScheme)

// ************************************************************************* //