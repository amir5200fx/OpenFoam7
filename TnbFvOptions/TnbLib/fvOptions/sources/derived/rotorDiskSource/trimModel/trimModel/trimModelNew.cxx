#include <trimModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::trimModel> tnbLib::trimModel::New
(
	const fv::rotorDiskSource& rotor,
	const dictionary& dict
)
{
	const word modelType(dict.lookup(typeName));

	Info << "    Selecting " << typeName << " " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << typeName << " type "
			<< modelType << nl << nl
			<< "Valid " << typeName << " types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<trimModel>(cstrIter()(rotor, dict));
}


// ************************************************************************* //