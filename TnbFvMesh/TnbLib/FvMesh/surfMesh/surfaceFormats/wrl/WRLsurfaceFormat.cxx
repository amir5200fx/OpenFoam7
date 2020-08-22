#include <WRLsurfaceFormat.hxx>

#include <Ostream.hxx>
#include <OFstream.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Face>
tnbLib::fileFormats::WRLsurfaceFormat<Face>::WRLsurfaceFormat()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
void tnbLib::fileFormats::WRLsurfaceFormat<Face>::write
(
	const fileName& filename,
	const MeshedSurfaceProxy<Face>& surf
)
{
	const pointField& pointLst = surf.points();
	const List<Face>&  faceLst = surf.faces();
	const List<label>& faceMap = surf.faceMap();

	// for no zones, suppress the group name
	const List<surfZone>& zones =
		(
			surf.surfZones().empty()
			? surfaceFormatsCore::oneZone(faceLst, "")
			: surf.surfZones()
			);

	const bool useFaceMap = (surf.useFaceMap() && zones.size() > 1);

	OFstream os(filename);
	if (!os.good())
	{
		FatalErrorInFunction
			<< "Cannot open file for writing " << filename
			<< exit(FatalError);
	}

	writeHeader(os, pointLst, faceLst.size(), zones);

	os << "\n"
		"Group {\n"
		" children [\n"
		"  Shape {\n";

	writeAppearance(os);

	os <<
		"   geometry IndexedFaceSet {\n"
		"    coord Coordinate {\n"
		"     point [\n";

	// Write vertex coords
	forAll(pointLst, ptI)
	{
		const point& pt = pointLst[ptI];

		os << pt.x() << ' ' << pt.y() << ' ' << pt.z() << nl;
	}

	os <<
		"     ]\n"                     // end point
		"    }\n"                      // end coord Coordinate
		"    coordIndex [\n";

	label faceIndex = 0;
	forAll(zones, zoneI)
	{
		const surfZone& zone = zones[zoneI];

		if (useFaceMap)
		{
			forAll(zone, localFacei)
			{
				const Face& f = faceLst[faceMap[faceIndex++]];

				forAll(f, fp)
				{
					os << f[fp] << ' ';
				}
				os << "-1,\n";
			}
		}
		else
		{
			forAll(zone, localFacei)
			{
				const Face& f = faceLst[faceIndex++];

				forAll(f, fp)
				{
					os << ' ' << f[fp];
				}
				os << " -1,\n";
			}
		}
	}

	os <<
		"    ]\n"                      // end coordIndex
		"   }\n"                       // end geometry IndexedFaceSet
		"  }\n"                        // end Shape
		" ]\n"                         // end children
		"}\n";                         // end Group
}


// ************************************************************************* //