#include <multivariateSurfaceInterpolationScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Define the constructor function hash tables

	defineTemplateRunTimeSelectionTable
	(
		multivariateSurfaceInterpolationScheme<scalar>,
		Istream
	);

	defineTemplateRunTimeSelectionTable
	(
		multivariateSurfaceInterpolationScheme<vector>,
		Istream
	);

	defineTemplateRunTimeSelectionTable
	(
		multivariateSurfaceInterpolationScheme<sphericalTensor>,
		Istream
	);

	defineTemplateRunTimeSelectionTable
	(
		multivariateSurfaceInterpolationScheme<symmTensor>,
		Istream
	);

	defineTemplateRunTimeSelectionTable
	(
		multivariateSurfaceInterpolationScheme<tensor>,
		Istream
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //