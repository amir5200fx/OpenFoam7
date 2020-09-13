#include <AtomizationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::AtomizationModel<CloudType>>
tnbLib::AtomizationModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word AtomizationModelType(dict.lookup("atomizationModel"));

	Info << "Selecting AtomizationModel " << AtomizationModelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(AtomizationModelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown AtomizationModelType type "
			<< AtomizationModelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid AtomizationModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<AtomizationModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //