#include <noPyrolysis.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <absorptionEmissionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(noPyrolysis, 0);
			addToRunTimeSelectionTable(pyrolysisModel, noPyrolysis, mesh);
			addToRunTimeSelectionTable(pyrolysisModel, noPyrolysis, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			void noPyrolysis::constructThermoChemistry()
			{
				solidThermo_.reset
				(
					solidReactionThermo::New(regionMesh()).ptr()
				);

				solidChemistry_.reset
				(
					basicSolidChemistryModel::New(solidThermo_()).ptr()
				);

				solidThermo_.reset(&solidChemistry_->solidThermo());
				radiation_.reset(radiationModel::New(solidThermo_->T()).ptr());
			}


			bool noPyrolysis::read()
			{
				if (pyrolysisModel::read())
				{
					// no additional info to read
					return true;
				}
				else
				{
					return false;
				}
			}


			bool noPyrolysis::read(const dictionary& dict)
			{
				if (pyrolysisModel::read(dict))
				{
					// no additional info to read
					return true;
				}
				else
				{
					return false;
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			noPyrolysis::noPyrolysis
			(
				const word& modelType,
				const fvMesh& mesh,
				const word& regionType
			)
				:
				pyrolysisModel(mesh, regionType),
				solidThermo_(nullptr),
				solidChemistry_(nullptr),
				radiation_(nullptr)
			{
				if (active())
				{
					constructThermoChemistry();
				}
			}


			noPyrolysis::noPyrolysis
			(
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& regionType
			)
				:
				pyrolysisModel(mesh, regionType),
				solidThermo_(nullptr),
				solidChemistry_(nullptr),
				radiation_(nullptr)
			{
				if (active())
				{
					constructThermoChemistry();
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			noPyrolysis::~noPyrolysis()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void noPyrolysis::preEvolveRegion()
			{}


			void noPyrolysis::evolveRegion()
			{}


			const volScalarField& noPyrolysis::rho() const
			{
				return solidThermo_->rho();
			}


			const volScalarField& noPyrolysis::T() const
			{
				return solidThermo_->T();
			}


			const tmp<volScalarField> noPyrolysis::Cp() const
			{
				return solidThermo_->Cp();
			}


			tmp<volScalarField> noPyrolysis::kappaRad() const
			{
				return radiation_->absorptionEmission().a();
			}


			tmp<volScalarField> noPyrolysis::kappa() const
			{
				return solidThermo_->kappa();
			}


			const surfaceScalarField& noPyrolysis::phiGas() const
			{
				FatalErrorInFunction
					<< "phiGas field not available for " << type() << abort(FatalError);
				return surfaceScalarField::null();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //