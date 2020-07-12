#include <extendedFeatureEdgeMeshFormat.hxx>

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
			edgeMesh,
			extendedFeatureEdgeMeshFormat,
			fileExtension,
			featureEdgeMesh
		);

	}
}

// ************************************************************************* //