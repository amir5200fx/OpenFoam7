#include <extendedCentredFaceToCellStencil.hxx>

#include <mapDistribute.hxx>
#include <faceToCellStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCentredFaceToCellStencil::extendedCentredFaceToCellStencil
(
	const faceToCellStencil& stencil
)
	:
	extendedFaceToCellStencil(stencil.mesh()),
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

void tnbLib::extendedCentredFaceToCellStencil::compact()
{
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