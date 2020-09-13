#include <CloudFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::CloudFunctionObject<CloudType>>
tnbLib::CloudFunctionObject<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner,
	const word& objectType,
	const word& modelName
)
{
	Info << "    Selecting cloud function " << modelName << " of type "
		<< objectType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(objectType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown cloud function type "
			<< objectType << nl << nl
			<< "Valid cloud function types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<CloudFunctionObject<CloudType>>
		(
			cstrIter()
			(
				dict,
				owner,
				modelName
				)
			);
}


// ************************************************************************* //