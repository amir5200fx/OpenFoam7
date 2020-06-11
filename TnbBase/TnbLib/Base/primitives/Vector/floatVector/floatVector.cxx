#include <floatVector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::floatVector::vsType::typeName = "floatVector";

template<>
const char* const tnbLib::floatVector::vsType::componentNames[] =
{
	"x", "y", "z"
};

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::zero
(
	floatVector::uniform(0)
);

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::one
(
	floatVector::uniform(1)
);

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::max
(
	floatVector::uniform(floatScalarVGreat)
);

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::min
(
	floatVector::uniform(-floatScalarVGreat)
);

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::rootMax
(
	floatVector::uniform(floatScalarRootVGreat)
);

template<>
const tnbLib::floatVector tnbLib::floatVector::vsType::rootMin
(
	floatVector::uniform(-floatScalarRootVGreat)
);


// ************************************************************************* //