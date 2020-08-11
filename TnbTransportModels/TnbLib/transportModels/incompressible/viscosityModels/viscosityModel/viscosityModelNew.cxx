#include <viscosityModel.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::viscosityModel> tnbLib::viscosityModel::New
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
{
	const word modelType(viscosityProperties.lookup("transportModel"));

	Info << "Selecting incompressible transport model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown viscosityModel type "
			<< modelType << nl << nl
			<< "Valid viscosityModels are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<viscosityModel>
		(cstrIter()(name, viscosityProperties, U, phi));
}


// ************************************************************************* //