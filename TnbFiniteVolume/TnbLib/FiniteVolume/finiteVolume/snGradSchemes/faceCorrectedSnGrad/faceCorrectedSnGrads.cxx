#include <faceCorrectedSnGrad.hxx>

#include <fvMesh.hxx>

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