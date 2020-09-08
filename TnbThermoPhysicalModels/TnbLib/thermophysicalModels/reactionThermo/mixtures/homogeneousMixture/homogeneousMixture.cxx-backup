#include <homogeneousMixture.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ThermoType>
const char* tnbLib::homogeneousMixture<ThermoType>::specieNames_[1] = { "b" };


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::homogeneousMixture<ThermoType>::homogeneousMixture
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

	reactants_(thermoDict.subDict("reactants")),
	products_(thermoDict.subDict("products")),
	mixture_("mixture", reactants_),
	b_(Y("b"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
const ThermoType& tnbLib::homogeneousMixture<ThermoType>::mixture
(
	const scalar b
) const
{
	if (b > 0.999)
	{
		return reactants_;
	}
	else if (b < 0.001)
	{
		return products_;
	}
	else
	{
		mixture_ = b * reactants_;
		mixture_ += (1 - b)*products_;

		return mixture_;
	}
}


template<class ThermoType>
void tnbLib::homogeneousMixture<ThermoType>::read(const dictionary& thermoDict)
{
	reactants_ = ThermoType(thermoDict.subDict("reactants"));
	products_ = ThermoType(thermoDict.subDict("products"));
}


template<class ThermoType>
const ThermoType& tnbLib::homogeneousMixture<ThermoType>::getLocalThermo
(
	const label speciei
) const
{
	if (speciei == 0)
	{
		return reactants_;
	}
	else if (speciei == 1)
	{
		return products_;
	}
	else
	{
		FatalErrorInFunction
			<< "Unknown specie index " << speciei << ". Valid indices are 0..1"
			<< abort(FatalError);

		return reactants_;
	}
}


// ************************************************************************* //