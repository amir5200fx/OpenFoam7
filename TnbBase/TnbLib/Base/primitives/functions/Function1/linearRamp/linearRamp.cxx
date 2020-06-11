#include <linearRamp.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{
		makeScalarFunction1(linearRamp);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Function1Types::linearRamp::linearRamp
(
	const word& entryName,
	const dictionary& dict
)
	:
	ramp(entryName, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::linearRamp::~linearRamp()
{}


// ************************************************************************* //