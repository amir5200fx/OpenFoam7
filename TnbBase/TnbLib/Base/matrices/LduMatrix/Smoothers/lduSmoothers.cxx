#include <TGaussSeidelSmoother.hxx>

#include <fieldTypes.hxx>

#define makeLduSmoothers(Type, DType, LUType)                                  \
                                                                               \
    makeLduSmoother(TGaussSeidelSmoother, Type, DType, LUType);                \
    makeLduSymSmoother(TGaussSeidelSmoother, Type, DType, LUType);             \
    makeLduAsymSmoother(TGaussSeidelSmoother, Type, DType, LUType);

namespace tnbLib
{
	makeLduSmoothers(scalar, scalar, scalar);
	makeLduSmoothers(vector, scalar, scalar);
	makeLduSmoothers(sphericalTensor, scalar, scalar);
	makeLduSmoothers(symmTensor, scalar, scalar);
	makeLduSmoothers(tensor, scalar, scalar);
};


// ************************************************************************* //