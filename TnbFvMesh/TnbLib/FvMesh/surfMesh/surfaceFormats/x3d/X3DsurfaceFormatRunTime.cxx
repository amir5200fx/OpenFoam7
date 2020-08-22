#include <X3DsurfaceFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
namespace tnbLib
{
	namespace fileFormats
	{

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			X3DsurfaceFormat,
			face,
			write,
			fileExtension,
			x3d
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			X3DsurfaceFormat,
			triFace,
			write,
			fileExtension,
			x3d
		);

	}
}

// ************************************************************************* //