#include <NASedgeFormat.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read edgeMesh - .bdf (Bulk Data Format)
		addNamedToRunTimeSelectionTable
		(
			edgeMesh,
			NASedgeFormat,
			fileExtension,
			bdf
		);

		// read edgeMesh - .nas (Nastran Data Format)
		addNamedToRunTimeSelectionTable
		(
			edgeMesh,
			NASedgeFormat,
			fileExtension,
			nas
		);

	}
}

// ************************************************************************* //