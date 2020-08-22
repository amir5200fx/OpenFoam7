#include <sigmaRadial.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(sigmaRadial, 0);

		addToRunTimeSelectionTable(extrudeModel, sigmaRadial, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		sigmaRadial::sigmaRadial(const dictionary& dict)
			:
			extrudeModel(typeName, dict),
			RTbyg_(readScalar(coeffDict_.lookup("RTbyg"))),
			pRef_(readScalar(coeffDict_.lookup("pRef"))),
			pStrat_(readScalar(coeffDict_.lookup("pStrat")))
		{
			if (mag(expansionRatio() - 1.0) > small)
			{
				WarningInFunction
					<< "Ignoring expansionRatio setting." << endl;
			}
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		sigmaRadial::~sigmaRadial()
		{}


		// * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * //

		point sigmaRadial::operator()
			(
				const point& surfacePoint,
				const vector& surfaceNormal,
				const label layer
				) const
		{
			// radius of the surface
			scalar rs = mag(surfacePoint);
			vector rsHat = surfacePoint / rs;

			scalar p = pRef_ - layer * (pRef_ - pStrat_) / nLayers_;
			scalar r = rs - RTbyg_ * log(p / pRef_);

			return r * rsHat;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //