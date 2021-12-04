#pragma once
#include <phasePair.hxx> // Added by Payvand [12/4/2021 Payvand]

template<class Thermo, class OtherThermo>
template<class ThermoType>
const typename tnbLib::multiComponentMixture<ThermoType>::thermoType&
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::getLocalThermo
(
	const word& speciesName,
	const multiComponentMixture<ThermoType>& globalThermo
) const
{
	return
		globalThermo.getLocalThermo
		(
			globalThermo.species()
			[
				speciesName
			]
	);
}


template<class Thermo, class OtherThermo>
template<class ThermoType>
const typename tnbLib::pureMixture<ThermoType>::thermoType&
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::getLocalThermo
(
	const word& speciesName,
	const pureMixture<ThermoType>& globalThermo
) const
{
	return globalThermo.cellMixture(0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::InterfaceCompositionModel
(
	const dictionary& dict,
	const phasePair& pair
)
	:
	interfaceCompositionModel(dict, pair),
	thermo_
	(
		pair.phase1().mesh().lookupObject<Thermo>
		(
			IOobject::groupName(basicThermo::dictName, pair.phase1().name())
			)
	),
	otherThermo_
	(
		pair.phase2().mesh().lookupObject<OtherThermo>
		(
			IOobject::groupName(basicThermo::dictName, pair.phase2().name())
			)
	),
	Le_("Le", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::
~InterfaceCompositionModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::dY
(
	const word& speciesName,
	const volScalarField& Tf
) const
{
	return
		Yf(speciesName, Tf)
		- thermo_.composition().Y()
		[
			thermo_.composition().species()[speciesName]
		];
}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::D
(
	const word& speciesName
) const
{
	const typename Thermo::thermoType& localThermo =
		getLocalThermo
		(
			speciesName,
			thermo_
		);

	const volScalarField& p(thermo_.p());

	const volScalarField& T(thermo_.T());

	tmp<volScalarField> tmpD
	(
		volScalarField::New
		(
			IOobject::groupName("D", pair_.name()),
			p.mesh(),
			dimensionedScalar(dimArea / dimTime, 0)
		)
	);

	volScalarField& D(tmpD.ref());

	forAll(p, celli)
	{
		D[celli] =
			localThermo.alphah(p[celli], T[celli])
			/ localThermo.rho(p[celli], T[celli]);
	}

	D /= Le_;

	return tmpD;
}


template<class Thermo, class OtherThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::L
(
	const word& speciesName,
	const volScalarField& Tf
) const
{
	const typename Thermo::thermoType& localThermo =
		getLocalThermo
		(
			speciesName,
			thermo_
		);
	const typename OtherThermo::thermoType& otherLocalThermo =
		getLocalThermo
		(
			speciesName,
			otherThermo_
		);

	const volScalarField& p(thermo_.p());
	const volScalarField& otherP(otherThermo_.p());

	tmp<volScalarField> tmpL
	(
		volScalarField::New
		(
			IOobject::groupName("L", pair_.name()),
			p.mesh(),
			dimensionedScalar(dimEnergy / dimMass, 0)
		)
	);

	volScalarField& L(tmpL.ref());

	forAll(p, celli)
	{
		L[celli] =
			localThermo.Ha(p[celli], Tf[celli])
			- otherLocalThermo.Ha(otherP[celli], Tf[celli]);
	}

	return tmpL;
}


template<class Thermo, class OtherThermo>
void tnbLib::InterfaceCompositionModel<Thermo, OtherThermo>::addMDotL
(
	const volScalarField& K,
	const volScalarField& Tf,
	volScalarField& mDotL,
	volScalarField& mDotLPrime
) const
{
	forAllConstIter(hashedWordList, this->speciesNames_, iter)
	{
		volScalarField rhoKDL
		(
			thermo_.rhoThermo::rho()
			* K
			* D(*iter)
			* L(*iter, Tf)
		);

		mDotL += rhoKDL * dY(*iter, Tf);
		mDotLPrime += rhoKDL * YfPrime(*iter, Tf);
	}
}