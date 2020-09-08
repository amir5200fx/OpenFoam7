#pragma once
#include <IFstream.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ThermoType>
tnbLib::speciesTable& tnbLib::foamChemistryReader<ThermoType>::setSpecies
(
	const dictionary& dict,
	speciesTable& species
)
{
	wordList s(dict.lookup("species"));
	species.transfer(s);
	return species;
}


template<class ThermoType>
void tnbLib::foamChemistryReader<ThermoType>::readSpeciesComposition()
{
	if (!chemDict_.found("elements"))
	{
		Info << "    elements not defined in " << chemDict_.name() << endl;
		return;
	}

	wordList e(chemDict_.lookup("elements"));
	label currentElementIndex(0);

	DynamicList<word> elementNames_;
	HashTable<label> elementIndices_;

	forAll(e, ei)
	{
		if (!elementIndices_.found(e[ei]))
		{
			elementIndices_.insert(e[ei], currentElementIndex++);
			elementNames_.append(e[ei]);
		}
		else
		{
			IOWarningInFunction(chemDict_)
				<< "element " << e[ei] << " already in table." << endl;
		}
	}

	// Loop through all species in thermoDict to retrieve
	// the species composition
	forAll(speciesTable_, si)
	{
		if (thermoDict_.subDict(speciesTable_[si]).isDict("elements"))
		{
			dictionary currentElements
			(
				thermoDict_.subDict(speciesTable_[si]).subDict("elements")
			);

			wordList currentElementsName(currentElements.toc());
			List<specieElement> currentComposition(currentElementsName.size());

			forAll(currentElementsName, eni)
			{
				currentComposition[eni].name() = currentElementsName[eni];

				currentComposition[eni].nAtoms() =
					currentElements.lookupOrDefault
					(
						currentElementsName[eni],
						0
					);
			}

			// Add current specie composition to the hash table
			speciesCompositionTable::iterator specieCompositionIter
			(
				speciesComposition_.find(speciesTable_[si])
			);

			if (specieCompositionIter != speciesComposition_.end())
			{
				speciesComposition_.erase(specieCompositionIter);
			}

			speciesComposition_.insert(speciesTable_[si], currentComposition);
		}
		else
		{
			FatalIOErrorInFunction(thermoDict_)
				<< "Specie " << speciesTable_[si]
				<< " does not contain element description."
				<< exit(FatalIOError);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::foamChemistryReader<ThermoType>::foamChemistryReader
(
	const fileName& reactionsFileName,
	speciesTable& species,
	const fileName& thermoFileName
)
	:
	chemistryReader<ThermoType>(),
	chemDict_
	(
		IFstream
		(
			fileName(reactionsFileName).expand()
		)()
	),
	thermoDict_
	(
		IFstream
		(
			fileName(thermoFileName).expand()
		)()
	),
	speciesTable_(setSpecies(chemDict_, species)),
	speciesThermo_(thermoDict_),
	reactions_(speciesTable_, speciesThermo_, chemDict_)
{
	readSpeciesComposition();
}


template<class ThermoType>
tnbLib::foamChemistryReader<ThermoType>::foamChemistryReader
(
	const dictionary& thermoDict,
	speciesTable& species
)
	:
	chemistryReader<ThermoType>(),
	chemDict_
	(
		IFstream
		(
			fileName(thermoDict.lookup("foamChemistryFile")).expand()
		)()
	),
	thermoDict_
	(
		IFstream
		(
			fileName(thermoDict.lookup("foamChemistryThermoFile")).expand()
		)()
	),
	speciesTable_(setSpecies(chemDict_, species)),
	speciesThermo_(thermoDict_),
	reactions_(speciesTable_, speciesThermo_, chemDict_)
{
	readSpeciesComposition();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //