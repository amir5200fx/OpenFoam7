#include <VTKedgeFormat.hxx>

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
			VTKedgeFormat,
			fileExtension,
			vtk
		);

		// write edgeMesh
		addNamedToMemberFunctionSelectionTable
		(
			edgeMesh,
			VTKedgeFormat,
			write,
			fileExtension,
			vtk
		);

	}
}

// ************************************************************************* //