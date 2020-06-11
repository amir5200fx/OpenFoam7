#include <sphericalTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::sphericalTensor::vsType::typeName = "sphericalTensor";

template<>
const char* const tnbLib::sphericalTensor::vsType::componentNames[] = { "ii" };

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::zero
(
	sphericalTensor::uniform(0)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::one
(
	sphericalTensor::uniform(1)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::max
(
	sphericalTensor::uniform(vGreat)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::min
(
	sphericalTensor::uniform(-vGreat)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::rootMax
(
	sphericalTensor::uniform(rootVGreat)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::vsType::rootMin
(
	sphericalTensor::uniform(-rootVGreat)
);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::I(1);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::oneThirdI(1.0 / 3.0);

template<>
const tnbLib::sphericalTensor tnbLib::sphericalTensor::twoThirdsI(2.0 / 3.0);

// ************************************************************************* //