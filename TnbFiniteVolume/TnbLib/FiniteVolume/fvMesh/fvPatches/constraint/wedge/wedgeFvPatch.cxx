#include <wedgeFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(wedgeFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, wedgeFvPatch, polyPatch);


	// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

	wedgeFvPatch::wedgeFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
		:
		fvPatch(patch, bm),
		wedgePolyPatch_(refCast<const wedgePolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
