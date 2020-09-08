#pragma once
#include <limitedSurfaceInterpolationScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <upwind.hxx>

#include <Time.hxx>  //- added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::multivariateSelectionScheme<Type>::multivariateSelectionScheme
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
	faceFlux_(faceFlux),
	weights_
	(
		IOobject
		(
			"multivariateWeights",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimless
	)
{
	typename multivariateSurfaceInterpolationScheme<Type>::
		fieldTable::const_iterator iter = this->fields().begin();

	surfaceScalarField limiter
	(
		limitedSurfaceInterpolationScheme<Type>::New
		(
			mesh,
			faceFlux_,
			schemes_.lookup(iter()->name())
		)().limiter(*iter())
	);

	for (++iter; iter != this->fields().end(); ++iter)
	{
		limiter = min
		(
			limiter,
			limitedSurfaceInterpolationScheme<Type>::New
			(
				mesh,
				faceFlux_,
				schemes_.lookup(iter()->name())
			)().limiter(*iter())
		);
	}

	weights_ =
		limiter * mesh.surfaceInterpolation::weights()
		+ (scalar(1) - limiter)*upwind<Type>(mesh, faceFlux_).weights();
}


// ************************************************************************* //