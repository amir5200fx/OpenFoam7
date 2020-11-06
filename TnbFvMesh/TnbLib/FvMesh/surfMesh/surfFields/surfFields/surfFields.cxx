#define FoamDimensionedField_EXPORT_DEFINE
#include <surfFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const word surfLabelField::typeName("surfLabelField");

	template<>
	const word surfScalarField::typeName("surfScalarField");

	template<>
	const word surfVectorField::typeName("surfVectorField");

	template<>
	const word surfSphericalTensorField::typeName("surfSphericalTensorField");

	template<>
	const word surfSymmTensorField::typeName("surfSymmTensorField");

	template<>
	const word surfTensorField::typeName("surfTensorField");

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //