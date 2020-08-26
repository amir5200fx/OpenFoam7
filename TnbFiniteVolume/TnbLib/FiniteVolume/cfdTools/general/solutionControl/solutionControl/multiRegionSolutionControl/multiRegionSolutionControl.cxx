#include <multiRegionSolutionControl.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(multiRegionSolutionControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::multiRegionSolutionControl::multiRegionSolutionControl
(
	const Time& time,
	const word& algorithmName
)
	:
	solutionControl(time, time, algorithmName),
	solution_(time)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::multiRegionSolutionControl::~multiRegionSolutionControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::dictionary& tnbLib::multiRegionSolutionControl::dict() const
{
	return solution_.subDict(algorithmName_);
}


// ************************************************************************* //