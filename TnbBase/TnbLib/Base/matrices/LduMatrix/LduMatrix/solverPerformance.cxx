#include <solverPerformance.hxx>

// added by amir
#include <LduMatrixTemplate.hxx>
#include <fieldTypes.hxx>

namespace tnbLib
{
	makeSolverPerformance(scalar);
	makeSolverPerformance(vector);
	makeSolverPerformance(sphericalTensor);
	makeSolverPerformance(symmTensor);
	makeSolverPerformance(tensor);
};


template<>
tnbLib::SolverPerformance<tnbLib::scalar>
tnbLib::SolverPerformance<tnbLib::scalar>::max()
{
	return *this;
}


// ************************************************************************* //