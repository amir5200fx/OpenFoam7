#include <renumberMethod.hxx>

#include <decompositionMethod.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(renumberMethod, 0);
	defineRunTimeSelectionTable(renumberMethod, dictionary);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::renumberMethod> tnbLib::renumberMethod::New
(
	const dictionary& renumberDict
)
{
	const word methodType(renumberDict.lookup("method"));

	// Info<< "Selecting renumberMethod " << methodType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(methodType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown renumberMethod "
			<< methodType << nl << nl
			<< "Valid renumberMethods are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<renumberMethod>(cstrIter()(renumberDict));
}


tnbLib::labelList tnbLib::renumberMethod::renumber
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

	// Renumber based on agglomerated points
	return renumber(cellCells(), points);
}


tnbLib::labelList tnbLib::renumberMethod::renumber
(
	const labelList& cellCells,
	const labelList& offsets,
	const pointField& cc
) const
{
	NotImplemented;
	return labelList();
}


tnbLib::labelList tnbLib::renumberMethod::renumber
(
	const polyMesh& mesh,
	const labelList& fineToCoarse,
	const pointField& coarsePoints
) const
{
	CompactListList<label> coarseCellCells;
	decompositionMethod::calcCellCells
	(
		mesh,
		fineToCoarse,
		coarsePoints.size(),
		false,                      // local only
		coarseCellCells
	);

	// Renumber based on agglomerated points
	labelList coarseDistribution
	(
		renumber
		(
			coarseCellCells(),
			coarsePoints
		)
	);

	// Rework back into renumbering for original mesh_
	labelList fineDistribution(fineToCoarse.size());

	forAll(fineDistribution, i)
	{
		fineDistribution[i] = coarseDistribution[fineToCoarse[i]];
	}

	return fineDistribution;
}


// ************************************************************************* //