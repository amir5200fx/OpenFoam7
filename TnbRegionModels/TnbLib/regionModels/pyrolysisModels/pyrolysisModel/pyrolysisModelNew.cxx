#include <pyrolysisModel.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<pyrolysisModel> pyrolysisModel::New
			(
				const fvMesh& mesh,
				const word& regionType
			)
			{
				// get model name, but do not register the dictionary
				const word modelType
				(
					IOdictionary
					(
						IOobject
						(
							regionType + "Properties",
							mesh.time().constant(),
							mesh,
							IOobject::MUST_READ,
							IOobject::NO_WRITE,
							false
						)
					).lookup("pyrolysisModel")
				);

				Info << "Selecting pyrolysisModel " << modelType << endl;

				meshConstructorTable::iterator cstrIter =
					meshConstructorTablePtr_->find(modelType);

				if (cstrIter == meshConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown pyrolysisModel type " << modelType
						<< nl << nl << "Valid pyrolisisModel types are:" << nl
						<< meshConstructorTablePtr_->sortedToc()
						<< exit(FatalError);
				}

				return autoPtr<pyrolysisModel>(cstrIter()(modelType, mesh, regionType));
			}


			autoPtr<pyrolysisModel> pyrolysisModel::New
			(
				const fvMesh& mesh,
				const dictionary& dict,
				const word& regionType
			)
			{

				const word modelType = dict.lookup("pyrolysisModel");

				Info << "Selecting pyrolysisModel " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown pyrolysisModel type " << modelType
						<< nl << nl << "Valid pyrolisisModel types are:" << nl
						<< dictionaryConstructorTablePtr_->sortedToc()
						<< exit(FatalError);
				}

				return autoPtr<pyrolysisModel>
					(
						cstrIter()
						(
							modelType,
							mesh,
							dict,
							regionType
							)
						);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //