#include <LduMatrixTemplate.hxx>

#include <fieldTypes.hxx>

namespace tnbLib
{
	makeLduMatrix(scalar, scalar, scalar);
	makeLduMatrix(vector, scalar, scalar);
	makeLduMatrix(sphericalTensor, scalar, scalar);
	makeLduMatrix(symmTensor, scalar, scalar);
	makeLduMatrix(tensor, scalar, scalar);
};


// ************************************************************************* //