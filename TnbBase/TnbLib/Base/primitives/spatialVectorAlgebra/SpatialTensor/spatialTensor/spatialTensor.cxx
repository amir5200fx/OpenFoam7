#include <spatialTensor.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::spatialTensor::vsType::typeName = "spatialTensor";

template<>
const char* const tnbLib::spatialTensor::vsType::componentNames[] =
{
	"Exx",  "Exy",  "Exz",    "Erxx", "Erxy", "Erxz",
	"Eyx",  "Eyy",  "Eyz",    "Eryx", "Eryy", "Eryz",
	"Ezx",  "Ezy",  "Ezz",    "Erzx", "Erzy", "Erzz"

	"Erxx", "Erxy", "Erxz",   "Exx",  "Exy",  "Exz",
	"Eryx", "Eryy", "Eryz",   "Eyx",  "Eyy",  "Eyz",
	"Erzx", "Erzy", "Erzz",   "Ezx",  "Ezy",  "Ezz"
};

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::zero
(
	tnbLib::spatialTensor::uniform(0)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::one
(
	spatialTensor::uniform(1)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::max
(
	spatialTensor::uniform(vGreat)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::min
(
	spatialTensor::uniform(-vGreat)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::rootMax
(
	spatialTensor::uniform(rootVGreat)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::vsType::rootMin
(
	spatialTensor::uniform(-rootVGreat)
);

template<>
const tnbLib::spatialTensor tnbLib::spatialTensor::I
(
	tnbLib::spatialTensor::identity()
);


// ************************************************************************* //