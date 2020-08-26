#include <correctorConvergenceControl.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(correctorConvergenceControl, 0);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::correctorConvergenceControl::getNSolves
(
	const fvMesh& mesh,
	const word& fieldName,
	label& n
)
{
	getNTypeSolves<scalar>(mesh, fieldName, n);
	getNTypeSolves<vector>(mesh, fieldName, n);
	getNTypeSolves<sphericalTensor>(mesh, fieldName, n);
	getNTypeSolves<symmTensor>(mesh, fieldName, n);
	getNTypeSolves<tensor>(mesh, fieldName, n);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::correctorConvergenceControl::correctorConvergenceControl
(
	const solutionControl& control,
	const word& loopName
)
	:
	control_(control),
	loopName_(loopName)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::correctorConvergenceControl::~correctorConvergenceControl()
{}


// ************************************************************************* //