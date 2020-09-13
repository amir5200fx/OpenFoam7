#include <BinaryCollisionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::BinaryCollisionModel<CloudType>>
tnbLib::BinaryCollisionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("BinaryCollisionModel"));

	Info << "Selecting BinaryCollisionModel " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown BinaryCollisionModel type "
			<< modelType << nl << nl
			<< "Valid BinaryCollisionModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<BinaryCollisionModel<CloudType>>
		(
			cstrIter()(dict, owner)
			);
}


// ************************************************************************* //