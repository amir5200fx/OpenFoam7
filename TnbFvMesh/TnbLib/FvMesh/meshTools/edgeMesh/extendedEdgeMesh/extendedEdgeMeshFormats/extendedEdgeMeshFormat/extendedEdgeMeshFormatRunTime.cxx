#include <extendedEdgeMeshFormat.hxx>

#include <extendedEdgeMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		// read extendedEdgeMesh
		addNamedToRunTimeSelectionTable
		(
			extendedEdgeMesh,
			extendedEdgeMeshFormat,
			fileExtension,
			extendedFeatureEdgeMesh         // extension
		);

	}
}

// ************************************************************************* //