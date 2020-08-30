#include <surfaceFilmRegionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(surfaceFilmRegionModel, 0);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			bool surfaceFilmRegionModel::read()
			{
				if (singleLayerRegion::read())
				{
					return true;
				}
				else
				{
					return false;
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			surfaceFilmRegionModel::surfaceFilmRegionModel
			(
				const word& modelType,
				const fvMesh& mesh,
				const dimensionedVector& g,
				const word& regionType
			)
				:
				surfaceFilmModel(),
				singleLayerRegion(mesh, regionType, modelType),
				g_(g)
			{
				if (active_)
				{
					read();
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			surfaceFilmRegionModel::~surfaceFilmRegionModel()
			{}



			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void surfaceFilmRegionModel::evolve()
			{
				singleLayerRegion::evolve();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //