#include <interpolationPointMVC.hxx>

#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationPointMVC<Type>::interpolationPointMVC
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi),
	psip_
	(
		volPointInterpolation::New(psi.mesh()).interpolate
		(
			psi,
			"volPointInterpolate(" + psi.name() + ')',
			true            // use cache
		)
	)
{}


// ************************************************************************* //