#include <SMESHsurfaceFormat.hxx>

#include <clock.hxx>
#include <IFstream.hxx>
#include <OFstream.hxx>
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Face>
tnbLib::fileFormats::SMESHsurfaceFormat<Face>::SMESHsurfaceFormat()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
void tnbLib::fileFormats::SMESHsurfaceFormat<Face>::write
(
	const fileName& filename,
	const MeshedSurfaceProxy<Face>& surf
)
{
	const pointField& pointLst = surf.points();
	const List<Face>&  faceLst = surf.faces();
	const List<label>& faceMap = surf.faceMap();

	const List<surfZone>& zones =
		(
			surf.surfZones().empty()
			? surfaceFormatsCore::oneZone(faceLst)
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


	// Write header
	os << "# tetgen .smesh file written " << clock::dateTime().c_str() << nl
		<< "# <points count=\"" << pointLst.size() << "\">" << nl
		<< pointLst.size() << " 3" << nl;    // 3: dimensions

	// Write vertex coords
	forAll(pointLst, ptI)
	{
		const point& pt = pointLst[ptI];

		os << ptI << ' ' << pt.x() << ' ' << pt.y() << ' ' << pt.z() << nl;
	}
	os << "# </points>" << nl
		<< nl
		<< "# <faces count=\"" << faceLst.size() << "\">" << endl;

	os << faceLst.size() << " 1" << endl;   // one attribute: zone number


	label faceIndex = 0;
	forAll(zones, zoneI)
	{
		const surfZone& zone = zones[zoneI];

		if (useFaceMap)
		{
			forAll(zone, localFacei)
			{
				const Face& f = faceLst[faceMap[faceIndex++]];

				os << f.size();
				forAll(f, fp)
				{
					os << ' ' << f[fp];
				}
				os << ' ' << zoneI << endl;
			}
		}
		else
		{
			forAll(zones[zoneI], localFacei)
			{
				const Face& f = faceLst[faceIndex++];

				os << f.size();
				forAll(f, fp)
				{
					os << ' ' << f[fp];
				}
				os << ' ' << zoneI << endl;
			}
		}
	}

	// write tail

	os << "# </faces>" << nl
		<< nl
		<< "# no holes or regions:" << nl
		<< '0' << nl        // holes
		<< '0' << endl;     // regions
}


// ************************************************************************* //