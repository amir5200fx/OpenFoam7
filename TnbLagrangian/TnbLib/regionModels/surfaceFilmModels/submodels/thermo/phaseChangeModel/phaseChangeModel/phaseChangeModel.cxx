#include <phaseChangeModel.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(phaseChangeModel, 0);
			defineRunTimeSelectionTable(phaseChangeModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			phaseChangeModel::phaseChangeModel
			(
				surfaceFilmRegionModel& film
			)
				:
				filmSubModelBase(film),
				latestMassPC_(0.0),
				totalMassPC_(0.0)
			{}


			phaseChangeModel::phaseChangeModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType),
				latestMassPC_(0.0),
				totalMassPC_(0.0)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			phaseChangeModel::~phaseChangeModel()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void phaseChangeModel::correct
			(
				const scalar dt,
				scalarField& availableMass,
				volScalarField& dMass,
				volScalarField& dEnergy
			)
			{
				if (!active())
				{
					return;
				}

				correctModel
				(
					dt,
					availableMass,
					dMass,
					dEnergy
				);

				latestMassPC_ = sum(dMass.primitiveField());
				totalMassPC_ += latestMassPC_;

				availableMass -= dMass;
				dMass.correctBoundaryConditions();

				if (writeTime())
				{
					scalar phaseChangeMass = getModelProperty<scalar>("phaseChangeMass");
					phaseChangeMass += returnReduce(totalMassPC_, sumOp<scalar>());
					setModelProperty<scalar>("phaseChangeMass", phaseChangeMass);
					totalMassPC_ = 0.0;
				}
			}


			void phaseChangeModel::info(Ostream& os) const
			{
				const scalar massPCRate =
					returnReduce(latestMassPC_, sumOp<scalar>())
					/ filmModel_.time().deltaTValue();

				scalar phaseChangeMass = getModelProperty<scalar>("phaseChangeMass");
				phaseChangeMass += returnReduce(totalMassPC_, sumOp<scalar>());

				os << indent << "mass phase change  = " << phaseChangeMass << nl
					<< indent << "vapourisation rate = " << massPCRate << nl;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // end namespace surfaceFilmModels
	} // end namespace regionModels
} // end namespace tnbLib

// ************************************************************************* //