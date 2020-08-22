#include <linearDirection.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(linearDirection, 0);

		addToRunTimeSelectionTable(extrudeModel, linearDirection, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		linearDirection::linearDirection(const dictionary& dict)
			:
			extrudeModel(typeName, dict),
			direction_(coeffDict_.lookup("direction")),
			thickness_(readScalar(coeffDict_.lookup("thickness")))
		{
			direction_ /= mag(direction_);

			if (thickness_ <= 0)
			{
				FatalErrorInFunction
					<< "thickness should be positive : " << thickness_
					<< exit(FatalError);
			}
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		linearDirection::~linearDirection()
		{}


		// * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * //

		point linearDirection::operator()
			(
				const point& surfacePoint,
				const vector& surfaceNormal,
				const label layer
				) const
		{
			// scalar d = thickness_*layer/nLayers_;
			scalar d = thickness_ * sumThickness(layer);
			return surfacePoint + d * direction_;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //