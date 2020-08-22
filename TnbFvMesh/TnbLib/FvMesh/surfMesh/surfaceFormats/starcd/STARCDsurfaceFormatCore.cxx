#include <STARCDsurfaceFormatCore.hxx>

#include <clock.hxx>
#include <regExp.hxx>
#include <IStringStream.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

// parse things like this:
//     CTNAME  1  someName
// don't bother with the older comma-delimited format

tnbLib::Map<tnbLib::word>
tnbLib::fileFormats::STARCDsurfaceFormatCore::readInpCellTable
(
	IFstream& is
)
{
	Map<word> lookup;

	regExp ctnameRE
	(
		" *CTNA[^ ]*"        // keyword - min 4 chars
		"[[:space:]]+"       // space delimited
		"([0-9]+)"           // 1: <digits>
		"[[:space:]]+"       // space delimited
		"([^,[:space:]].*)", // 2: <name>
		true                 // ignore case
	);

	string line;
	List<string> groups;
	while (is.good() && is.getLine(line).good())
	{
		if (ctnameRE.match(line, groups))
		{
			const label tableId = atoi(groups[0].c_str());

			// strip bad chars
			string::stripInvalid<word>(groups[1]);

			if (!groups[1].empty())
			{
				lookup.insert(tableId, groups[1]);
			}
		}
	}

	return lookup;
}


void tnbLib::fileFormats::STARCDsurfaceFormatCore::writeCase
(
	Ostream& os,
	const pointField& pointLst,
	const label nFaces,
	const UList<surfZone>& zoneLst
)
{
	word caseName = os.name().lessExt().name();

	os << "! STAR-CD file written " << clock::dateTime().c_str() << nl
		<< "! " << pointLst.size() << " points, " << nFaces << " faces" << nl
		<< "! case " << caseName << nl
		<< "! ------------------------------" << nl;

	forAll(zoneLst, zoneI)
	{
		os << "ctable " << zoneI + 1 << " shell" << " ,,,,,," << nl
			<< "ctname " << zoneI + 1 << " "
			<< zoneLst[zoneI].name() << nl;
	}

	os << "! ------------------------------" << nl
		<< "*set icvo mxv - 1" << nl
		<< "vread " << caseName << ".vrt icvo,,,coded" << nl
		<< "cread " << caseName << ".cel icvo,,,add,coded" << nl
		<< "*set icvo" << nl
		<< "! end" << nl;

	os.flush();
}


// ************************************************************************* //