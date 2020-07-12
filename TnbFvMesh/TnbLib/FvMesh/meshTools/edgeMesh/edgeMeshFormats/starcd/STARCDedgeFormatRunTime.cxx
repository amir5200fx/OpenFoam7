#include <STARCDedgeFormat.hxx>

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
			STARCDedgeFormat,
			fileExtension,
			inp
		);

		// write edgeMesh
		addNamedToMemberFunctionSelectionTable
		(
			edgeMesh,
			STARCDedgeFormat,
			write,
			fileExtension,
			inp
		);

	}
}

// ************************************************************************* //