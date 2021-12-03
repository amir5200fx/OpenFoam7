

template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::
wRatioByP() const
{
    const dimensionedScalar Wi
    (
        "W",
        dimMass / dimMoles,
        this->thermo_.composition().Wi(saturatedIndex_)
    );

    return Wi / this->thermo_.W() / this->thermo_.p();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::Saturated
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    InterfaceCompositionModel<Thermo, OtherThermo>(dict, pair),
    saturatedName_(this->speciesNames_[0]),
    saturatedIndex_
    (
        this->thermo_.composition().species()[saturatedName_]
    ),
    saturationModel_
    (
        saturationModel::New
        (
            dict.subDict("saturationPressure"),
            pair.phase1().mesh()
        )
    )
{
    if (this->speciesNames_.size() != 1)
    {
        FatalErrorInFunction
            << "Saturated model is suitable for one species only."
            << exit(FatalError);
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::~Saturated()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
void
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::update
(
    const volScalarField& Tf
)
{}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::Yf
(
    const word& speciesName,
    const volScalarField& Tf
) const
{
    if (saturatedName_ == speciesName)
    {
        return wRatioByP() * saturationModel_->pSat(Tf);
    }
    else
    {
        const label speciesIndex
        (
            this->thermo_.composition().species()[speciesName]
        );

        return
            this->thermo_.Y()[speciesIndex]
            * (scalar(1) - wRatioByP() * saturationModel_->pSat(Tf))
            / max(scalar(1) - this->thermo_.Y()[saturatedIndex_], small);
    }
}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::interfaceCompositionModels::Saturated<Thermo, OtherThermo>::YfPrime
(
    const word& speciesName,
    const volScalarField& Tf
) const
{
    if (saturatedName_ == speciesName)
    {
        return wRatioByP() * saturationModel_->pSatPrime(Tf);
    }
    else
    {
        const label speciesIndex
        (
            this->thermo_.composition().species()[speciesName]
        );

        return
            -this->thermo_.Y()[speciesIndex]
            * wRatioByP() * saturationModel_->pSatPrime(Tf)
            / max(scalar(1) - this->thermo_.Y()[saturatedIndex_], small);
    }
}


