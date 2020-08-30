#include <noThermo.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace thermalBaffleModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(noThermo, 0);

			addToRunTimeSelectionTable(thermalBaffleModel, noThermo, mesh);
			addToRunTimeSelectionTable(thermalBaffleModel, noThermo, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			bool noThermo::read()
			{
				return regionModel1D::read();
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			noThermo::noThermo(const word& modelType, const fvMesh& mesh)
				:
				thermalBaffleModel(mesh)
			{}


			noThermo::noThermo
			(
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict
			)
				:
				thermalBaffleModel(modelType, mesh, dict)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			noThermo::~noThermo()
			{}

			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void noThermo::preEvolveRegion()
			{}


			void noThermo::evolveRegion()
			{}


			const tmp<volScalarField> noThermo::Cp() const
			{
				FatalErrorInFunction
					<< "Cp field not available for " << type()
					<< abort(FatalError);

				return tmp<volScalarField>
					(
						volScalarField::New
						(
							"noThermo::Cp",
							primaryMesh(),
							dimensionedScalar(dimEnergy / dimVolume / dimTime, 0)
						)
						);
			}

			const volScalarField& noThermo::kappaRad() const
			{
				FatalErrorInFunction
					<< "kappa field not available for " << type()
					<< abort(FatalError);
				return volScalarField::null();
			}


			const volScalarField& noThermo::rho() const
			{
				FatalErrorInFunction
					<< "rho field not available for " << type()
					<< abort(FatalError);
				return volScalarField::null();
			}


			const volScalarField& noThermo::kappa() const
			{
				FatalErrorInFunction
					<< "K field not available for " << type()
					<< abort(FatalError);
				return volScalarField::null();
			}


			const volScalarField& noThermo::T() const
			{
				FatalErrorInFunction
					<< "T field not available for " << type()
					<< abort(FatalError);
				return volScalarField::null();
			}


			const solidThermo& noThermo::thermo() const
			{
				FatalErrorInFunction
					<< "T field not available for " << type()
					<< abort(FatalError);
				return NullObjectRef<solidThermo>();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermalBaffleModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //