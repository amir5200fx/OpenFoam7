#include <spatialVector.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::spatialVector::vsType::typeName = "spatialVector";

template<>
const char* const tnbLib::spatialVector::vsType::componentNames[] =
{
	"wx", "wy", "wz", "lx", "ly", "lz"
};

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::zero
(
	tnbLib::spatialVector::uniform(0)
);

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::one
(
	spatialVector::uniform(1)
);

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::max
(
	spatialVector::uniform(vGreat)
);

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::min
(
	spatialVector::uniform(-vGreat)
);

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::rootMax
(
	spatialVector::uniform(rootVGreat)
);

template<>
const tnbLib::spatialVector tnbLib::spatialVector::vsType::rootMin
(
	spatialVector::uniform(-rootVGreat)
);


// ************************************************************************* //