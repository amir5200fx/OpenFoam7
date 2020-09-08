#include <veryInhomogeneousMixture.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ThermoType>
const char* tnbLib::veryInhomogeneousMixture<ThermoType>::specieNames_[3] =
{
	"ft",
	"fu",
	"b"
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::veryInhomogeneousMixture<ThermoType>::veryInhomogeneousMixture
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
	fu_(Y("fu")),
	b_(Y("b"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
const ThermoType& tnbLib::veryInhomogeneousMixture<ThermoType>::mixture
(
	const scalar ft,
	const scalar fu
) const
{
	if (ft < 0.0001)
	{
		return oxidant_;
	}
	else
	{
		scalar ox = 1 - ft - (ft - fu)*stoicRatio().value();
		scalar pr = 1 - fu - ox;

		mixture_ = fu * fuel_;
		mixture_ += ox * oxidant_;
		mixture_ += pr * products_;

		return mixture_;
	}
}


template<class ThermoType>
void tnbLib::veryInhomogeneousMixture<ThermoType>::read
(
	const dictionary& thermoDict
)
{
	fuel_ = ThermoType(thermoDict.subDict("fuel"));
	oxidant_ = ThermoType(thermoDict.subDict("oxidant"));
	products_ = ThermoType(thermoDict.subDict("burntProducts"));
}


template<class ThermoType>
const ThermoType& tnbLib::veryInhomogeneousMixture<ThermoType>::getLocalThermo
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