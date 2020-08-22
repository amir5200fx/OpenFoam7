#include <AC3DsurfaceFormatCore.hxx>

#include <clock.hxx>
#include <IFstream.hxx>
#include <IStringStream.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::fileFormats::AC3DsurfaceFormatCore::readCmd
(
	IFstream& is,
	string& cmd,
	string& args
)
{
	if (is.good())
	{
		string line;
		is.getLine(line);

		string::size_type space = line.find(' ');

		if (space != string::npos)
		{
			cmd = line.substr(0, space);
			args = line.substr(space + 1);

			return true;
		}
	}
	return false;
}


// Read up to line starting with cmd. Sets args to rest of line.
// Returns true if found, false if stream is not good anymore.
bool tnbLib::fileFormats::AC3DsurfaceFormatCore::cueTo
(
	IFstream& is,
	const string& cmd,
	string& args
)
{
	while (is.good())
	{
		string line;
		is.getLine(line);

		string::size_type space = line.find(' ');

		if (space != string::npos)
		{
			if (line.substr(0, space) == cmd)
			{
				args = line.substr(space + 1);

				return true;
			}
		}
	}
	return false;
}


// Similar to cueTo(), but throws error if cmd not found
tnbLib::string tnbLib::fileFormats::AC3DsurfaceFormatCore::cueToOrDie
(
	IFstream& is,
	const string& cmd,
	const string& errorMsg
)
{
	string args;
	if (!cueTo(is, cmd, args))
	{
		FatalErrorInFunction
			<< "Cannot find command " << cmd
			<< " " << errorMsg
			<< exit(FatalError);
	}

	return args;
}


void tnbLib::fileFormats::AC3DsurfaceFormatCore::writeHeader
(
	Ostream& os,
	const UList<surfZone>& zoneLst
)
{
	// Write with zones as separate objects under "world" object.
	// Header is taken over from sample file.
	// Defines separate materials for all zones. Recycle colours.

	// Define 8 standard colours as r,g,b components
	static scalar colourMap[] =
	{
		1, 1, 1,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 0,
		0, 1, 1,
		1, 0, 1,
		0.5, 0.5, 1
	};

	// Write header. Define materials.
	os << "AC3Db" << nl;

	forAll(zoneLst, zoneI)
	{
		label colourI = zoneI % 8;
		label colourCompI = 3 * colourI;

		os << "MATERIAL \"" << zoneLst[zoneI].name() << "Mat\" rgb "
			<< colourMap[colourCompI] << ' ' << colourMap[colourCompI + 1]
			<< ' ' << colourMap[colourCompI + 2]
			<< "  amb 0.2 0.2 0.2  emis 0 0 0  spec 0.5 0.5 0.5  shi 10"
			<< "  trans 0"
			<< nl;
	}

	os << "OBJECT world" << nl
		<< "kids " << zoneLst.size() << endl;
}


// ************************************************************************* //