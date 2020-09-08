#include <correctedSnGrad.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <linear.hxx>
#include <fvcGrad.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fv::correctedSnGrad<Type>::~correctedSnGrad()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::fv::correctedSnGrad<Type>::fullGradCorrection
(
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	const fvMesh& mesh = this->mesh();

	// construct GeometricField<Type, fvsPatchField, surfaceMesh>
	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tssf =
		linear<typename outerProduct<vector, Type>::type>(mesh).dotInterpolate
		(
			mesh.nonOrthCorrectionVectors(),
			gradScheme<Type>::New
			(
				mesh,
				mesh.gradScheme("grad(" + vf.name() + ')')
			)().grad(vf, "grad(" + vf.name() + ')')
		);
	tssf.ref().rename("snGradCorr(" + vf.name() + ')');

	return tssf;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::fv::correctedSnGrad<Type>::correction
(
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	const fvMesh& mesh = this->mesh();

	// construct GeometricField<Type, fvsPatchField, surfaceMesh>
	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tssf
	(
		new GeometricField<Type, fvsPatchField, surfaceMesh>
		(
			IOobject
			(
				"snGradCorr(" + vf.name() + ')',
				vf.instance(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh,
			vf.dimensions()*mesh.nonOrthDeltaCoeffs().dimensions()
			)
	);
	GeometricField<Type, fvsPatchField, surfaceMesh>& ssf = tssf.ref();

	for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
	{
		ssf.replace
		(
			cmpt,
			correctedSnGrad<typename pTraits<Type>::cmptType>(mesh)
			.fullGradCorrection(vf.component(cmpt))
		);
	}

	return tssf;
}


// ************************************************************************* //