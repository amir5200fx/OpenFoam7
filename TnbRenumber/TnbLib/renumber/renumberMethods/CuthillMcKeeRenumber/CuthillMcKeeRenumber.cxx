#include <CuthillMcKeeRenumber.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <bandCompression.hxx>
#include <decompositionMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(CuthillMcKeeRenumber, 0);

	addToRunTimeSelectionTable
	(
		renumberMethod,
		CuthillMcKeeRenumber,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CuthillMcKeeRenumber::CuthillMcKeeRenumber(const dictionary& renumberDict)
	:
	renumberMethod(renumberDict),
	reverse_
	(
		renumberDict.optionalSubDict
		(
			typeName + "Coeffs"
		).lookupOrDefault<Switch>("reverse", false)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::CuthillMcKeeRenumber::renumber
(
	const polyMesh& mesh,
	const pointField& points
) const
{
	CompactListList<label> cellCells;
	decompositionMethod::calcCellCells
	(
		mesh,
		identity(mesh.nCells()),
		mesh.nCells(),
		false,                      // local only
		cellCells
	);

	labelList orderedToOld = bandCompression(cellCells());

	if (reverse_)
	{
		reverse(orderedToOld);
	}

	return orderedToOld;
}


tnbLib::labelList tnbLib::CuthillMcKeeRenumber::renumber
(
	const labelList& cellCells,
	const labelList& offsets,
	const pointField& cc
) const
{
	labelList orderedToOld = bandCompression(cellCells, offsets);

	if (reverse_)
	{
		reverse(orderedToOld);
	}

	return orderedToOld;
}


tnbLib::labelList tnbLib::CuthillMcKeeRenumber::renumber
(
	const labelListList& cellCells,
	const pointField& points
) const
{
	labelList orderedToOld = bandCompression(cellCells);

	if (reverse_)
	{
		reverse(orderedToOld);
	}

	return orderedToOld;
}


// ************************************************************************* //