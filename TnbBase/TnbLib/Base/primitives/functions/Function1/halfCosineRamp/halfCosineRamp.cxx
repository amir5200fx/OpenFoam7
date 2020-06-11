#include <halfCosineRamp.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{
		makeScalarFunction1(halfCosineRamp);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Function1Types::halfCosineRamp::halfCosineRamp
(
	const word& entryName,
	const dictionary& dict
)
	:
	ramp(entryName, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::halfCosineRamp::~halfCosineRamp()
{}


// ************************************************************************* //