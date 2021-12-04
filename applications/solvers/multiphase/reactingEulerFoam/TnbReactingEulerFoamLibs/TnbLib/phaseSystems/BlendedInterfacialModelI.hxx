#pragma once
#include <fvc.hxx> // Added by Payvand [12/4/2021 Payvand]
#include <typeInfo.hxx> // Added by Payvand [12/4/2021 Payvand]
#include <fixedValueFvsPatchFields.hxx>  // Added by Payvand [12/4/2021 Payvand]

namespace tnbLib
{

    // * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

    template<>
    inline tmp<tnbLib::volScalarField>
        blendedInterfacialModel::interpolate(tmp<volScalarField> f)
    {
        return f;
    }


    template<>
    inline tmp<tnbLib::surfaceScalarField>
        blendedInterfacialModel::interpolate(tmp<volScalarField> f)
    {
        return fvc::interpolate(f);
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ModelType>
template<class GeoField>
void tnbLib::BlendedInterfacialModel<ModelType>::correctFixedFluxBCs
(
    GeoField& field
) const
{
    typename GeoField::Boundary& fieldBf = field.boundaryFieldRef();

    forAll(phase1_.phi()().boundaryField(), patchi)
    {
        if
            (
                isA<fixedValueFvsPatchScalarField>
                (
                    phase1_.phi()().boundaryField()[patchi]
                    )
                )
        {
            fieldBf[patchi] = Zero;
        }
    }
}


template<class ModelType>
template
<
    class Type,
    template<class> class PatchField,
    class GeoMesh,
    class ... Args
>
tnbLib::tmp<tnbLib::GeometricField<Type, PatchField, GeoMesh>>
tnbLib::BlendedInterfacialModel<ModelType>::evaluate
(
    tmp<GeometricField<Type, PatchField, GeoMesh>>
    (ModelType::* method)(Args ...) const,
    const word& name,
    const dimensionSet& dims,
    const bool subtract,
    Args ... args
) const
{
    typedef GeometricField<scalar, PatchField, GeoMesh> scalarGeoField;
    typedef GeometricField<Type, PatchField, GeoMesh> typeGeoField;

    tmp<scalarGeoField> f1, f2;

    if (model_.valid() || model1In2_.valid())
    {
        f1 =
            blendedInterfacialModel::interpolate<scalarGeoField>
            (
                blending_.f1(phase1_, phase2_)
                );
    }

    if (model_.valid() || model2In1_.valid())
    {
        f2 =
            blendedInterfacialModel::interpolate<scalarGeoField>
            (
                blending_.f2(phase1_, phase2_)
                );
    }

    tmp<typeGeoField> x
    (
        new typeGeoField
        (
            IOobject
            (
                ModelType::typeName + ":" + name,
                phase1_.mesh().time().timeName(),
                phase1_.mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                false
            ),
            phase1_.mesh(),
            dimensioned<Type>("zero", dims, Zero)
        )
    );

    if (model_.valid())
    {
        if (subtract)
        {
            FatalErrorInFunction
                << "Cannot treat an interfacial model with no distinction "
                << "between continuous and dispersed phases as signed"
                << exit(FatalError);
        }

        x.ref() += (model_().*method)(args ...) * (scalar(1) - f1() - f2());
    }

    if (model1In2_.valid())
    {
        x.ref() += (model1In2_().*method)(args ...) * f1;
    }

    if (model2In1_.valid())
    {
        tmp<typeGeoField> dx = (model2In1_().*method)(args ...) * f2;

        if (subtract)
        {
            x.ref() -= dx;
        }
        else
        {
            x.ref() += dx;
        }
    }

    if
        (
            correctFixedFluxBCs_
            && (model_.valid() || model1In2_.valid() || model2In1_.valid())
            )
    {
        correctFixedFluxBCs(x.ref());
    }

    return x;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ModelType>
tnbLib::BlendedInterfacialModel<ModelType>::BlendedInterfacialModel
(
    const phaseModel& phase1,
    const phaseModel& phase2,
    const blendingMethod& blending,
    autoPtr<ModelType> model,
    autoPtr<ModelType> model1In2,
    autoPtr<ModelType> model2In1,
    const bool correctFixedFluxBCs
)
    :
    regIOobject
    (
        IOobject
        (
            IOobject::groupName(typeName, phasePair(phase1, phase2).name()),
            phase1.mesh().time().timeName(),
            phase1.mesh()
        )
    ),
    phase1_(phase1),
    phase2_(phase2),
    blending_(blending),
    model_(model),
    model1In2_(model1In2),
    model2In1_(model2In1),
    correctFixedFluxBCs_(correctFixedFluxBCs)
{}


template<class ModelType>
tnbLib::BlendedInterfacialModel<ModelType>::BlendedInterfacialModel
(
    const phasePair::dictTable& modelTable,
    const blendingMethod& blending,
    const phasePair& pair,
    const orderedPhasePair& pair1In2,
    const orderedPhasePair& pair2In1,
    const bool correctFixedFluxBCs
)
    :
    regIOobject
    (
        IOobject
        (
            IOobject::groupName(typeName, pair.name()),
            pair.phase1().mesh().time().timeName(),
            pair.phase1().mesh()
        )
    ),
    phase1_(pair.phase1()),
    phase2_(pair.phase2()),
    blending_(blending),
    correctFixedFluxBCs_(correctFixedFluxBCs)
{
    if (modelTable.found(pair))
    {
        model_.set
        (
            ModelType::New
            (
                modelTable[pair],
                pair
            ).ptr()
        );
    }

    if (modelTable.found(pair1In2))
    {
        model1In2_.set
        (
            ModelType::New
            (
                modelTable[pair1In2],
                pair1In2
            ).ptr()
        );
    }

    if (modelTable.found(pair2In1))
    {
        model2In1_.set
        (
            ModelType::New
            (
                modelTable[pair2In1],
                pair2In1
            ).ptr()
        );
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ModelType>
tnbLib::BlendedInterfacialModel<ModelType>::~BlendedInterfacialModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ModelType>
bool tnbLib::BlendedInterfacialModel<ModelType>::hasModel
(
    const class phaseModel& phase
) const
{
    return
        &phase == &(phase1_)
        ? model1In2_.valid()
        : model2In1_.valid();
}


template<class ModelType>
const ModelType& tnbLib::BlendedInterfacialModel<ModelType>::model
(
    const class phaseModel& phase
) const
{
    return &phase == &(phase1_) ? model1In2_ : model2In1_;
}


template<class ModelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::K() const
{
    tmp<volScalarField>(ModelType:: * k)() const = &ModelType::K;

    return evaluate(k, "K", ModelType::dimK, false);
}


template<class ModelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::K(const scalar residualAlpha) const
{
    tmp<volScalarField>(ModelType:: * k)(const scalar) const = &ModelType::K;

    return evaluate(k, "K", ModelType::dimK, false, residualAlpha);
}


template<class ModelType>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::Kf() const
{
    return evaluate(&ModelType::Kf, "Kf", ModelType::dimK, false);
}


template<class ModelType>
template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::BlendedInterfacialModel<ModelType>::F() const
{
    return evaluate(&ModelType::F, "F", ModelType::dimF, true);
}


template<class ModelType>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::Ff() const
{
    return evaluate(&ModelType::Ff, "Ff", ModelType::dimF * dimArea, true);
}


template<class ModelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::D() const
{
    return evaluate(&ModelType::D, "D", ModelType::dimD, false);
}


template<class ModelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<ModelType>::dmdt() const
{
    return evaluate(&ModelType::dmdt, "dmdt", ModelType::dimDmdt, false);
}


template<class ModelType>
bool tnbLib::BlendedInterfacialModel<ModelType>::writeData(Ostream& os) const
{
    return os.good();
}


// ************************************************************************* //
