#include <generalizedNewtonianViscosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::laminarModels::generalizedNewtonianViscosityModel>
tnbLib::laminarModels::generalizedNewtonianViscosityModel::New
(
	const dictionary& viscosityProperties
)
{
	const word modelType
	(
		viscosityProperties.lookup("viscosityModel")
	);

	Info << "Selecting generalized Newtonian model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown generalizedNewtonianViscosityModel type "
			<< modelType << nl << nl
			<< "Valid generalizedNewtonianViscosityModels are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<generalizedNewtonianViscosityModel>
		(
			cstrIter()(viscosityProperties)
			);
}


// ************************************************************************* //