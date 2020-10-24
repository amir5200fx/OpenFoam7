#include <springRenumber.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <decompositionMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(springRenumber, 0);

	addToRunTimeSelectionTable
	(
		renumberMethod,
		springRenumber,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::springRenumber::springRenumber(const dictionary& renumberDict)
	:
	renumberMethod(renumberDict),
	dict_(renumberDict.optionalSubDict(typeName + "Coeffs")),
	maxCo_(readScalar(dict_.lookup("maxCo"))),
	maxIter_(readLabel(dict_.lookup("maxIter"))),
	freezeFraction_(readScalar(dict_.lookup("freezeFraction")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::springRenumber::renumber
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

	return renumber(cellCells(), points);
}


tnbLib::labelList tnbLib::springRenumber::renumber
(
	const labelListList& cellCells,
	const pointField& points
) const
{
	// Look at cell index as a 1D position parameter.
	// Move cells to the average 'position' of their neighbour.

	scalarField position(cellCells.size());
	forAll(position, celli)
	{
		position[celli] = celli;
	}

	labelList oldToNew(identity(cellCells.size()));

	scalar maxCo = maxCo_ * cellCells.size();

	for (label iter = 0; iter < maxIter_; iter++)
	{
		// Pout<< "Iteration : " << iter << nl
		//    << "------------"
		//    << endl;

		// Pout<< "Position :" << nl
		//    << "    min : " << min(position) << nl
		//    << "    max : " << max(position) << nl
		//    << "    avg : " << average(position) << nl
		//    << endl;

		// Sum force per cell.
		scalarField sumForce(cellCells.size(), 0.0);
		forAll(cellCells, oldCelli)
		{
			const labelList& cCells = cellCells[oldCelli];
			label celli = oldToNew[oldCelli];

			forAll(cCells, i)
			{
				label nbrCelli = oldToNew[cCells[i]];

				sumForce[celli] += (position[nbrCelli] - position[celli]);
			}
		}

		// Pout<< "Force :" << nl
		//    << "    min    : " << min(sumForce) << nl
		//    << "    max    : " << max(sumForce) << nl
		//    << "    avgMag : " << average(mag(sumForce)) << nl
		//    << "DeltaT : " << deltaT << nl
		//    << endl;

		// Limit displacement
		scalar deltaT = maxCo / max(mag(sumForce));

		Info << "Iter:" << iter
			<< "  maxCo:" << maxCo
			<< "  deltaT:" << deltaT
			<< "  average force:" << average(mag(sumForce)) << endl;

		// Determine displacement.
		scalarField displacement(deltaT*sumForce);

		// Pout<< "Displacement :" << nl
		//    << "    min    : " << min(displacement) << nl
		//    << "    max    : " << max(displacement) << nl
		//    << "    avgMag : " << average(mag(displacement)) << nl
		//    << endl;

		// Calculate new position and scale to be within original range
		// (0..nCells-1) for ease of postprocessing.
		position += displacement;
		position -= min(position);
		position *= (position.size() - 1) / max(position);

		// Slowly freeze.
		maxCo *= freezeFraction_;
	}

	// writeOBJ("endPosition.obj", cellCells, position);

	// Move cells to new position
	labelList shuffle;
	sortedOrder(position, shuffle);

	// Reorder oldToNew
	inplaceReorder(shuffle, oldToNew);

	return invert(oldToNew.size(), oldToNew);
}


// ************************************************************************* //