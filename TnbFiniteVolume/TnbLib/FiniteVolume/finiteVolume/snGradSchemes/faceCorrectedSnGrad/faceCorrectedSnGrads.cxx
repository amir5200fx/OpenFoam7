#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <faceCorrectedSnGrad.hxx>

#include <fvMesh.hxx>
#include <GeometricFields.hxx>  // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeSnGradScheme(faceCorrectedSnGrad)


template<>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::fv::faceCorrectedSnGrad<tnbLib::scalar>::correction
(
	const volScalarField& vsf
) const
{
	return fullGradCorrection(vsf);
}


template<>
tnbLib::tmp<tnbLib::surfaceVectorField>
tnbLib::fv::faceCorrectedSnGrad<tnbLib::vector>::correction
(
	const volVectorField& vvf
) const
{
	return fullGradCorrection(vvf);
}


// ************************************************************************* //