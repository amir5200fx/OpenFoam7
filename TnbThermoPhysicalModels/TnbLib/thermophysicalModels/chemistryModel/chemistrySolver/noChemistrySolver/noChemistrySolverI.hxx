#pragma once
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ChemistryModel>
tnbLib::noChemistrySolver<ChemistryModel>::noChemistrySolver
(
	typename ChemistryModel::reactionThermo& thermo
)
	:
	chemistrySolver<ChemistryModel>(thermo)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ChemistryModel>
tnbLib::noChemistrySolver<ChemistryModel>::~noChemistrySolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ChemistryModel>
void tnbLib::noChemistrySolver<ChemistryModel>::solve
(
	scalarField&,
	scalar&,
	scalar&,
	scalar&,
	scalar&
) const
{}


// ************************************************************************* //