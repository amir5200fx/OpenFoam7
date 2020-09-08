#include <singleComponentMixture.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::singleComponentMixture<ThermoType>::singleComponentMixture
(
	const dictionary& thermoDict,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicSpecieMixture(thermoDict, wordList(), mesh, phaseName),
	thermo_(thermoDict.subDict("mixture"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::singleComponentMixture<ThermoType>::~singleComponentMixture()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ThermoType>
void tnbLib::singleComponentMixture<ThermoType>::read
(
	const dictionary& thermoDict
)
{
	thermo_ = ThermoType(thermoDict.subDict("mixture"));
}


// ************************************************************************* //