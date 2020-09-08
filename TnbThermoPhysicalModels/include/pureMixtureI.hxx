#pragma once
#include <fvMesh.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::pureMixture<ThermoType>::pureMixture
(
	const dictionary& thermoDict,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicMixture(thermoDict, mesh, phaseName),
	mixture_(thermoDict.subDict("mixture"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
void tnbLib::pureMixture<ThermoType>::read(const dictionary& thermoDict)
{
	mixture_ = ThermoType(thermoDict.subDict("mixture"));
}


// ************************************************************************* //