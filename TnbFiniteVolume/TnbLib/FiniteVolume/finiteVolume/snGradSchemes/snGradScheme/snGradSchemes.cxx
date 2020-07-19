#include <snGradScheme.hxx>

#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

		defineTemplateRunTimeSelectionTable(snGradScheme<scalar>, Mesh);
		defineTemplateRunTimeSelectionTable(snGradScheme<vector>, Mesh);
		defineTemplateRunTimeSelectionTable(snGradScheme<sphericalTensor>, Mesh);
		defineTemplateRunTimeSelectionTable(snGradScheme<symmTensor>, Mesh);
		defineTemplateRunTimeSelectionTable(snGradScheme<tensor>, Mesh);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //