#include <wedge.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(wedge, 0);

		addToRunTimeSelectionTable(extrudeModel, wedge, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		wedge::wedge(const dictionary& dict)
			:
			sector(dict)
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

		wedge::~wedge()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //