#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <multivariateIndependentScheme.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(multivariateIndependentScheme<scalar>, 0);

	multivariateSurfaceInterpolationScheme<scalar>::addIstreamConstructorToTable
		<multivariateIndependentScheme<scalar>>
		addMultivariateIndependentSchemeScalarConstructorToTable_;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //