#include <quarterCosineRamp.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{
		makeScalarFunction1(quarterCosineRamp);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Function1Types::quarterCosineRamp::quarterCosineRamp
(
	const word& entryName,
	const dictionary& dict
)
	:
	ramp(entryName, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::quarterCosineRamp::~quarterCosineRamp()
{}


// ************************************************************************* //