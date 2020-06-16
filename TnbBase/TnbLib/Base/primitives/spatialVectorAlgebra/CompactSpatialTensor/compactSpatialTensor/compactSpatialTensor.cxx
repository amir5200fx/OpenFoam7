#include <compactSpatialTensor.hxx>

#include <CompactSpatialTensorT.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::compactSpatialTensor::vsType::typeName =
"compactSpatialTensor";

template<>
const char* const tnbLib::compactSpatialTensor::vsType::componentNames[] =
{
	"Exx",  "Exy",  "Exz",
	"Eyx",  "Eyy",  "Eyz",
	"Ezx",  "Ezy",  "Ezz",

	"Erxx", "Erxy", "Erxz",
	"Eryx", "Eryy", "Eryz",
	"Erzx", "Erzy", "Erzz",
};

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::zero
(
	tnbLib::compactSpatialTensor::uniform(0)
);

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::one
(
	compactSpatialTensor::uniform(1)
);

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::max
(
	compactSpatialTensor::uniform(vGreat)
);

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::min
(
	compactSpatialTensor::uniform(-vGreat)
);

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::rootMax
(
	compactSpatialTensor::uniform(rootVGreat)
);

template<>
const tnbLib::compactSpatialTensor tnbLib::compactSpatialTensor::vsType::rootMin
(
	compactSpatialTensor::uniform(-rootVGreat)
);


// ************************************************************************* //