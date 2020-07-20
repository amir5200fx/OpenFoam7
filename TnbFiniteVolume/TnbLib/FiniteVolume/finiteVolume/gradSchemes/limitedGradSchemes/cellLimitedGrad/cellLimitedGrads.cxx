#include <cellLimitedGrad.hxx>
#include <minmodGradientLimiter.hxx>
#include <VenkatakrishnanGradientLimiter.hxx>
#include <cubicGradientLimiter.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeNamedFvLimitedGradTypeScheme(SS, Type, Limiter, Name)              \
    typedef tnbLib::fv::SS<tnbLib::Type, tnbLib::fv::gradientLimiters::Limiter>      \
        SS##Type##Limiter##_;                                                  \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        SS##Type##Limiter##_,                                                  \
        Name,                                                                  \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            gradScheme<Type>::addIstreamConstructorToTable                     \
            <                                                                  \
                SS<Type, gradientLimiters::Limiter>                            \
            > add##SS##Type##Limiter##IstreamConstructorToTable_;              \
        }                                                                      \
    }

#define makeFvLimitedGradTypeScheme(SS, Type, Limiter)                         \
    makeNamedFvLimitedGradTypeScheme(SS##Grad, Type, Limiter, #SS"<"#Limiter">")

#define makeFvLimitedGradScheme(SS, Limiter)                                   \
                                                                               \
    makeFvLimitedGradTypeScheme(SS, scalar, Limiter)                           \
    makeFvLimitedGradTypeScheme(SS, vector, Limiter)


// Default limiter in minmod specified without the limiter name
// for backward compatibility
makeNamedFvLimitedGradTypeScheme(cellLimitedGrad, scalar, minmod, "cellLimited")
makeNamedFvLimitedGradTypeScheme(cellLimitedGrad, vector, minmod, "cellLimited")

makeFvLimitedGradScheme(cellLimited, Venkatakrishnan)
makeFvLimitedGradScheme(cellLimited, cubic)

// ************************************************************************* //