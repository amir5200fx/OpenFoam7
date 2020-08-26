#include <solidNoLoopControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solidNoLoopControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidNoLoopControl::solidNoLoopControl
(
	fvMesh& mesh,
	const word& algorithmName,
	const pimpleLoop& loop
)
	:
	nonOrthogonalSolutionControl(mesh, algorithmName),
	singleRegionConvergenceControl
	(
		static_cast<singleRegionSolutionControl&>(*this)
	),
	singleRegionCorrectorConvergenceControl
	(
		static_cast<singleRegionSolutionControl&>(*this),
		"outerCorrector"
	),
	loop_(loop)
{
	read();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidNoLoopControl::~solidNoLoopControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::solidNoLoopControl::read()
{
	return
		nonOrthogonalSolutionControl::read()
		&& readResidualControls()
		&& readCorrResidualControls();
}


bool tnbLib::solidNoLoopControl::isFinal() const
{
	return loop_.finalPimpleIter() && finalNonOrthogonalIter();
}


// ************************************************************************* //