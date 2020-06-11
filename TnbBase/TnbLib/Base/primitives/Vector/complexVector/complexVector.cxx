#include <complexVector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::complexVector::vsType::typeName = "complexVector";

template<>
const char* const tnbLib::complexVector::vsType::componentNames[] =
{
	"x", "y", "z"
};

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::zero
(
	complexVector::uniform(complex(0, 0))
);

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::one
(
	complexVector::uniform(complex(1, 1))
);

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::max
(
	complexVector::uniform(complex(vGreat, vGreat))
);

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::min
(
	complexVector::uniform(complex(-vGreat, -vGreat))
);

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::rootMax
(
	complexVector::uniform(complex(rootVGreat, rootVGreat))
);

template<>
const tnbLib::complexVector tnbLib::complexVector::vsType::rootMin
(
	complexVector::uniform(complex(-rootVGreat, -rootVGreat))
);


// ************************************************************************* //