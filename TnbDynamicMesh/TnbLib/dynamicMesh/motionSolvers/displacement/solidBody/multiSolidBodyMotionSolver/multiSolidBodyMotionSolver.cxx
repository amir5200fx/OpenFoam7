#include <multiSolidBodyMotionSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <transformField.hxx>
#include <cellZoneMesh.hxx>
#include <boolList.hxx>
#include <syncTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(multiSolidBodyMotionSolver, 0);
	addToRunTimeSelectionTable
	(
		motionSolver,
		multiSolidBodyMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::multiSolidBodyMotionSolver::multiSolidBodyMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	points0MotionSolver(mesh, dict, typeName)
{
	zoneIDs_.setSize(coeffDict().size());
	SBMFs_.setSize(coeffDict().size());
	pointIDs_.setSize(coeffDict().size());
	label zonei = 0;

	forAllConstIter(dictionary, coeffDict(), iter)
	{
		if (iter().isDict())
		{
			zoneIDs_[zonei] = mesh.cellZones().findZoneID(iter().keyword());

			if (zoneIDs_[zonei] == -1)
			{
				FatalIOErrorInFunction
				(
					coeffDict()
				) << "Cannot find cellZone named " << iter().keyword()
					<< ". Valid zones are " << mesh.cellZones().names()
					<< exit(FatalIOError);
			}

			const dictionary& subDict = iter().dict();

			SBMFs_.set
			(
				zonei,
				solidBodyMotionFunction::New(subDict, mesh.time())
			);

			// Collect points of cell zone.
			const cellZone& cz = mesh.cellZones()[zoneIDs_[zonei]];

			boolList movePts(mesh.nPoints(), false);

			forAll(cz, i)
			{
				label celli = cz[i];
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

			pointIDs_[zonei].transfer(ptIDs);

			Info << "Applying solid body motion " << SBMFs_[zonei].type()
				<< " to " << pointIDs_[zonei].size() << " points of cellZone "
				<< iter().keyword() << endl;

			zonei++;
		}
	}
	zoneIDs_.setSize(zonei);
	SBMFs_.setSize(zonei);
	pointIDs_.setSize(zonei);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::multiSolidBodyMotionSolver::~multiSolidBodyMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField> tnbLib::multiSolidBodyMotionSolver::curPoints() const
{
	tmp<pointField> ttransformedPts(new pointField(mesh().points()));
	pointField& transformedPts = ttransformedPts.ref();

	forAll(zoneIDs_, i)
	{
		const labelList& zonePoints = pointIDs_[i];

		UIndirectList<point>(transformedPts, zonePoints) = transformPoints
		(
			SBMFs_[i].transformation(),
			pointField(points0_, zonePoints)
		);
	}

	return ttransformedPts;
}


// ************************************************************************* //