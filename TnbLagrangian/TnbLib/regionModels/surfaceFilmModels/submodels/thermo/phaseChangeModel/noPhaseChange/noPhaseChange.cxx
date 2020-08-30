#include <noPhaseChange.hxx>

#include <addToRunTimeSelectionTable.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(noPhaseChange, 0);
			addToRunTimeSelectionTable(phaseChangeModel, noPhaseChange, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			noPhaseChange::noPhaseChange
			(
				surfaceFilmRegionModel& film,
				const dictionary&
			)
				:
				phaseChangeModel(film)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			noPhaseChange::~noPhaseChange()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			bool noPhaseChange::active() const
			{
				return false;
			}


			void noPhaseChange::correctModel
			(
				const scalar,
				scalarField&,
				scalarField&,
				scalarField&
			)
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //