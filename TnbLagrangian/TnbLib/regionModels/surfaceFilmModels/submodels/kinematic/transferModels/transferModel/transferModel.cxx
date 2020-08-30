#include <transferModel.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(transferModel, 0);
			defineRunTimeSelectionTable(transferModel, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			void transferModel::addToTransferredMass(const scalar dMass)
			{
				transferredMass_ += dMass;
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			transferModel::transferModel(surfaceFilmRegionModel& film)
				:
				filmSubModelBase(film),
				transferredMass_(0.0)
			{}


			transferModel::transferModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType),
				transferredMass_(0)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			transferModel::~transferModel()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void transferModel::correct()
			{
				if (writeTime())
				{
					scalar transferredMass0 = getModelProperty<scalar>("transferredMass");
					transferredMass0 += returnReduce(transferredMass_, sumOp<scalar>());
					setModelProperty<scalar>("transferredMass", transferredMass0);
					transferredMass_ = 0.0;
				}
			}

			void transferModel::correct
			(
				scalarField& availableMass,
				scalarField& massToTransfer,
				scalarField& energyToTransfer
			)
			{
				scalarField massToTransfer0(massToTransfer.size(), scalar(0));
				correct(availableMass, massToTransfer0);
				massToTransfer += massToTransfer0;
				energyToTransfer += massToTransfer0 * film().hs();
			}

			scalar transferModel::transferredMassTotal() const
			{
				scalar transferredMass0 = getModelProperty<scalar>("transferredMass");
				return transferredMass0 + returnReduce(transferredMass_, sumOp<scalar>());
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //