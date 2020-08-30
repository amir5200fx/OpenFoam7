#include <surfaceFilmModel.hxx>

#include <noFilm.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{

		// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

		autoPtr<surfaceFilmModel> surfaceFilmModel::New
		(
			const fvMesh& mesh,
			const dimensionedVector& g,
			const word& regionType
		)
		{
			word modelType;

			{
				IOobject surfaceFilmPropertiesDictHeader
				(
					regionType + "Properties",
					mesh.time().constant(),
					mesh,
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				);

				if (surfaceFilmPropertiesDictHeader.typeHeaderOk<IOdictionary>())
				{
					IOdictionary surfaceFilmPropertiesDict
					(
						surfaceFilmPropertiesDictHeader
					);

					surfaceFilmPropertiesDict.lookup("surfaceFilmModel") >> modelType;
				}
				else
				{
					modelType = surfaceFilmModels::noFilm::typeName;
				}
			}

			Info << "Selecting surfaceFilmModel " << modelType << endl;

			meshConstructorTable::iterator cstrIter =
				meshConstructorTablePtr_->find(modelType);

			if (cstrIter == meshConstructorTablePtr_->end())
			{
				FatalErrorInFunction
					<< "Unknown surfaceFilmModel type " << modelType
					<< nl << nl << "Valid surfaceFilmModel types are:" << nl
					<< meshConstructorTablePtr_->toc()
					<< exit(FatalError);
			}

			return autoPtr<surfaceFilmModel>
				(
					cstrIter()
					(
						modelType,
						mesh,
						g,
						regionType
						)
					);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //