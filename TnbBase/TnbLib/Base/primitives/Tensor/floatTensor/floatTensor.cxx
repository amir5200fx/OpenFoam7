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
	tnbLib::floatTensor::uniform(0)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::one
(
	tnbLib::floatTensor::uniform(1)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::max
(
	tnbLib::floatTensor::uniform(tnbLib::floatScalarVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::min
(
	tnbLib::floatTensor::uniform(-tnbLib::floatScalarVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::rootMax
(
	tnbLib::floatTensor::uniform(tnbLib::floatScalarRootVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::vsType::rootMin
(
	tnbLib::floatTensor::uniform(-tnbLib::floatScalarRootVGreat)
);

template<>
const tnbLib::floatTensor tnbLib::floatTensor::I
(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);


// ************************************************************************* //