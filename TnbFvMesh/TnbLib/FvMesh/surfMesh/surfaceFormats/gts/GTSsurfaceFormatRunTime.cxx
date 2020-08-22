#include <GTSsurfaceFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read UnsortedMeshedSurface
		addNamedTemplatedToRunTimeSelectionTable
		(
			UnsortedMeshedSurface,
			GTSsurfaceFormat,
			face,
			fileExtension,
			gts
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			UnsortedMeshedSurface,
			GTSsurfaceFormat,
			triFace,
			fileExtension,
			gts
		);

		// write MeshedSurface
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurface,
			GTSsurfaceFormat,
			face,
			write,
			fileExtension,
			gts
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurface,
			GTSsurfaceFormat,
			triFace,
			write,
			fileExtension,
			gts
		);

		// write UnsortedMeshedSurface
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			GTSsurfaceFormat,
			face,
			write,
			fileExtension,
			gts
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			GTSsurfaceFormat,
			triFace,
			write,
			fileExtension,
			gts
		);

	}
}

// ************************************************************************* //