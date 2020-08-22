#include <OBJsurfaceFormat.hxx>

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
			OBJsurfaceFormat,
			face,
			fileExtension,
			obj
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			OBJsurfaceFormat,
			triFace,
			fileExtension,
			obj
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OBJsurfaceFormat,
			face,
			write,
			fileExtension,
			obj
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OBJsurfaceFormat,
			triFace,
			write,
			fileExtension,
			obj
		);

	}
}

// ************************************************************************* //