#include <PairModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::PairModel<CloudType>>
tnbLib::PairModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word PairModelType(dict.lookup("pairModel"));

	Info << "Selecting pair model " << PairModelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(PairModelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown pair model type "
			<< PairModelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid pair model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<PairModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //