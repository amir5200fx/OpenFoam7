#include <OBJedgeFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read edgeMesh
		addNamedToRunTimeSelectionTable
		(
			edgeMesh,
			OBJedgeFormat,
			fileExtension,
			obj
		);

		// write edgeMesh
		addNamedToMemberFunctionSelectionTable
		(
			edgeMesh,
			OBJedgeFormat,
			write,
			fileExtension,
			obj
		);

	}
}

// ************************************************************************* //