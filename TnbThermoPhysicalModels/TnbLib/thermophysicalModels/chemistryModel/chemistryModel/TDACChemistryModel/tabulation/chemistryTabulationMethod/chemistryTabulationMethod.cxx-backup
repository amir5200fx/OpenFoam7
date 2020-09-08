#include <chemistryTabulationMethod.hxx>

#include <TDACChemistryModel.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryTabulationMethod<CompType, ThermoType>::chemistryTabulationMethod
(
	const dictionary& dict,
	TDACChemistryModel<CompType, ThermoType>& chemistry
)
	:
	dict_(dict),
	coeffsDict_(dict.subDict("tabulation")),
	active_(coeffsDict_.lookupOrDefault<Switch>("active", false)),
	log_(coeffsDict_.lookupOrDefault<Switch>("log", false)),
	chemistry_(chemistry),
	tolerance_(coeffsDict_.lookupOrDefault<scalar>("tolerance", 1e-4))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryTabulationMethod<CompType, ThermoType>::
~chemistryTabulationMethod()
{}


// ************************************************************************* //