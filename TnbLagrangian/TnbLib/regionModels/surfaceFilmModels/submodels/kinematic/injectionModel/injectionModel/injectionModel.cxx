#include <injectionModel.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(injectionModel, 0);
			defineRunTimeSelectionTable(injectionModel, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			void injectionModel::addToInjectedMass(const scalar dMass)
			{
				injectedMass_ += dMass;
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			injectionModel::injectionModel(surfaceFilmRegionModel& film)
				:
				filmSubModelBase(film),
				injectedMass_(0.0)
			{}


			injectionModel::injectionModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType),
				injectedMass_(0.0)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			injectionModel::~injectionModel()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void injectionModel::correct()
			{
				if (writeTime())
				{
					scalar injectedMass0 = getModelProperty<scalar>("injectedMass");
					injectedMass0 += returnReduce(injectedMass_, sumOp<scalar>());
					setModelProperty<scalar>("injectedMass", injectedMass0);
					injectedMass_ = 0.0;
				}
			}


			scalar injectionModel::injectedMassTotal() const
			{
				scalar injectedMass0 = getModelProperty<scalar>("injectedMass");
				return injectedMass0 + returnReduce(injectedMass_, sumOp<scalar>());
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //