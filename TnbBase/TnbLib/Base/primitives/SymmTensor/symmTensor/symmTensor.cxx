#include <symmTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::symmTensor::vsType::typeName = "symmTensor";

template<>
const char* const tnbLib::symmTensor::vsType::componentNames[] =
{
	"xx", "xy", "xz",
		  "yy", "yz",
				"zz"
};

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::vsType::zero
(
	symmTensor::uniform(0)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::one
(
	symmTensor::uniform(1)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::max
(
	symmTensor::uniform(vGreat)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::min
(
	symmTensor::uniform(-vGreat)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::rootMax
(
	symmTensor::uniform(rootVGreat)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::vsType::rootMin
(
	symmTensor::uniform(-rootVGreat)
);

template<>
const tnbLib::symmTensor tnbLib::symmTensor::I
(
	1, 0, 0,
	1, 0,
	1
);


// ************************************************************************* //