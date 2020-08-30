#include <filmThermoModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<filmThermoModel> filmThermoModel::New
			(
				surfaceFilmRegionModel& model,
				const dictionary& dict
			)
			{
				word modelType(dict.lookup("filmThermoModel"));

				Info << "    Selecting filmThermoModel " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown filmThermoModel type " << modelType << nl << nl
						<< "Valid filmThermoModel types are:" << nl
						<< dictionaryConstructorTablePtr_->toc()
						<< exit(FatalError);
				}

				return autoPtr<filmThermoModel>(cstrIter()(model, dict));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //