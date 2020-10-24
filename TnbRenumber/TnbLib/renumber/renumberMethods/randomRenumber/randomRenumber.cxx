#include <randomRenumber.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(randomRenumber, 0);

	addToRunTimeSelectionTable
	(
		renumberMethod,
		randomRenumber,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::randomRenumber::randomRenumber(const dictionary& renumberDict)
	:
	renumberMethod(renumberDict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::randomRenumber::renumber
(
	const pointField& points
) const
{
	Random rndGen(0);

	labelList newToOld(identity(points.size()));

	for (label iter = 0; iter < 10; iter++)
	{
		forAll(newToOld, i)
		{
			label j = rndGen.sampleAB<label>(0, newToOld.size());
			Swap(newToOld[i], newToOld[j]);
		}
	}
	return newToOld;
}


tnbLib::labelList tnbLib::randomRenumber::renumber
(
	const polyMesh& mesh,
	const pointField& points
) const
{
	return renumber(points);
}


tnbLib::labelList tnbLib::randomRenumber::renumber
(
	const labelListList& cellCells,
	const pointField& points
) const
{
	return renumber(points);
}


// ************************************************************************* //