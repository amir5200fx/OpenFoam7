#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <SemiImplicitSource.hxx>

#include <makeFvOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvOption(SemiImplicitSource, scalar);
makeFvOption(SemiImplicitSource, vector);
makeFvOption(SemiImplicitSource, sphericalTensor);
makeFvOption(SemiImplicitSource, symmTensor);
makeFvOption(SemiImplicitSource, tensor);


// ************************************************************************* //