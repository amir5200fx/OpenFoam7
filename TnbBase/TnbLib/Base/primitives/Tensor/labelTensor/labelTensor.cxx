#include <labelTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelTensor::vsType::typeName = "labelTensor";

template<>
const char* const tnbLib::labelTensor::vsType::componentNames[] =
{
	"xx", "xy", "xz",
	"yx", "yy", "yz",
	"zx", "zy", "zz"
};

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::zero
(
	labelTensor::uniform(0)
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::one
(
	labelTensor::uniform(1)
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::max
(
	labelTensor::uniform(labelMax)
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::min
(
	labelTensor::uniform(-labelMax)
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::rootMax
(
	labelTensor::uniform(sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelTensor tnbLib::labelTensor::vsType::rootMin
(
	labelTensor::uniform(-sqrt(scalar(labelMax)))
);


// ************************************************************************* //