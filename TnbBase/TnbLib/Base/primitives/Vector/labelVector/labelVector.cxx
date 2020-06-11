#include <labelVector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelVector::vsType::typeName = "labelVector";

template<>
const char* const tnbLib::labelVector::vsType::componentNames[] =
{
	"x", "y", "z"
};

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::zero
(
	labelVector::uniform(0)
);

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::one
(
	labelVector::uniform(1)
);

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::max
(
	labelVector::uniform(labelMax)
);

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::min
(
	labelVector::uniform(-labelMax)
);

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::rootMax
(
	labelVector::uniform(sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelVector tnbLib::labelVector::vsType::rootMin
(
	labelVector::uniform(-sqrt(scalar(labelMax)))
);


// ************************************************************************* //