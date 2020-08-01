#include <fvcFlux.hxx>

#include <surfaceInterpolate.hxx>
#include <volFields.hxx>  // added by amir
#include <fvMesh.hxx>  // added by amir
#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::flux
(
	const volVectorField& vvf
)
{
	return scheme<vector>
		(
			vvf.mesh(),
			"flux(" + vvf.name() + ')'
			)().dotInterpolate(vvf.mesh().Sf(), vvf);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::flux
(
	const tmp<volVectorField>& tvvf
)
{
	tmp<surfaceScalarField> Flux(fvc::flux(tvvf()));
	tvvf.clear();
	return Flux;
}


// ************************************************************************* //