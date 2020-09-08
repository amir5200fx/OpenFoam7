#pragma once
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ThermoType>
const char* tnbLib::inhomogeneousMixture<ThermoType>::specieNames_[2] =
{
	"ft",
	"b"
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::inhomogeneousMixture<ThermoType>::inhomogeneousMixture
(
	const dictionary& thermoDict,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicCombustionMixture
	(
		thermoDict,
		speciesTable(nSpecies_, specieNames_),
		mesh,
		phaseName
	),

	stoicRatio_(thermoDict.lookup("stoichiometricAirFuelMassRatio")),

	fuel_(thermoDict.subDict("fuel")),
	oxidant_(thermoDict.subDict("oxidant")),
	products_(thermoDict.subDict("burntProducts")),

	mixture_("mixture", fuel_),

	ft_(Y("ft")),
	b_(Y("b"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
const ThermoType& tnbLib::inhomogeneousMixture<ThermoType>::mixture
(
	const scalar ft,
	const scalar b
) const
{
	if (ft < 0.0001)
	{
		return oxidant_;
	}
	else
	{
		scalar fu = b * ft + (1.0 - b)*fres(ft, stoicRatio().value());
		scalar ox = 1 - ft - (ft - fu)*stoicRatio().value();
		scalar pr = 1 - fu - ox;

		mixture_ = fu * fuel_;
		mixture_ += ox * oxidant_;
		mixture_ += pr * products_;

		return mixture_;
	}
}


template<class ThermoType>
void tnbLib::inhomogeneousMixture<ThermoType>::read(const dictionary& thermoDict)
{
	stoicRatio_ = thermoDict.lookup("stoichiometricAirFuelMassRatio");

	fuel_ = ThermoType(thermoDict.subDict("fuel"));
	oxidant_ = ThermoType(thermoDict.subDict("oxidant"));
	products_ = ThermoType(thermoDict.subDict("burntProducts"));
}


template<class ThermoType>
const ThermoType& tnbLib::inhomogeneousMixture<ThermoType>::getLocalThermo
(
	const label speciei
) const
{
	if (speciei == 0)
	{
		return fuel_;
	}
	else if (speciei == 1)
	{
		return oxidant_;
	}
	else if (speciei == 2)
	{
		return products_;
	}
	else
	{
		FatalErrorInFunction
			<< "Unknown specie index " << speciei << ". Valid indices are 0..2"
			<< abort(FatalError);

		return fuel_;
	}
}


// ************************************************************************* //