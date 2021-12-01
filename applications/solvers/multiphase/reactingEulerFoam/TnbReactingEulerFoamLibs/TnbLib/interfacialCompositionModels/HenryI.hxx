#pragma once
template<class Thermo, class OtherThermo>
tnbLib::interfaceCompositionModels::Henry<Thermo, OtherThermo>::Henry
(
	const dictionary& dict,
	const phasePair& pair
)
	:
	InterfaceCompositionModel<Thermo, OtherThermo>(dict, pair),
	k_(dict.lookup("k")),
	YSolvent_
	(
		IOobject
		(
			IOobject::groupName("YSolvent", pair.name()),
			pair.phase1().mesh().time().timeName(),
			pair.phase1().mesh()
		),
		pair.phase1().mesh(),
		dimensionedScalar(dimless, 1)
	)
{
	if (k_.size() != this->speciesNames_.size())
	{
		FatalErrorInFunction
			<< "Differing number of species and solubilities"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::interfaceCompositionModels::Henry<Thermo, OtherThermo>::~Henry()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
void tnbLib::interfaceCompositionModels::Henry<Thermo, OtherThermo>::update
(
	const volScalarField& Tf
)
{
	YSolvent_ = scalar(1);

	forAllConstIter(hashedWordList, this->speciesNames_, iter)
	{
		YSolvent_ -= Yf(*iter, Tf);
	}
}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::interfaceCompositionModels::Henry<Thermo, OtherThermo>::Yf
(
	const word& speciesName,
	const volScalarField& Tf
) const
{
	if (this->speciesNames_.contains(speciesName))
	{
		const label index = this->speciesNames_[speciesName];

		return
			k_[index]
			* this->otherThermo_.composition().Y(speciesName)
			* this->otherThermo_.rhoThermo::rho()
			/ this->thermo_.rhoThermo::rho();
	}
	else
	{
		return
			YSolvent_
			* this->thermo_.composition().Y(speciesName);
	}
}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::interfaceCompositionModels::Henry<Thermo, OtherThermo>::YfPrime
(
	const word& speciesName,
	const volScalarField& Tf
) const
{
	return volScalarField::New
	(
		IOobject::groupName("YfPrime", this->pair_.name()),
		this->pair_.phase1().mesh(),
		dimensionedScalar(dimless / dimTemperature, 0)
	);
}