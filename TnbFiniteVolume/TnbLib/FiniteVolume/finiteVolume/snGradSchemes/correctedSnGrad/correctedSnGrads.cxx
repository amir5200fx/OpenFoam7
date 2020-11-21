#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <correctedSnGrad.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeSnGradScheme(correctedSnGrad)

template<>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::fv::correctedSnGrad<tnbLib::scalar>::correction
(
	const volScalarField& vsf
) const
{
	return fullGradCorrection(vsf);
}


template<>
tnbLib::tmp<tnbLib::surfaceVectorField>
tnbLib::fv::correctedSnGrad<tnbLib::vector>::correction
(
	const volVectorField& vvf
) const
{
	return fullGradCorrection(vvf);
}


// ************************************************************************* //