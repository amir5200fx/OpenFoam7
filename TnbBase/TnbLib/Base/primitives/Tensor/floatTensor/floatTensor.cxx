#include <floatTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::floatTensor::vsType::typeName = "floatTensor";

template<>
const char* const tnbLib::floatTensor::vsType::componentNames[] =
{
	"xx", "xy", "xz",
	"yx", "yy", "yz",
	"zx", "zy", "zz"
};

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::zero
(
	floatTensor::uniform(0)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::one
(
	floatTensor::uniform(1)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::max
(
	floatTensor::uniform(floatScalarVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::min
(
	floatTensor::uniform(-floatScalarVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::rootMax
(
	floatTensor::uniform(floatScalarRootVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::rootMin
(
	floatTensor::uniform(-floatScalarRootVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::I
(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);


// ************************************************************************* //