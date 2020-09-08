#include <noChemistryReduction.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryReductionMethods::none<CompType, ThermoType>::none
(
	const IOdictionary& dict,
	TDACChemistryModel<CompType, ThermoType>& chemistry
)
	:
	chemistryReductionMethod<CompType, ThermoType>(dict, chemistry)
{
	this->active_ = false;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryReductionMethods::none<CompType, ThermoType>::~none()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
void tnbLib::chemistryReductionMethods::none<CompType, ThermoType>::
reduceMechanism
(
	const scalarField &c,
	const scalar T,
	const scalar p
)
{
	NotImplemented;
}


// ************************************************************************* //