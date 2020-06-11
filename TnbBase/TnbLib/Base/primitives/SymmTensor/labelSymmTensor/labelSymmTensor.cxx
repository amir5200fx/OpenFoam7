#include <labelSymmTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelSymmTensor::vsType::typeName = "labelSymmTensor";

template<>
const char* const tnbLib::labelSymmTensor::vsType::componentNames[] =
{
	"xx", "xy", "xz",
		  "yy", "yz",
				"zz"
};

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::vsType::zero
(
	labelSymmTensor::uniform(0)
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::one
(
	labelSymmTensor::uniform(1)
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::max
(
	labelSymmTensor::uniform(labelMax)
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::min
(
	labelSymmTensor::uniform(-labelMax)
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::rootMax
(
	labelSymmTensor::uniform(sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::vsType::rootMin
(
	labelSymmTensor::uniform(-sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelSymmTensor tnbLib::labelSymmTensor::I
(
	1, 0, 0,
	1, 0,
	1
);


// ************************************************************************* //