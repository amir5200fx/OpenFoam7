#include <vector2D.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::vector2D::vsType::typeName = "vector2D";

template<>
const char* const tnbLib::vector2D::vsType::componentNames[] = { "x", "y" };

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::vsType::zero
(
	vector2D::uniform(0)
);

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::one
(
	vector2D::uniform(1)
);

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::max
(
	vector2D::uniform(vGreat)
);

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::min
(
	vector2D::uniform(-vGreat)
);

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::rootMax
(
	vector2D::uniform(rootVGreat)
);

template<>
const tnbLib::vector2D tnbLib::vector2D::vsType::rootMin
(
	vector2D::uniform(-rootVGreat)
);


// ************************************************************************* //