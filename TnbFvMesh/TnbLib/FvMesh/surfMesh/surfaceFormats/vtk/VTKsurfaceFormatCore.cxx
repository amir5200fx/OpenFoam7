#include <VTKsurfaceFormatCore.hxx>

#include <clock.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fileFormats::VTKsurfaceFormatCore::writeHeader
(
	Ostream& os,
	const pointField& pointLst
)
{
	// Write header
	os << "# vtk DataFile Version 2.0" << nl
		<< "surface written " << clock::dateTime().c_str() << nl
		<< "ASCII" << nl
		<< nl
		<< "DATASET POLYDATA" << nl;

	// Write vertex coords
	os << "POINTS " << pointLst.size() << " float" << nl;
	forAll(pointLst, ptI)
	{
		const point& pt = pointLst[ptI];

		os << pt.x() << ' ' << pt.y() << ' ' << pt.z() << nl;
	}
}


void tnbLib::fileFormats::VTKsurfaceFormatCore::writeTail
(
	Ostream& os,
	const UList<surfZone>& zoneLst
)
{
	label nFaces = 0;
	forAll(zoneLst, zoneI)
	{
		nFaces += zoneLst[zoneI].size();
	}

	// Print zone numbers
	os << nl
		<< "CELL_DATA " << nFaces << nl
		<< "FIELD attributes 1" << nl
		<< "region 1 " << nFaces << " float" << nl;


	forAll(zoneLst, zoneI)
	{
		forAll(zoneLst[zoneI], localFacei)
		{
			if (localFacei)
			{
				if (localFacei % 20)
				{
					os << ' ';
				}
				else
				{
					os << nl;
				}
			}
			os << zoneI + 1;
		}
		os << nl;
	}
}


void tnbLib::fileFormats::VTKsurfaceFormatCore::writeTail
(
	Ostream& os,
	const labelUList& zoneIds
)
{
	// Print zone numbers
	os << nl
		<< "CELL_DATA " << zoneIds.size() << nl
		<< "FIELD attributes 1" << nl
		<< "region 1 " << zoneIds.size() << " float" << nl;

	forAll(zoneIds, facei)
	{
		if (facei)
		{
			if (facei % 20)
			{
				os << ' ';
			}
			else
			{
				os << nl;
			}
		}
		os << zoneIds[facei] + 1;
	}
	os << nl;
}


// ************************************************************************* //