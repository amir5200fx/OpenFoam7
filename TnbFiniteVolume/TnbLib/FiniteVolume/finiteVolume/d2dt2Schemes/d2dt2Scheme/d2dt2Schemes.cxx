#include <d2dt2Scheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

		defineTemplateRunTimeSelectionTable(d2dt2Scheme<scalar>, Istream);
		defineTemplateRunTimeSelectionTable(d2dt2Scheme<vector>, Istream);
		defineTemplateRunTimeSelectionTable(d2dt2Scheme<sphericalTensor>, Istream);
		defineTemplateRunTimeSelectionTable(d2dt2Scheme<symmTensor>, Istream);
		defineTemplateRunTimeSelectionTable(d2dt2Scheme<tensor>, Istream);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //