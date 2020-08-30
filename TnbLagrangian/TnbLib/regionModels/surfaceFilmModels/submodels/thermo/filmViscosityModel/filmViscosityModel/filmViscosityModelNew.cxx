#include <filmViscosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<filmViscosityModel> filmViscosityModel::New
			(
				surfaceFilmRegionModel& model,
				const dictionary& dict,
				volScalarField& mu
			)
			{
				word modelType(dict.lookup("filmViscosityModel"));

				Info << "    Selecting filmViscosityModel " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown filmViscosityModel type " << modelType
						<< nl << nl << "Valid filmViscosityModel types are:" << nl
						<< dictionaryConstructorTablePtr_->toc()
						<< exit(FatalError);
				}

				return autoPtr<filmViscosityModel>(cstrIter()(model, dict, mu));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // end namespace surfaceFilmModels
	} // end namespace regionModels
} // end namespace tnbLib

// ************************************************************************* //