#include <AC3DsurfaceFormat.hxx>

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
			AC3DsurfaceFormat,
			face,
			fileExtension,
			ac
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			AC3DsurfaceFormat,
			triFace,
			fileExtension,
			ac
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			AC3DsurfaceFormat,
			face,
			write,
			fileExtension,
			ac
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			AC3DsurfaceFormat,
			triFace,
			write,
			fileExtension,
			ac
		);


		// write UnsortedMeshedSurface
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			AC3DsurfaceFormat,
			face,
			write,
			fileExtension,
			ac
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			AC3DsurfaceFormat,
			triFace,
			write,
			fileExtension,
			ac
		);

	}
}

// ************************************************************************* //
