#include <surfaceTensionModel.hxx>

#include <constantSurfaceTension.hxx>

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::surfaceTensionModel> tnbLib::surfaceTensionModel::New
(
	const dictionary& dict,
	const fvMesh& mesh
)
{
	if (dict.isDict("sigma"))
	{
		const dictionary& sigmaDict = surfaceTensionModel::sigmaDict(dict);

		word surfaceTensionModelType(sigmaDict.lookup("type"));

		Info << "Selecting surfaceTensionModel "
			<< surfaceTensionModelType << endl;

		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(surfaceTensionModelType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown surfaceTensionModelType type "
				<< surfaceTensionModelType << endl << endl
				<< "Valid surfaceTensionModel types are : " << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return cstrIter()(sigmaDict, mesh);
	}
	else
	{
		return autoPtr<surfaceTensionModel>
			(
				new surfaceTensionModels::constant(dict, mesh)
				);
	}
}


// ************************************************************************* //