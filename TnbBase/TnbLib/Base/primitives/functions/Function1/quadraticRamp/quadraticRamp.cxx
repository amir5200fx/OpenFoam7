#include <quadraticRamp.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{
		makeScalarFunction1(quadraticRamp);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Function1Types::quadraticRamp::quadraticRamp
(
	const word& entryName,
	const dictionary& dict
)
	:
	ramp(entryName, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::quadraticRamp::~quadraticRamp()
{}


// ************************************************************************* //