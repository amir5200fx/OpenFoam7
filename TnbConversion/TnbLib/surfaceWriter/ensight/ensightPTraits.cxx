#include <ensightPTraits.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::ensightPTraits<tnbLib::scalar>::typeName =
tnbLib::pTraits<tnbLib::scalar>::typeName;

const char* const tnbLib::ensightPTraits<tnbLib::vector>::typeName =
tnbLib::pTraits<tnbLib::vector>::typeName;

const char* const tnbLib::ensightPTraits<tnbLib::sphericalTensor>::typeName =
tnbLib::pTraits<tnbLib::scalar>::typeName;

const char* const tnbLib::ensightPTraits<tnbLib::symmTensor>::typeName =
"tensor symm";

const char* const tnbLib::ensightPTraits<tnbLib::tensor>::typeName =
"tensor asym";


// ************************************************************************* //