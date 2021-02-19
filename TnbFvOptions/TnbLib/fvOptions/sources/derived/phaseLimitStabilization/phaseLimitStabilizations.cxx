#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <PhaseLimitStabilization.hxx>

#include <makeFvOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvOption(PhaseLimitStabilization, scalar);
makeFvOption(PhaseLimitStabilization, vector);
makeFvOption(PhaseLimitStabilization, sphericalTensor);
makeFvOption(PhaseLimitStabilization, symmTensor);
makeFvOption(PhaseLimitStabilization, tensor);


// ************************************************************************* //