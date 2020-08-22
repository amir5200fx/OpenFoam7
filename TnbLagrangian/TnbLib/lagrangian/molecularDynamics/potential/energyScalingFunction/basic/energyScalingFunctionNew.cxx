#include <energyScalingFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::energyScalingFunction> tnbLib::energyScalingFunction::New
(
	const word& name,
	const dictionary& propDict,
	const pairPotential& pairPot
)
{
	const word scalingType(propDict.lookup("energyScalingFunction"));

	Info << "Selecting energy scaling function "
		<< scalingType << " for "
		<< name << " potential energy." << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(scalingType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown energyScalingFunction type "
			<< scalingType << nl << nl
			<< "Valid energyScalingFunctions are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<energyScalingFunction>(cstrIter()(name, propDict, pairPot));
}


// ************************************************************************* //