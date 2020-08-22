#include <OFFsurfaceFormat.hxx>

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
			OFFsurfaceFormat,
			face,
			fileExtension,
			off
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			OFFsurfaceFormat,
			triFace,
			fileExtension,
			off
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OFFsurfaceFormat,
			face,
			write,
			fileExtension,
			off
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			OFFsurfaceFormat,
			triFace,
			write,
			fileExtension,
			off
		);


	}
}

// ************************************************************************* //