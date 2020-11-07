#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <boundedConvectionScheme.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvConvectionScheme(boundedConvectionScheme)

// ************************************************************************* //