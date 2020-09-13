#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::WallModel<CloudType>>
tnbLib::WallModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word WallModelType(dict.lookup("wallModel"));

	Info << "Selecting wall model " << WallModelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(WallModelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown wall model type type " << WallModelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid wall model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<WallModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //