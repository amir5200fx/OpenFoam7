#include <planeExtrusion.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(plane, 0);

		addToRunTimeSelectionTable(extrudeModel, plane, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		plane::plane(const dictionary& dict)
			:
			linearNormal(dict)
		{
			if (nLayers_ != 1)
			{
				IOWarningInFunction(dict)
					<< "Expected nLayers (if specified) to be 1"
					<< endl;
				nLayers_ = 1;
			}
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		plane::~plane()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //