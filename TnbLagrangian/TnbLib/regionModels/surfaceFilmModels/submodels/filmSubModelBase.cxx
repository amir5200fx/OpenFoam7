#include <filmSubModelBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			filmSubModelBase::filmSubModelBase(surfaceFilmRegionModel& film)
				:
				subModelBase(film.outputProperties()),
				filmModel_(film)
			{}


			filmSubModelBase::filmSubModelBase
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				const word& baseName,
				const word& modelType,
				const word& dictExt
			)
				:
				subModelBase
				(
					film.outputProperties(),
					dict,
					baseName,
					modelType,
					dictExt
				),
				filmModel_(film)
			{}


			filmSubModelBase::filmSubModelBase
			(
				const word& modelName,
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				const word& baseName,
				const word& modelType
			)
				:
				subModelBase
				(
					modelName,
					film.outputProperties(),
					dict,
					baseName,
					modelType
				),
				filmModel_(film)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			filmSubModelBase::~filmSubModelBase()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			bool filmSubModelBase::writeTime() const
			{
				return active() && filmModel_.time().writeTime();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //