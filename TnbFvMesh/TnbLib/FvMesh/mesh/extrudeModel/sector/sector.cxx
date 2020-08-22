#include <sector.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <unitConversion.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(sector, 0);

		addToRunTimeSelectionTable(extrudeModel, sector, dictionary);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		sector::sector(const dictionary& dict)
			:
			extrudeModel(typeName, dict),
			axisPt_(coeffDict_.lookup("axisPt")),
			axis_(coeffDict_.lookup("axis")),
			angle_
			(
				degToRad(readScalar(coeffDict_.lookup("angle")))
			)
		{}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		sector::~sector()
		{}


		// * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * //

		point sector::operator()
			(
				const point& surfacePoint,
				const vector& surfaceNormal,
				const label layer
				) const
		{
			scalar sliceAngle;

			// For the case of a single layer extrusion assume a
			// symmetric sector about the reference plane is required
			if (nLayers_ == 1)
			{
				if (layer == 0)
				{
					sliceAngle = -angle_ / 2.0;
				}
				else
				{
					sliceAngle = angle_ / 2.0;
				}
			}
			else
			{
				sliceAngle = angle_ * sumThickness(layer);
			}

			// Find projection onto axis (or rather decompose surfacePoint
			// into vector along edge (proj), vector normal to edge in plane
			// of surface point and surface normal.
			point d = surfacePoint - axisPt_;

			d -= (axis_ & d)*axis_;

			scalar dMag = mag(d);

			point edgePt = surfacePoint - d;

			// Rotate point around sliceAngle.
			point rotatedPoint = edgePt;

			if (dMag > vSmall)
			{
				vector n = (d / dMag) ^ axis_;

				rotatedPoint +=
					+cos(sliceAngle)*d
					- sin(sliceAngle)*mag(d)*n; // Use either n or surfaceNormal
			}

			return rotatedPoint;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// ************************************************************************* //