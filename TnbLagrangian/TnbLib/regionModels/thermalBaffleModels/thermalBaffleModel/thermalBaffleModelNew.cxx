#include <thermalBaffleModel.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace thermalBaffleModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<thermalBaffleModel> thermalBaffleModel::New(const fvMesh& mesh)
			{
				word modelType;
				{
					IOdictionary thermalBafflePropertiesDict
					(
						IOobject
						(
							"thermalBaffleProperties",
							mesh.time().constant(),
							mesh,
							IOobject::MUST_READ_IF_MODIFIED,
							IOobject::NO_WRITE,
							false
						)
					);

					word modelType =
						thermalBafflePropertiesDict.lookupOrDefault<word>
						(
							"thermalBaffleModel",
							"thermalBaffle"
							);
				}

				meshConstructorTable::iterator cstrIter =
					meshConstructorTablePtr_->find(modelType);

				if (cstrIter == meshConstructorTablePtr_->end())
				{

					FatalErrorInFunction
						<< "Unknown thermalBaffleModel type " << modelType
						<< nl << nl
						<< "Valid thermalBaffleModel types are:" << nl
						<< meshConstructorTablePtr_->sortedToc()
						<< exit(FatalError);
				}

				return autoPtr<thermalBaffleModel>(cstrIter()(modelType, mesh));
			}


			autoPtr<thermalBaffleModel> thermalBaffleModel::New
			(
				const fvMesh& mesh,
				const dictionary& dict
			)
			{
				word modelType =
					dict.lookupOrDefault<word>("thermalBaffleModel", "thermalBaffle");

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{

					FatalErrorInFunction
						<< "Unknown thermalBaffleModel type " << modelType
						<< nl << nl
						<< "Valid thermalBaffleModel types are:" << nl
						<< dictionaryConstructorTablePtr_->sortedToc()
						<< exit(FatalError);
				}

				return autoPtr<thermalBaffleModel>(cstrIter()(modelType, mesh, dict));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermalBaffleModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //