#include <pyrolysisModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(pyrolysisModel, 0);
			defineRunTimeSelectionTable(pyrolysisModel, mesh);
			defineRunTimeSelectionTable(pyrolysisModel, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			void pyrolysisModel::readPyrolysisControls()
			{}


			bool pyrolysisModel::read()
			{
				if (regionModel1D::read())
				{
					readPyrolysisControls();
					return true;
				}
				else
				{
					return false;
				}
			}


			bool pyrolysisModel::read(const dictionary& dict)
			{
				if (regionModel1D::read(dict))
				{
					readPyrolysisControls();
					return true;
				}
				else
				{
					return false;
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			pyrolysisModel::pyrolysisModel(const fvMesh& mesh, const word& regionType)
				:
				regionModel1D(mesh, regionType)
			{}


			pyrolysisModel::pyrolysisModel
			(
				const word& modelType,
				const fvMesh& mesh,
				const word& regionType
			)
				:
				regionModel1D(mesh, regionType, modelType)
			{
				if (active_)
				{
					read();
				}
			}


			pyrolysisModel::pyrolysisModel
			(
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& regionType
			)
				:
				regionModel1D(mesh, regionType, modelType, dict)
			{
				if (active_)
				{
					read(dict);
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			pyrolysisModel::~pyrolysisModel()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			scalar pyrolysisModel::addMassSources
			(
				const label patchi,
				const label facei
			)
			{
				return 0.0;
			}


			scalar pyrolysisModel::solidRegionDiffNo() const
			{
				return -great;
			}


			scalar pyrolysisModel::maxDiff() const
			{
				return great;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //