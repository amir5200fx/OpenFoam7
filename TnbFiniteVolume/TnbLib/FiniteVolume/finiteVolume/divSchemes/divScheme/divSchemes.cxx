#include <divScheme.hxx>

#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

		defineTemplateRunTimeSelectionTable
		(
			divScheme<vector>,
			Istream
		);

		defineTemplateRunTimeSelectionTable
		(
			divScheme<sphericalTensor>,
			Istream
		);

		defineTemplateRunTimeSelectionTable
		(
			divScheme<symmTensor>,
			Istream
		);

		defineTemplateRunTimeSelectionTable
		(
			divScheme<tensor>,
			Istream
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //