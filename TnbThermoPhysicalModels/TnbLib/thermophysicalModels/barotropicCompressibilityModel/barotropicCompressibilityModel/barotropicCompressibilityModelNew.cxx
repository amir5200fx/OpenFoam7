#include <barotropicCompressibilityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::barotropicCompressibilityModel>
tnbLib::barotropicCompressibilityModel::New
(
	const dictionary& compressibilityProperties,
	const volScalarField& gamma,
	const word& psiName
)
{
	const word modelType
	(
		compressibilityProperties.lookup("barotropicCompressibilityModel")
	);

	Info << "Selecting compressibility model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown barotropicCompressibilityModel type "
			<< modelType << nl << nl
			<< "Valid barotropicCompressibilityModels are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<barotropicCompressibilityModel>
		(
			cstrIter()(compressibilityProperties, gamma, psiName)
			);
}


// ************************************************************************* //