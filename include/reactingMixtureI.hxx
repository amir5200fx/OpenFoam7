#pragma once
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::reactingMixture<ThermoType>::reactingMixture
(
	const dictionary& thermoDict,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	speciesTable(),
	autoPtr<chemistryReader<ThermoType>>
	(
		chemistryReader<ThermoType>::New(thermoDict, *this)
		),
	multiComponentMixture<ThermoType>
	(
		thermoDict,
		*this,
		autoPtr<chemistryReader<ThermoType>>::operator()().speciesThermo(),
		mesh,
		phaseName
		),
	PtrList<Reaction<ThermoType>>
	(
		autoPtr<chemistryReader<ThermoType>>::operator()().reactions()
		),
	speciesComposition_
	(
		autoPtr<chemistryReader<ThermoType>>::operator()().specieComposition()
	)
{
	autoPtr<chemistryReader<ThermoType>>::clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
void tnbLib::reactingMixture<ThermoType>::read(const dictionary& thermoDict)
{}


// ************************************************************************* //