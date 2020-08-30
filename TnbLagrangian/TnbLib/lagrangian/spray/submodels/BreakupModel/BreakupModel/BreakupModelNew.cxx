#include <BreakupModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::BreakupModel<CloudType>>
tnbLib::BreakupModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word BreakupModelType(dict.lookup("breakupModel"));

	Info << "Selecting BreakupModel " << BreakupModelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(BreakupModelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown BreakupModelType type "
			<< BreakupModelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid BreakupModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<BreakupModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //