#include <filmRadiationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<filmRadiationModel> filmRadiationModel::New
			(
				surfaceFilmRegionModel& model,
				const dictionary& dict
			)
			{
				word modelType(dict.lookup("radiationModel"));

				Info << "    Selecting radiationModel " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown radiationModel type " << modelType << nl << nl
						<< "Valid filmRadiationModel types are:" << nl
						<< dictionaryConstructorTablePtr_->toc()
						<< exit(FatalError);
				}

				return autoPtr<filmRadiationModel>(cstrIter()(model, dict));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //