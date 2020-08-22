#include <solidBodyMotionSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <transformField.hxx>
#include <cellZoneMesh.hxx>
#include <cellSet.hxx>
#include <boolList.hxx>
#include <syncTools.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solidBodyMotionSolver, 0);
	addToRunTimeSelectionTable
	(
		motionSolver,
		solidBodyMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionSolver::solidBodyMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	points0MotionSolver(mesh, dict, typeName),
	SBMFPtr_(solidBodyMotionFunction::New(coeffDict(), mesh.time())),
	pointIDs_(),
	moveAllCells_(false)
{
	word cellZoneName =
		coeffDict().lookupOrDefault<word>("cellZone", "none");

	word cellSetName =
		coeffDict().lookupOrDefault<word>("cellSet", "none");

	if ((cellZoneName != "none") && (cellSetName != "none"))
	{
		FatalIOErrorInFunction(coeffDict())
			<< "Either cellZone OR cellSet can be supplied, but not both. "
			<< "If neither is supplied, all cells will be included"
			<< exit(FatalIOError);
	}

	labelList cellIDs;
	if (cellZoneName != "none")
	{
		Info << "Applying solid body motion to cellZone " << cellZoneName
			<< endl;

		label zoneID = mesh.cellZones().findZoneID(cellZoneName);

		if (zoneID == -1)
		{
			FatalErrorInFunction
				<< "Unable to find cellZone " << cellZoneName
				<< ".  Valid cellZones are:"
				<< mesh.cellZones().names()
				<< exit(FatalError);
		}

		cellIDs = mesh.cellZones()[zoneID];
	}

	if (cellSetName != "none")
	{
		Info << "Applying solid body motion to cellSet " << cellSetName
			<< endl;

		cellSet set(mesh, cellSetName);

		cellIDs = set.toc();
	}

	label nCells = returnReduce(cellIDs.size(), sumOp<label>());
	moveAllCells_ = nCells == 0;

	if (moveAllCells_)
	{
		Info << "Applying solid body motion to entire mesh" << endl;
	}
	else
	{
		// collect point IDs of points in cell zone

		boolList movePts(mesh.nPoints(), false);

		forAll(cellIDs, i)
		{
			label celli = cellIDs[i];
			const cell& c = mesh.cells()[celli];
			forAll(c, j)
			{
				const face& f = mesh.faces()[c[j]];
				forAll(f, k)
				{
					label pointi = f[k];
					movePts[pointi] = true;
				}
			}
		}

		syncTools::syncPointList(mesh, movePts, orEqOp<bool>(), false);

		DynamicList<label> ptIDs(mesh.nPoints());
		forAll(movePts, i)
		{
			if (movePts[i])
			{
				ptIDs.append(i);
			}
		}

		pointIDs_.transfer(ptIDs);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionSolver::~solidBodyMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField> tnbLib::solidBodyMotionSolver::curPoints() const
{
	if (moveAllCells_)
	{
		return transformPoints(SBMFPtr_().transformation(), points0_);
	}
	else
	{
		tmp<pointField> ttransformedPts(new pointField(mesh().points()));
		pointField& transformedPts = ttransformedPts.ref();

		UIndirectList<point>(transformedPts, pointIDs_) = transformPoints
		(
			SBMFPtr_().transformation(),
			pointField(points0_, pointIDs_)
		);

		return ttransformedPts;
	}
}


// ************************************************************************* //