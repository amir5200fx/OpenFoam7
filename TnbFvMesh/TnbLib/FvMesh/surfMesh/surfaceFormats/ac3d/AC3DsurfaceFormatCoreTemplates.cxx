#include <AC3DsurfaceFormatCore.hxx>

#include <IStringStream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
Type tnbLib::fileFormats::AC3DsurfaceFormatCore::parse(const string& s)
{
	IStringStream ss(s);

	Type t;
	ss >> t;
	return t;
}


// ************************************************************************* //