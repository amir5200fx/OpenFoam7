#include <ddtScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

		defineTemplateRunTimeSelectionTable(ddtScheme<scalar>, Istream);
		defineTemplateRunTimeSelectionTable(ddtScheme<vector>, Istream);
		defineTemplateRunTimeSelectionTable(ddtScheme<sphericalTensor>, Istream);
		defineTemplateRunTimeSelectionTable(ddtScheme<symmTensor>, Istream);
		defineTemplateRunTimeSelectionTable(ddtScheme<tensor>, Istream);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //