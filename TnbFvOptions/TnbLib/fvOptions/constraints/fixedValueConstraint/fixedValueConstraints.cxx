#include <makeFvOption.hxx>
#include <FixedValueConstraint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvOption(FixedValueConstraint, scalar);
makeFvOption(FixedValueConstraint, vector);
makeFvOption(FixedValueConstraint, sphericalTensor);
makeFvOption(FixedValueConstraint, symmTensor);
makeFvOption(FixedValueConstraint, tensor);

// ************************************************************************* //