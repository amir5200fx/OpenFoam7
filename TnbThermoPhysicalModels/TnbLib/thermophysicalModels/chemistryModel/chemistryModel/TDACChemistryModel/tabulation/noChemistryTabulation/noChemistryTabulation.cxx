#include <noChemistryTabulation.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryTabulationMethods::none<CompType, ThermoType>::none
(
	const dictionary& chemistryProperties,
	TDACChemistryModel<CompType, ThermoType>& chemistry
)
	:
	chemistryTabulationMethod<CompType, ThermoType>
	(
		chemistryProperties,
		chemistry
		)
{
	this->active_ = false;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::chemistryTabulationMethods::none<CompType, ThermoType>::~none()
{}


// ************************************************************************* //