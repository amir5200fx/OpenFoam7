#include <NoPreconditionerTemplate.hxx>
#include <DiagonalPreconditionerTemplate.hxx>
#include <TDILUPreconditioner.hxx>
#include <fieldTypes.hxx>

#define makeLduPreconditioners(Type, DType, LUType)                            \
                                                                               \
    makeLduPreconditioner(NoPreconditioner, Type, DType, LUType);              \
    makeLduSymPreconditioner(NoPreconditioner, Type, DType, LUType);           \
    makeLduAsymPreconditioner(NoPreconditioner, Type, DType, LUType);          \
                                                                               \
    makeLduPreconditioner(DiagonalPreconditioner, Type, DType, LUType);        \
    makeLduSymPreconditioner(DiagonalPreconditioner, Type, DType, LUType);     \
    makeLduAsymPreconditioner(DiagonalPreconditioner, Type, DType, LUType);    \
                                                                               \
    makeLduPreconditioner(TDILUPreconditioner, Type, DType, LUType);           \
    makeLduAsymPreconditioner(TDILUPreconditioner, Type, DType, LUType);

namespace tnbLib
{
	makeLduPreconditioners(scalar, scalar, scalar);
	makeLduPreconditioners(vector, scalar, scalar);
	makeLduPreconditioners(sphericalTensor, scalar, scalar);
	makeLduPreconditioners(symmTensor, scalar, scalar);
	makeLduPreconditioners(tensor, scalar, scalar);
};


// ************************************************************************* //