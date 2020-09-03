#include <solution.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class FieldType>
void tnbLib::solution::cachePrintMessage
(
	const char* message,
	const word& name,
	const FieldType& vf
)
{
	if (solution::debug)
	{
		Info << "Cache: " << message << token::SPACE << name
			<< ", originating from " << vf.name()
			<< " event No. " << vf.eventNo()
			<< endl;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //