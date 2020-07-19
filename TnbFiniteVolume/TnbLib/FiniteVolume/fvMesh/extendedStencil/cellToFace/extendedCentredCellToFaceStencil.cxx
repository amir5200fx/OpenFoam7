#include <extendedCentredCellToFaceStencil.hxx>

#include <mapDistribute.hxx>
#include <cellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCentredCellToFaceStencil::extendedCentredCellToFaceStencil
(
	const cellToFaceStencil& stencil
)
	:
	extendedCellToFaceStencil(stencil.mesh()),
	stencil_(stencil)
{
	// Calculate distribute map (also renumbers elements in stencil)
	List<Map<label>> compactMap(Pstream::nProcs());
	mapPtr_.reset
	(
		new mapDistribute
		(
			stencil.globalNumbering(),
			stencil_,
			compactMap
		)
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::extendedCentredCellToFaceStencil::compact()
{
	// Per face which elements of the stencil to keep.

	boolList isInStencil(map().constructSize(), false);

	forAll(stencil_, facei)
	{
		const labelList& stencilCells = stencil_[facei];

		forAll(stencilCells, i)
		{
			isInStencil[stencilCells[i]] = true;
		}
	}

	mapPtr_().compact(isInStencil, Pstream::msgType());
}


// ************************************************************************* //