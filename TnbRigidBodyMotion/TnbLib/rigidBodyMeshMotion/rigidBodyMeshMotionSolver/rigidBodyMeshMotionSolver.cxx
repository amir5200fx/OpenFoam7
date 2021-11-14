#include <rigidBodyMeshMotionSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <polyMesh.hxx>
#include <pointPatchDist.hxx>
#include <pointConstraints.hxx>
#include <uniformDimensionedFields.hxx>
#include <forces.hxx>
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(rigidBodyMeshMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		rigidBodyMeshMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rigidBodyMeshMotionSolver::bodyMesh::bodyMesh
(
	const polyMesh& mesh,
	const word& name,
	const label bodyID,
	const dictionary& dict
)
	:
	name_(name),
	bodyID_(bodyID),
	patches_(wordReList(dict.lookup("patches"))),
	patchSet_(mesh.boundaryMesh().patchSet(patches_))
{}


tnbLib::rigidBodyMeshMotionSolver::rigidBodyMeshMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	motionSolver(mesh, dict, typeName),
	RBD::rigidBodyMotion
	(
		coeffDict(),
		IOobject
		(
			"rigidBodyMotionState",
			mesh.time().timeName(),
			"uniform",
			mesh
		).typeHeaderOk<IOdictionary>(true)
		? IOdictionary
		(
			IOobject
			(
				"rigidBodyMotionState",
				mesh.time().timeName(),
				"uniform",
				mesh,
				IOobject::READ_IF_PRESENT,
				IOobject::NO_WRITE,
				false
			)
		)
		: coeffDict()
	),
	test_(coeffDict().lookupOrDefault<Switch>("test", false)),
	rhoInf_(1.0),
	rhoName_(coeffDict().lookupOrDefault<word>("rho", "rho")),
	curTimeIndex_(-1),
	meshSolverPtr_
	(
		motionSolver::New
		(
			mesh,
			IOdictionary
			(
				IOobject
				(
					"rigidBodyMotionSolver:meshSolver",
					mesh.time().constant(),
					mesh
				),
				coeffDict().subDict("meshSolver")
			)
		)
	),
	meshSolver_(refCast<displacementMotionSolver>(meshSolverPtr_()))
{
	if (rhoName_ == "rhoInf")
	{
		rhoInf_ = readScalar(coeffDict().lookup("rhoInf"));
	}

	const dictionary& bodiesDict = coeffDict().subDict("bodies");

	forAllConstIter(IDLList<entry>, bodiesDict, iter)
	{
		const dictionary& bodyDict = iter().dict();

		if (bodyDict.found("patches"))
		{
			const label bodyID = this->bodyID(iter().keyword());

			if (bodyID == -1)
			{
				FatalErrorInFunction
					<< "Body " << iter().keyword()
					<< " has been merged with another body"
					" and cannot be assigned a set of patches"
					<< exit(FatalError);
			}

			bodyMeshes_.append
			(
				new bodyMesh
				(
					mesh,
					iter().keyword(),
					bodyID,
					bodyDict
				)
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::rigidBodyMeshMotionSolver::~rigidBodyMeshMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::rigidBodyMeshMotionSolver::curPoints() const
{
	return meshSolverPtr_->curPoints();
}


void tnbLib::rigidBodyMeshMotionSolver::solve()
{
	const Time& t = mesh().time();

	if (mesh().nPoints() != meshSolver_.points0().size())
	{
		FatalErrorInFunction
			<< "The number of points in the mesh seems to have changed." << endl
			<< "In constant/polyMesh there are " << meshSolver_.points0().size()
			<< " points; in the current mesh there are " << mesh().nPoints()
			<< " points." << exit(FatalError);
	}

	// Store the motion state at the beginning of the time-step
	if (curTimeIndex_ != t.timeIndex())
	{
		newTime();
		curTimeIndex_ = t.timeIndex();
	}

	if (mesh().foundObject<uniformDimensionedVectorField>("g"))
	{
		g() =
			mesh().lookupObject<uniformDimensionedVectorField>("g").value();
	}

	if (test_)
	{
		label nIter(readLabel(coeffDict().lookup("nIter")));

		for (label i = 0; i < nIter; i++)
		{
			RBD::rigidBodyMotion::solve
			(
				t.value(),
				t.deltaTValue(),
				scalarField(nDoF(), Zero),
				Field<spatialVector>(nBodies(), Zero)
			);
		}
	}
	else
	{
		Field<spatialVector> fx(nBodies(), Zero);

		forAll(bodyMeshes_, bi)
		{
			const label bodyID = bodyMeshes_[bi].bodyID_;

			dictionary forcesDict;
			forcesDict.add("type", functionObjects::forces::typeName);
			forcesDict.add("patches", bodyMeshes_[bi].patches_);
			forcesDict.add("rhoInf", rhoInf_);
			forcesDict.add("rho", rhoName_);
			forcesDict.add("CofR", vector::zero);

			functionObjects::forces f("forces", t, forcesDict);
			f.calcForcesMoment();

			fx[bodyID] = spatialVector(f.momentEff(), f.forceEff());
		}

		RBD::rigidBodyMotion::solve
		(
			t.value(),
			t.deltaTValue(),
			scalarField(nDoF(), Zero),
			fx
		);
	}

	if (Pstream::master() && report())
	{
		forAll(bodyMeshes_, bi)
		{
			status(bodyMeshes_[bi].bodyID_);
		}
	}

	// Update the displacements
	forAll(bodyMeshes_, bi)
	{
		forAllConstIter(labelHashSet, bodyMeshes_[bi].patchSet_, iter)
		{
			label patchi = iter.key();

			pointField patchPoints0
			(
				meshSolver_.pointDisplacement().boundaryField()[patchi]
				.patchInternalField(meshSolver_.points0())
			);

			meshSolver_.pointDisplacement().boundaryFieldRef()[patchi] ==
				(
					transformPoints
					(
						bodyMeshes_[bi].bodyID_,
						patchPoints0
					) - patchPoints0
					)();
		}
	}

	meshSolverPtr_->solve();
}


void tnbLib::rigidBodyMeshMotionSolver::movePoints(const pointField& points)
{
	meshSolverPtr_->movePoints(points);
}


void tnbLib::rigidBodyMeshMotionSolver::updateMesh(const mapPolyMesh& mpm)
{
	meshSolverPtr_->updateMesh(mpm);
}


bool tnbLib::rigidBodyMeshMotionSolver::write() const
{
	IOdictionary dict
	(
		IOobject
		(
			"rigidBodyMotionState",
			mesh().time().timeName(),
			"uniform",
			mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	state().write(dict);

	return
		dict.regIOobject::writeObject
		(
			IOstream::ASCII,
			IOstream::currentVersion,
			mesh().time().writeCompression(),
			true
		)
		&& motionSolver::write();
}


// ************************************************************************* //