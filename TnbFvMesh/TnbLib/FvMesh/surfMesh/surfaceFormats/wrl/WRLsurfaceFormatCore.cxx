#include <WRLsurfaceFormatCore.hxx>

#include <clock.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fileFormats::WRLsurfaceFormatCore::writeHeader
(
	Ostream& os,
	const pointField& pointLst,
	const label nFaces,
	const UList<surfZone>& zoneLst
)
{
	os << "#VRML V2.0 utf8" << nl
		<< nl
		<< "# written " << clock::dateTime().c_str() << nl
		<< "# points : " << pointLst.size() << nl
		<< "# faces  : " << nFaces << nl
		<< "# zones  : " << zoneLst.size() << nl;

	// Print zone names as comment
	forAll(zoneLst, zoneI)
	{
		os << "#   " << zoneI << "  " << zoneLst[zoneI].name()
			<< "  (nFaces: " << zoneLst[zoneI].size() << ")" << nl;
	}
}


void tnbLib::fileFormats::WRLsurfaceFormatCore::writeAppearance
(
	Ostream& os
)
{
	os <<
		"   appearance Appearance {\n"
		"    material Material {\n"
		"     diffuseColor   0.8 0.8 0.8\n"
		"     specularColor  1.0 1.0 1.0\n"
		"     shininess      0.5\n"
		"     transparency   0.0\n"
		"    }\n"                      // end material
		"   }\n";                      // end appearance

}


// ************************************************************************* //