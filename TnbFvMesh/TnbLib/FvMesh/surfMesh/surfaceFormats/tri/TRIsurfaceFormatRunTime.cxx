#include <TRIsurfaceFormat.hxx>

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
			TRIsurfaceFormat,
			face,
			fileExtension,
			tri
		);
		addNamedTemplatedToRunTimeSelectionTable
		(
			MeshedSurface,
			TRIsurfaceFormat,
			triFace,
			fileExtension,
			tri
		);

		// write MeshedSurfaceProxy
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			TRIsurfaceFormat,
			face,
			write,
			fileExtension,
			tri
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			MeshedSurfaceProxy,
			TRIsurfaceFormat,
			triFace,
			write,
			fileExtension,
			tri
		);

		// write UnsortedMeshedSurface
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			TRIsurfaceFormat,
			face,
			write,
			fileExtension,
			tri
		);
		addNamedTemplatedToMemberFunctionSelectionTable
		(
			UnsortedMeshedSurface,
			TRIsurfaceFormat,
			triFace,
			write,
			fileExtension,
			tri
		);

	}
}

// ************************************************************************* //