#include <cyclicSector.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(cyclicSector, 0);

		addToRunTimeSelectionTable(extrudeModel, cyclicSector, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		cyclicSector::cyclicSector(const dictionary& dict)
			:
			sector(dict)
		{}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		cyclicSector::~cyclicSector()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //