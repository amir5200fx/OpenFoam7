#include <STARCDsurfaceFormat.hxx>

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
			STARCDsurfaceFormat,
			face,
			fileExtension,
			inp
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			STARCDsurfaceFormat,
			triFace,
			fileExtension,
			inp
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STARCDsurfaceFormat,
			face,
			write,
			fileExtension,
			inp
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STARCDsurfaceFormat,
			triFace,
			write,
			fileExtension,
			inp
		);


	}
}

// ************************************************************************* //