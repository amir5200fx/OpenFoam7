#include <TRIsurfaceFormat.hxx>

#include <ListOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Face>
inline void tnbLib::fileFormats::TRIsurfaceFormat<Face>::writeShell
(
	Ostream& os,
	const pointField& pointLst,
	const Face& f,
	const label zoneI
)
{
	// simple triangulation about f[0].
	// better triangulation should have been done before
	const point& p0 = pointLst[f[0]];
	for (label fp1 = 1; fp1 < f.size() - 1; ++fp1)
	{
		label fp2 = f.fcIndex(fp1);

		const point& p1 = pointLst[f[fp1]];
		const point& p2 = pointLst[f[fp2]];

		os << p0.x() << ' ' << p0.y() << ' ' << p0.z() << ' '
			<< p1.x() << ' ' << p1.y() << ' ' << p1.z() << ' '
			<< p2.x() << ' ' << p2.y() << ' ' << p2.z() << ' '
			// zone as colour
			<< "0x" << hex << zoneI << dec << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Face>
tnbLib::fileFormats::TRIsurfaceFormat<Face>::TRIsurfaceFormat
(
	const fileName& filename
)
{
	read(filename);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
bool tnbLib::fileFormats::TRIsurfaceFormat<Face>::read
(
	const fileName& filename
)
{
	this->clear();

	// read in the values
	TRIsurfaceFormatCore reader(filename);

	// transfer points
	this->storedPoints().transfer(reader.points());

	// retrieve the original zone information
	List<label> sizes(move(reader.sizes()));
	List<label> zoneIds(move(reader.zoneIds()));

	// generate the (sorted) faces
	List<Face> faceLst(zoneIds.size());

	if (reader.sorted())
	{
		// already sorted - generate directly
		forAll(faceLst, facei)
		{
			const label startPt = 3 * facei;
			faceLst[facei] = triFace(startPt, startPt + 1, startPt + 2);
		}
	}
	else
	{
		// unsorted - determine the sorted order:
		// avoid SortableList since we discard the main list anyhow
		List<label> faceMap;
		sortedOrder(zoneIds, faceMap);

		// generate sorted faces
		forAll(faceMap, facei)
		{
			const label startPt = 3 * faceMap[facei];
			faceLst[facei] = triFace(startPt, startPt + 1, startPt + 2);
		}
	}
	zoneIds.clear();

	// transfer:
	this->storedFaces().transfer(faceLst);

	this->addZones(sizes);
	this->stitchFaces(small);
	return true;
}


template<class Face>
void tnbLib::fileFormats::TRIsurfaceFormat<Face>::write
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

	label faceIndex = 0;
	forAll(zones, zoneI)
	{
		const surfZone& zone = zones[zoneI];

		if (useFaceMap)
		{
			forAll(zone, localFacei)
			{
				const Face& f = faceLst[faceMap[faceIndex++]];
				writeShell(os, pointLst, f, zoneI);
			}
		}
		else
		{
			forAll(zone, localFacei)
			{
				const Face& f = faceLst[faceIndex++];
				writeShell(os, pointLst, f, zoneI);
			}
		}
	}
}


template<class Face>
void tnbLib::fileFormats::TRIsurfaceFormat<Face>::write
(
	const fileName& filename,
	const UnsortedMeshedSurface<Face>& surf
)
{
	const pointField& pointLst = surf.points();
	const List<Face>& faceLst = surf.faces();

	OFstream os(filename);
	if (!os.good())
	{
		FatalErrorInFunction
			<< "Cannot open file for writing " << filename
			<< exit(FatalError);
	}


	// a single zone needs no sorting
	if (surf.zoneToc().size() == 1)
	{
		const List<label>& zoneIds = surf.zoneIds();

		forAll(faceLst, facei)
		{
			writeShell(os, pointLst, faceLst[facei], zoneIds[facei]);
		}
	}
	else
	{
		labelList faceMap;
		List<surfZone> zoneLst = surf.sortedZones(faceMap);

		label faceIndex = 0;
		forAll(zoneLst, zoneI)
		{
			forAll(zoneLst[zoneI], localFacei)
			{
				const Face& f = faceLst[faceMap[faceIndex++]];
				writeShell(os, pointLst, f, zoneI);
			}
		}
	}
}


// ************************************************************************* //