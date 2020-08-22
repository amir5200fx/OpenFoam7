#include <WRLsurfaceFormat.hxx>

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
			WRLsurfaceFormat,
			face,
			write,
			fileExtension,
			wrl
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			WRLsurfaceFormat,
			triFace,
			write,
			fileExtension,
			wrl
		);

	}
}

// ************************************************************************* //