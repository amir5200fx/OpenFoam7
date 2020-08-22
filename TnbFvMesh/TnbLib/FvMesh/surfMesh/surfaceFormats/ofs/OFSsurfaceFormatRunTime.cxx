#include <OFSsurfaceFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read MeshedSurface
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			OFSsurfaceFormat,
			face,
			fileExtension,
			ofs
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			OFSsurfaceFormat,
			triFace,
			fileExtension,
			ofs
		);


		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OFSsurfaceFormat,
			face,
			write,
			fileExtension,
			ofs
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OFSsurfaceFormat,
			triFace,
			write,
			fileExtension,
			ofs
		);


	}
}

// ************************************************************************* //