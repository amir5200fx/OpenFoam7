#include <VTKsurfaceFormat.hxx>

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
			VTKsurfaceFormat,
			face,
			fileExtension,
			vtk
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			VTKsurfaceFormat,
			triFace,
			fileExtension,
			vtk
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			VTKsurfaceFormat,
			face,
			write,
			fileExtension,
			vtk
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			VTKsurfaceFormat,
			triFace,
			write,
			fileExtension,
			vtk
		);

		// write UnsortedMeshedSurface
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			VTKsurfaceFormat,
			face,
			write,
			fileExtension,
			vtk
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			VTKsurfaceFormat,
			triFace,
			write,
			fileExtension,
			vtk
		);


	}
}

// ************************************************************************* //