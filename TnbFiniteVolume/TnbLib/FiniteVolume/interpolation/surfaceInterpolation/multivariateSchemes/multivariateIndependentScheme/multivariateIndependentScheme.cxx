#include <multivariateIndependentScheme.hxx>

#include <limitedSurfaceInterpolationScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <upwind.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::multivariateIndependentScheme<Type>::multivariateIndependentScheme
(
	const fvMesh& mesh,
	const typename multivariateSurfaceInterpolationScheme<Type>::
	fieldTable& fields,
	const surfaceScalarField& faceFlux,
	Istream& schemeData
)
	:
	multivariateSurfaceInterpolationScheme<Type>
	(
		mesh,
		fields,
		faceFlux,
		schemeData
		),
	schemes_(schemeData),
	faceFlux_(faceFlux)
{}


// ************************************************************************* //