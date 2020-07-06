#include <PCICG.hxx>
#include <PBiCCCG.hxx>
#include <PBiCICG.hxx>
#include <SmoothSolverTemplate.hxx>
#include <DiagonalSolverTemplate.hxx>  // added by amir
#include <fieldTypes.hxx>

#define makeLduSolvers(Type, DType, LUType)                                    \
                                                                               \
    makeLduSolver(DiagonalSolver, Type, DType, LUType);                        \
    makeLduSymSolver(DiagonalSolver, Type, DType, LUType);                     \
    makeLduAsymSolver(DiagonalSolver, Type, DType, LUType);                    \
                                                                               \
    makeLduSolver(PCICG, Type, DType, LUType);                                 \
    makeLduSymSolver(PCICG, Type, DType, LUType);                              \
                                                                               \
    makeLduSolver(PBiCCCG, Type, DType, LUType);                               \
    makeLduAsymSolver(PBiCCCG, Type, DType, LUType);                           \
                                                                               \
    makeLduSolver(PBiCICG, Type, DType, LUType);                               \
    makeLduAsymSolver(PBiCICG, Type, DType, LUType);                           \
                                                                               \
    makeLduSolver(SmoothSolver, Type, DType, LUType);                          \
    makeLduSymSolver(SmoothSolver, Type, DType, LUType);                       \
    makeLduAsymSolver(SmoothSolver, Type, DType, LUType);

namespace tnbLib
{
	makeLduSolvers(scalar, scalar, scalar);
	makeLduSolvers(vector, scalar, scalar);
	makeLduSolvers(sphericalTensor, scalar, scalar);
	makeLduSolvers(symmTensor, scalar, scalar);
	makeLduSolvers(tensor, scalar, scalar);
};


// ************************************************************************* //