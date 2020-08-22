#include <STLsurfaceFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read MeshedSurface (ascii)
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			STLsurfaceFormat,
			face,
			fileExtension,
			stl
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			STLsurfaceFormat,
			triFace,
			fileExtension,
			stl
		);

		// read MeshedSurface (binary)
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			STLsurfaceFormat,
			face,
			fileExtension,
			stlb
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			STLsurfaceFormat,
			triFace,
			fileExtension,
			stlb
		);


		// write MeshedSurfaceProxy (ascii)
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STLsurfaceFormat,
			face,
			write,
			fileExtension,
			stl
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STLsurfaceFormat,
			triFace,
			write,
			fileExtension,
			stl
		);

		// write MeshedSurfaceProxy (binary)
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STLsurfaceFormat,
			face,
			write,
			fileExtension,
			stlb
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			STLsurfaceFormat,
			triFace,
			write,
			fileExtension,
			stlb
		);

		// write UnsortedMeshedSurface (ascii)
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			STLsurfaceFormat,
			face,
			write,
			fileExtension,
			stl
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			STLsurfaceFormat,
			triFace,
			write,
			fileExtension,
			stl
		);

		// write UnsortedMeshedSurface (binary)
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			STLsurfaceFormat,
			face,
			write,
			fileExtension,
			stlb
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			STLsurfaceFormat,
			triFace,
			write,
			fileExtension,
			stlb
		);

	}
}

// ************************************************************************* //