#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <CodedSource.hxx>

#include <makeFvOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvOption(CodedSource, scalar);
makeFvOption(CodedSource, vector);
makeFvOption(CodedSource, sphericalTensor);
makeFvOption(CodedSource, symmTensor);
makeFvOption(CodedSource, tensor);


// ************************************************************************* //