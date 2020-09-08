#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::autoPtr<tnbLib::chemistryTabulationMethod<CompType, ThermoType>>
tnbLib::chemistryTabulationMethod<CompType, ThermoType>::New
(
	const IOdictionary& dict,
	TDACChemistryModel<CompType, ThermoType>& chemistry
)
{
	const dictionary& tabulationDict(dict.subDict("tabulation"));

	const word methodName(tabulationDict.lookup("method"));

	Info << "Selecting chemistry tabulation method " << methodName << endl;

	const word methodTypeName =
		methodName + '<' + CompType::typeName + ',' + ThermoType::typeName()
		+ '>';

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(methodTypeName);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << typeName_() << " type " << methodName << endl
			<< endl;

		const wordList names(dictionaryConstructorTablePtr_->toc());

		wordList thisCmpts;
		thisCmpts.append(word::null);
		thisCmpts.append(CompType::typeName);
		thisCmpts.append
		(
			basicThermo::splitThermoName(ThermoType::typeName(), 5)
		);

		wordList validNames;
		forAll(names, i)
		{
			const wordList cmpts(basicThermo::splitThermoName(names[i], 7));

			bool isValid = true;
			for (label i = 1; i < cmpts.size() && isValid; ++i)
			{
				isValid = isValid && cmpts[i] == thisCmpts[i];
			}

			if (isValid)
			{
				validNames.append(cmpts[0]);
			}
		}

		FatalErrorInFunction
			<< "Valid " << typeName_() << " types for this thermodynamic model "
			<< "are:" << endl << validNames << endl;

		List<wordList> validCmpts;
		validCmpts.append(wordList(7, word::null));
		validCmpts[0][0] = typeName_();
		validCmpts[0][1] = "reactionThermo";
		validCmpts[0][2] = "transport";
		validCmpts[0][3] = "thermo";
		validCmpts[0][4] = "equationOfState";
		validCmpts[0][5] = "specie";
		validCmpts[0][6] = "energy";
		forAll(names, i)
		{
			validCmpts.append(basicThermo::splitThermoName(names[i], 7));
		}

		FatalErrorInFunction
			<< "All " << validCmpts[0][0] << '/' << validCmpts[0][1]
			<< "/thermoPhysics combinations are:" << endl << endl;
		printTable(validCmpts, FatalErrorInFunction);

		FatalErrorInFunction << exit(FatalError);
	}

	return autoPtr<chemistryTabulationMethod<CompType, ThermoType>>
		(
			cstrIter()(dict, chemistry)
			);

}


// ************************************************************************* //