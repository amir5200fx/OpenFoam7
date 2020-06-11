#include <sphericalTensor2D.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::sphericalTensor2D::vsType::typeName
(
	"sphericalTensor2D"
);

template<>
const char* const tnbLib::sphericalTensor2D::vsType::componentNames[] =
{
	"ii"
};

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::vsType::zero
(
	sphericalTensor2D::uniform(0)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::one
(
	sphericalTensor2D::uniform(1)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::max
(
	sphericalTensor2D::uniform(vGreat)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::min
(
	sphericalTensor2D::uniform(-vGreat)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::rootMax
(
	sphericalTensor2D::uniform(rootVGreat)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::vsType::rootMin
(
	sphericalTensor2D::uniform(-rootVGreat)
);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::I(1);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::oneThirdI(1.0 / 3.0);

template<>
const tnbLib::sphericalTensor2D tnbLib::sphericalTensor2D::twoThirdsI(2.0 / 3.0);


// ************************************************************************* //