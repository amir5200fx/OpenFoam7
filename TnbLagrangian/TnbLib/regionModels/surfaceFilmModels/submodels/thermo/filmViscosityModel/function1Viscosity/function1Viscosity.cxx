#include <function1Viscosity.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(function1Viscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				function1Viscosity,
				dictionary
			);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			function1Viscosity::function1Viscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu),
				viscosity_(filmViscosityModel::New(film, coeffDict_, mu)),
				function_
				(
					Function1<scalar>::New("function", coeffDict_)
				)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			function1Viscosity::~function1Viscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void function1Viscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				viscosity_->correct(p, T);
				mu_.primitiveFieldRef() *= function_->value(T)();
				mu_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //