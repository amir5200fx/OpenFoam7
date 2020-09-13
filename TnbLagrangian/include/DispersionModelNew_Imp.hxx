#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::DispersionModel<CloudType>>
tnbLib::DispersionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("dispersionModel"));

	Info << "Selecting dispersion model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown dispersion model type "
			<< modelType << nl << nl
			<< "Valid dispersion model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<DispersionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //