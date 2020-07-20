#include <multivariateSelectionScheme.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(multivariateSelectionScheme<scalar>, 0);

	multivariateSurfaceInterpolationScheme<scalar>::addIstreamConstructorToTable
		<multivariateSelectionScheme<scalar>>
		addMultivariateSelectionSchemeScalarConstructorToTable_;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //