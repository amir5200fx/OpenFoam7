#include <NASsurfaceFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read MeshedSurface - .bdf (Bulk Data Format)
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			NASsurfaceFormat,
			face,
			fileExtension,
			bdf
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			NASsurfaceFormat,
			face,
			fileExtension,
			nas
		);

		// read MeshedSurface - .nas (Nastran)
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			NASsurfaceFormat,
			triFace,
			fileExtension,
			bdf
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			NASsurfaceFormat,
			triFace,
			fileExtension,
			nas
		);

	}
}

// ************************************************************************* //