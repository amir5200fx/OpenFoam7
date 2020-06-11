#include <labelSphericalTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::labelSphericalTensor::vsType::typeName
(
	"labelSphericalTensor"
);

template<>
const char* const tnbLib::labelSphericalTensor::vsType::componentNames[] =
{
	"ii"
};

template<>
const tnbLib::labelSphericalTensor
tnbLib::labelSphericalTensor::vsType::vsType::zero
(
	labelSphericalTensor::uniform(0)
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::vsType::one
(
	labelSphericalTensor::uniform(1)
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::vsType::max
(
	labelSphericalTensor::uniform(labelMax)
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::vsType::min
(
	labelSphericalTensor::uniform(-labelMax)
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::vsType::rootMax
(
	labelSphericalTensor::uniform(sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::vsType::rootMin
(
	labelSphericalTensor::uniform(-sqrt(scalar(labelMax)))
);

template<>
const tnbLib::labelSphericalTensor tnbLib::labelSphericalTensor::I(1);


// ************************************************************************* //