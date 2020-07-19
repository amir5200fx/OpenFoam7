#include <emptyFvPatch.hxx>

#include <fvBoundaryMesh.hxx>
#include <fvMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(emptyFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, emptyFvPatch, polyPatch);


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	emptyFvPatch::emptyFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
		:
		fvPatch(patch, bm),
		faceCells_
		(
			labelList::subList
			(
				boundaryMesh().mesh().faceOwner(), 0, patch.start()
			)
		)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const labelUList& emptyFvPatch::faceCells() const
	{
		return faceCells_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //