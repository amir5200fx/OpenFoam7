#include <dummyAgglomeration.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dummyAgglomeration, 0);

	addToRunTimeSelectionTable
	(
		GAMGAgglomeration,
		dummyAgglomeration,
		lduMesh
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dummyAgglomeration::dummyAgglomeration
(
	const lduMesh& mesh,
	const dictionary& controlDict
)
	:
	GAMGAgglomeration(mesh, controlDict),
	nLevels_(readLabel(controlDict.lookup("nLevels")))
{
	const label nCoarseCells = mesh.lduAddr().size();

	for
		(
			label nCreatedLevels = 0;
			nCreatedLevels < nLevels_;
			nCreatedLevels++
			)
	{
		nCells_[nCreatedLevels] = nCoarseCells;
		restrictAddressing_.set
		(
			nCreatedLevels,
			new labelField(identity(nCoarseCells))
		);

		agglomerateLduAddressing(nCreatedLevels);
	}

	// Shrink the storage of the levels to those created
	compactLevels(nLevels_);
}


// ************************************************************************* //