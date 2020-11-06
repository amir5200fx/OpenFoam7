#define FoamDimensionedField_EXPORT_DEFINE
#include <surfPointFields.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const word surfPointLabelField::typeName("surfPointLabelField");

	template<>
	const word surfPointScalarField::typeName("surfPointScalarField");

	template<>
	const word surfPointVectorField::typeName("surfPointVectorField");

	template<>
	const word surfPointSphericalTensorField::typeName
	(
		"surfPointSphericalTensorField"
	);

	template<>
	const word surfPointSymmTensorField::typeName("surfPointSymmTensorField");

	template<>
	const word surfPointTensorField::typeName("surfPointTensorField");

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //