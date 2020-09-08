#include <chemistryReductionMethod.hxx>

#include <TDACChemistryModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryReductionMethod<CompType, ThermoType>::chemistryReductionMethod
(
	const tnbLib::IOdictionary& dict,
	tnbLib::TDACChemistryModel<CompType, ThermoType>& chemistry
)
	:
	dict_(dict),
	coeffsDict_(dict.subDict("reduction")),
	active_(coeffsDict_.lookupOrDefault<Switch>("active", false)),
	log_(coeffsDict_.lookupOrDefault<Switch>("log", false)),
	chemistry_(chemistry),
	activeSpecies_(chemistry.nSpecie(), false),
	NsSimp_(chemistry.nSpecie()),
	nSpecie_(chemistry.nSpecie()),
	tolerance_(coeffsDict_.lookupOrDefault<scalar>("tolerance", 1e-4))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryReductionMethod<CompType, ThermoType>::
~chemistryReductionMethod()
{}


// ************************************************************************* //