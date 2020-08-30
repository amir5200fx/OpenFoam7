#include <injectionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<injectionModel> injectionModel::New
			(
				surfaceFilmRegionModel& model,
				const dictionary& dict,
				const word& modelType
			)
			{
				Info << "        " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown injectionModel type " << modelType
						<< nl << nl << "Valid injectionModel types are:" << nl
						<< dictionaryConstructorTablePtr_->toc()
						<< exit(FatalError);
				}

				return autoPtr<injectionModel>(cstrIter()(model, dict));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //