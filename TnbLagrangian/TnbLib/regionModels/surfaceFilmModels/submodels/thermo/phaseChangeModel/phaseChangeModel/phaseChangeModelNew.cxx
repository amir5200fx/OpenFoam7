#include <phaseChangeModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

			autoPtr<phaseChangeModel> phaseChangeModel::New
			(
				surfaceFilmRegionModel& model,
				const dictionary& dict
			)
			{
				word modelType(dict.lookup("phaseChangeModel"));

				Info << "    Selecting phaseChangeModel " << modelType << endl;

				dictionaryConstructorTable::iterator cstrIter =
					dictionaryConstructorTablePtr_->find(modelType);

				if (cstrIter == dictionaryConstructorTablePtr_->end())
				{
					FatalErrorInFunction
						<< "Unknown phaseChangeModel type " << modelType
						<< nl << nl << "Valid phaseChangeModel types are:" << nl
						<< dictionaryConstructorTablePtr_->toc()
						<< exit(FatalError);
				}

				return autoPtr<phaseChangeModel>(cstrIter()(model, dict));
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // end namespace surfaceFilmModels
	} // end namespace regionModels
} // end namespace tnbLib

// ************************************************************************* //