#include <extendedCentredCellToCellStencil.hxx>

#include <mapDistribute.hxx>
#include <cellToCellStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCentredCellToCellStencil::extendedCentredCellToCellStencil
(
	const cellToCellStencil& stencil
)
	:
	extendedCellToCellStencil(stencil.mesh()),
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

void tnbLib::extendedCentredCellToCellStencil::compact()
{
	boolList isInStencil(map().constructSize(), false);

	forAll(stencil_, celli)
	{
		const labelList& stencilCells = stencil_[celli];

		forAll(stencilCells, i)
		{
			isInStencil[stencilCells[i]] = true;
		}
	}

	mapPtr_().compact(isInStencil, Pstream::msgType());
}


// ************************************************************************* //