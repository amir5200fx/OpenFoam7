#include <radial.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <IOstreams.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(radial, 0);

		addToRunTimeSelectionTable(extrudeModel, radial, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		radial::radial(const dictionary& dict)
			:
			extrudeModel(typeName, dict),
			R_(Function1<scalar>::New("R", coeffDict_))
		{}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		radial::~radial()
		{}


		// * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * //

		point radial::operator()
			(
				const point& surfacePoint,
				const vector& surfaceNormal,
				const label layer
				) const
		{
			// radius of the surface
			scalar rs = mag(surfacePoint);
			vector rsHat = surfacePoint / rs;

			scalar r = R_->value(layer);

			Pout << "** for layer " << layer << " r:" << r << endl;

			return r * rsHat;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //