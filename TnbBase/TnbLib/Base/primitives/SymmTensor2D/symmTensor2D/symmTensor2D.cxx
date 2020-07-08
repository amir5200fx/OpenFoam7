#include <symmTensor2D.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::symmTensor2D::vsType::typeName = "symmTensor2D";

template<>
const char* const tnbLib::symmTensor2D::vsType::componentNames[] =
{
	"xx", "xy",
		  "yy"
};

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::vsType::zero
(
	symmTensor2D::uniform(0)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::one
(
	symmTensor2D::uniform(1)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::max
(
	symmTensor2D::uniform(vGreat)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::min
(
	symmTensor2D::uniform(-vGreat)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::rootMax
(
	symmTensor2D::uniform(rootVGreat)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::vsType::rootMin
(
	symmTensor2D::uniform(-rootVGreat)
);

template<>
const tnbLib::symmTensor2D tnbLib::symmTensor2D::I
(
	1, 0,
	1
);


// ************************************************************************* //