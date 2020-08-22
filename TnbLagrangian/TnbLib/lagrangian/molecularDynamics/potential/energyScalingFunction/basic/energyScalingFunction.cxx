#include <energyScalingFunction.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(energyScalingFunction, 0);
	defineRunTimeSelectionTable(energyScalingFunction, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::energyScalingFunction::energyScalingFunction
(
	const word& name,
	const dictionary& energyScalingFunctionProperties,
	const pairPotential& pairPot
)
	:
	name_(name),
	energyScalingFunctionProperties_(energyScalingFunctionProperties),
	pairPot_(pairPot)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


bool tnbLib::energyScalingFunction::read
(
	const dictionary& energyScalingFunctionProperties
)
{
	energyScalingFunctionProperties_ = energyScalingFunctionProperties;

	return true;
}


// ************************************************************************* //