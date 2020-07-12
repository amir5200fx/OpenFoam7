#include <edgeMeshFormat.hxx>

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
			edgeMeshFormat,
			fileExtension,
			eMesh
		);

		// write edgeMesh
		addNamedToMemberFunctionSelectionTable
		(
			edgeMesh,
			edgeMeshFormat,
			write,
			fileExtension,
			eMesh
		);

	}
}

// ************************************************************************* //