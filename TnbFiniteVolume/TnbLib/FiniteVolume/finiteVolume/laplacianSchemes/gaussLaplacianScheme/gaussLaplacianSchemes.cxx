#include <gaussLaplacianScheme.hxx>
#include <fvMesh.hxx>

#include <fvcDiv.hxx>  // added by amir
#include <fvMatrix.hxx>   // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvLaplacianScheme(gaussLaplacianScheme)

#define declareFvmLaplacianScalarGamma(Type)                                   \
                                                                               \
template<>                                                                     \
tnbLib::tmp<tnbLib::fvMatrix<tnbLib::Type>>                                          \
tnbLib::fv::gaussLaplacianScheme<tnbLib::Type, tnbLib::scalar>::fvmLaplacian         \
(                                                                              \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>& gamma,           \
    const GeometricField<Type, fvPatchField, volMesh>& vf                      \
)                                                                              \
{                                                                              \
    const fvMesh& mesh = this->mesh();                                         \
                                                                               \
    GeometricField<scalar, fvsPatchField, surfaceMesh> gammaMagSf              \
    (                                                                          \
        gamma*mesh.magSf()                                                     \
    );                                                                         \
                                                                               \
    tmp<fvMatrix<Type>> tfvm = fvmLaplacianUncorrected                         \
    (                                                                          \
        gammaMagSf,                                                            \
        this->tsnGradScheme_().deltaCoeffs(vf),                                \
        vf                                                                     \
    );                                                                         \
    fvMatrix<Type>& fvm = tfvm.ref();                                          \
                                                                               \
    if (this->tsnGradScheme_().corrected())                                    \
    {                                                                          \
        if (mesh.fluxRequired(vf.name()))                                      \
        {                                                                      \
            fvm.faceFluxCorrectionPtr() = new                                  \
            GeometricField<Type, fvsPatchField, surfaceMesh>                   \
            (                                                                  \
                gammaMagSf*this->tsnGradScheme_().correction(vf)               \
            );                                                                 \
                                                                               \
            fvm.source() -=                                                    \
                mesh.V()*                                                      \
                fvc::div                                                       \
                (                                                              \
                    *fvm.faceFluxCorrectionPtr()                               \
                )().primitiveField();                                          \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            fvm.source() -=                                                    \
                mesh.V()*                                                      \
                fvc::div                                                       \
                (                                                              \
                    gammaMagSf*this->tsnGradScheme_().correction(vf)           \
                )().primitiveField();                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    return tfvm;                                                               \
}                                                                              \
                                                                               \
                                                                               \
template<>                                                                     \
tnbLib::tmp<tnbLib::GeometricField<tnbLib::Type, tnbLib::fvPatchField, tnbLib::volMesh>> \
tnbLib::fv::gaussLaplacianScheme<tnbLib::Type, tnbLib::scalar>::fvcLaplacian         \
(                                                                              \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>& gamma,           \
    const GeometricField<Type, fvPatchField, volMesh>& vf                      \
)                                                                              \
{                                                                              \
    const fvMesh& mesh = this->mesh();                                         \
                                                                               \
    tmp<GeometricField<Type, fvPatchField, volMesh>> tLaplacian                \
    (                                                                          \
        fvc::div(gamma*this->tsnGradScheme_().snGrad(vf)*mesh.magSf())         \
    );                                                                         \
                                                                               \
    tLaplacian.ref().rename                                                    \
    (                                                                          \
        "laplacian(" + gamma.name() + ',' + vf.name() + ')'                    \
    );                                                                         \
                                                                               \
    return tLaplacian;                                                         \
}


declareFvmLaplacianScalarGamma(scalar);
declareFvmLaplacianScalarGamma(vector);
declareFvmLaplacianScalarGamma(sphericalTensor);
declareFvmLaplacianScalarGamma(symmTensor);
declareFvmLaplacianScalarGamma(tensor);


// ************************************************************************* //