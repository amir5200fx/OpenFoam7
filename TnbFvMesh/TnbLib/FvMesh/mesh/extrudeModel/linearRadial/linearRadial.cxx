#include <linearRadial.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(linearRadial, 0);

		addToRunTimeSelectionTable(extrudeModel, linearRadial, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		linearRadial::linearRadial(const dictionary& dict)
			:
			extrudeModel(typeName, dict),
			R_(readScalar(coeffDict_.lookup("R"))),
			Rsurface_(coeffDict_.lookupOrDefault<scalar>("Rsurface", -1))
		{}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		linearRadial::~linearRadial()
		{}


		// * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * //

		point linearRadial::operator()
			(
				const point& surfacePoint,
				const vector& surfaceNormal,
				const label layer
				) const
		{
			// radius of the surface
			scalar rs = mag(surfacePoint);
			vector rsHat = surfacePoint / rs;
			if (Rsurface_ >= 0) rs = Rsurface_;

			scalar r = rs + (R_ - rs)*sumThickness(layer);
			return r * rsHat;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //