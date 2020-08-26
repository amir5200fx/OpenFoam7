#include <radiationModel.hxx>

#include <volFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::radiationModel> tnbLib::radiationModel::New
(
	const volScalarField& T
)
{
	IOobject radIO
	(
		"radiationProperties",
		T.time().constant(),
		T.mesh(),
		IOobject::MUST_READ_IF_MODIFIED,
		IOobject::NO_WRITE,
		false
	);

	word modelType("none");
	if (radIO.typeHeaderOk<IOdictionary>(false))
	{
		IOdictionary(radIO).lookup("radiationModel") >> modelType;
	}
	else
	{
		Info << "Radiation model not active: radiationProperties not found"
			<< endl;
	}

	Info << "Selecting radiationModel " << modelType << endl;

	TConstructorTable::iterator cstrIter =
		TConstructorTablePtr_->find(modelType);

	if (cstrIter == TConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown radiationModel type "
			<< modelType << nl << nl
			<< "Valid radiationModel types are:" << nl
			<< TConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<radiationModel>(cstrIter()(T));
}


tnbLib::autoPtr<tnbLib::radiationModel> tnbLib::radiationModel::New
(
	const dictionary& dict,
	const volScalarField& T
)
{
	const word modelType(dict.lookup("radiationModel"));

	Info << "Selecting radiationModel " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown radiationModel type "
			<< modelType << nl << nl
			<< "Valid radiationModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<radiationModel>(cstrIter()(dict, T));
}


// ************************************************************************* //