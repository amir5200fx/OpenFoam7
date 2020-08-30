#include <waxSolventViscosity.hxx>

#include <kinematicSingleLayer.hxx>
#include <waxSolventEvaporation.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <zeroGradientFvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(waxSolventViscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				waxSolventViscosity,
				dictionary
			);


			// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

			void waxSolventViscosity::correctMu()
			{
				const kinematicSingleLayer& film = filmType<kinematicSingleLayer>();

				const uniformDimensionedScalarField Wwax
				(
					film.regionMesh().lookupObject<uniformDimensionedScalarField>
					(
						waxSolventEvaporation::typeName + ":Wwax"
						)
				);

				const uniformDimensionedScalarField Wsolvent
				(
					film.regionMesh().lookupObject<uniformDimensionedScalarField>
					(
						waxSolventEvaporation::typeName + ":Wsolvent"
						)
				);

				const uniformDimensionedScalarField Ysolvent0
				(
					film.regionMesh().lookupObject<uniformDimensionedScalarField>
					(
						waxSolventEvaporation::typeName + ":Ysolvent0"
						)
				);

				const volScalarField& Ysolvent
				(
					film.regionMesh().lookupObject<volScalarField>
					(
						waxSolventEvaporation::typeName + ":Ysolvent"
						)
				);

				const volScalarField Xsolvent
				(
					Ysolvent*Wsolvent / ((1 - Ysolvent)*Wwax + Ysolvent * Wsolvent)
				);

				const dimensionedScalar Xsolvent0
				(
					Ysolvent0*Wsolvent / ((1 - Ysolvent0)*Wwax + Ysolvent0 * Wsolvent)
				);

				mu_ = pow(muWax_ / muSolvent_, (1 - Xsolvent) / (1 - Xsolvent0))*muSolvent_;
				mu_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			waxSolventViscosity::waxSolventViscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu),
				muWax_
				(
					IOobject
					(
						typeName + ":muWax",
						film.regionMesh().time().timeName(),
						film.regionMesh(),
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimDynamicViscosity, 0),
					zeroGradientFvPatchScalarField::typeName
				),
				muWaxModel_
				(
					filmViscosityModel::New
					(
						film,
						coeffDict_.subDict("muWax"),
						muWax_
					)
				),
				muSolvent_
				(
					IOobject
					(
						typeName + ":muSolvent",
						film.regionMesh().time().timeName(),
						film.regionMesh(),
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimDynamicViscosity, 0),
					zeroGradientFvPatchScalarField::typeName
				),
				muSolventModel_
				(
					filmViscosityModel::New
					(
						film,
						coeffDict_.subDict("muSolvent"),
						muSolvent_
					)
				)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			waxSolventViscosity::~waxSolventViscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void waxSolventViscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				muWaxModel_->correct(p, T);
				muSolventModel_->correct(p, T);

				correctMu();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //