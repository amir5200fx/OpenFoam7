#pragma once
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::autoPtr<tnbLib::chemistryReader<ThermoType>>
tnbLib::chemistryReader<ThermoType>::New
(
	const dictionary& thermoDict,
	speciesTable& species
)
{
	// Let the chemistry reader type default to CHEMKIN
	// for backward compatibility
	word chemistryReaderTypeName("chemkinReader");

	// otherwise use the specified reader
	thermoDict.readIfPresent("chemistryReader", chemistryReaderTypeName);

	Info << "Selecting chemistryReader " << chemistryReaderTypeName << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(chemistryReaderTypeName);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown chemistryReader type "
			<< chemistryReaderTypeName << nl << nl
			<< "Valid chemistryReader types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<chemistryReader<ThermoType>>
		(
			cstrIter()(thermoDict, species)
			);
}


// ************************************************************************* //