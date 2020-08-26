#include <pimpleNoLoopControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pimpleNoLoopControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pimpleNoLoopControl::pimpleNoLoopControl
(
	fvMesh& mesh,
	const word& algorithmName,
	const pimpleLoop& loop
)
	:
	pisoControl(mesh, algorithmName),
	singleRegionConvergenceControl
	(
		static_cast<singleRegionSolutionControl&>(*this)
	),
	singleRegionCorrectorConvergenceControl
	(
		static_cast<singleRegionSolutionControl&>(*this),
		"outerCorrector"
	),
	loop_(loop),
	simpleRho_(false),
	turbOnFinalIterOnly_(true)
{
	read();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pimpleNoLoopControl::~pimpleNoLoopControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::pimpleNoLoopControl::read()
{
	if
		(
			!pisoControl::read()
			|| !readResidualControls()
			|| !readCorrResidualControls()
			)
	{
		return false;
	}

	// The SIMPLErho keyword is maintained here for backwards compatibility
	simpleRho_ = mesh().steady();
	simpleRho_ = dict().lookupOrDefault<bool>("SIMPLErho", simpleRho_);
	simpleRho_ = dict().lookupOrDefault<bool>("simpleRho", simpleRho_);

	turbOnFinalIterOnly_ =
		dict().lookupOrDefault<bool>("turbOnFinalIterOnly", true);

	return true;
}


bool tnbLib::pimpleNoLoopControl::isFinal() const
{
	return
		(!anyPisoIter() && loop_.finalPimpleIter())
		|| pisoControl::isFinal();
}


// ************************************************************************* //