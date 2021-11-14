#include <sixDoFRigidBodyMotionSolver.hxx>

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
	defineTypeNameAndDebug(sixDoFRigidBodyMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		sixDoFRigidBodyMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionSolver::sixDoFRigidBodyMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	displacementMotionSolver(mesh, dict, typeName),
	motion_
	(
		coeffDict(),
		IOobject
		(
			"sixDoFRigidBodyMotionState",
			mesh.time().timeName(),
			"uniform",
			mesh
		).typeHeaderOk<IOdictionary>(true)
		? IOdictionary
		(
			IOobject
			(
				"sixDoFRigidBodyMotionState",
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
	patches_(wordReList(coeffDict().lookup("patches"))),
	patchSet_(mesh.boundaryMesh().patchSet(patches_)),
	di_(readScalar(coeffDict().lookup("innerDistance"))),
	do_(readScalar(coeffDict().lookup("outerDistance"))),
	test_(coeffDict().lookupOrDefault<Switch>("test", false)),
	rhoInf_(1.0),
	rhoName_(coeffDict().lookupOrDefault<word>("rho", "rho")),
	scale_
	(
		IOobject
		(
			"motionScale",
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		pointMesh::New(mesh),
		dimensionedScalar(dimless, 0)
	),
	curTimeIndex_(-1)
{
	if (rhoName_ == "rhoInf")
	{
		rhoInf_ = readScalar(coeffDict().lookup("rhoInf"));
	}

	// Calculate scaling factor everywhere
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	{
		const pointMesh& pMesh = pointMesh::New(mesh);

		pointPatchDist pDist(pMesh, patchSet_, points0());

		// Scaling: 1 up to di then linear down to 0 at do away from patches
		scale_.primitiveFieldRef() =
			min
			(
				max
				(
				(do_ - pDist.primitiveField()) / (do_ - di_),
					scalar(0)
				),
				scalar(1)
			);

		// Convert the scale function to a cosine
		scale_.primitiveFieldRef() =
			min
			(
				max
				(
					0.5
					- 0.5
					*cos(scale_.primitiveField()
						*tnbLib::constant::mathematical::pi),
					scalar(0)
				),
				scalar(1)
			);

		pointConstraints::New(pMesh).constrain(scale_);
		scale_.write();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionSolver::~sixDoFRigidBodyMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::sixDoFRigidBodyMotion&
tnbLib::sixDoFRigidBodyMotionSolver::motion() const
{
	return motion_;
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::sixDoFRigidBodyMotionSolver::curPoints() const
{
	return points0() + pointDisplacement_.primitiveField();
}


void tnbLib::sixDoFRigidBodyMotionSolver::solve()
{
	const Time& t = mesh().time();

	if (mesh().nPoints() != points0().size())
	{
		FatalErrorInFunction
			<< "The number of points in the mesh seems to have changed." << endl
			<< "In constant/polyMesh there are " << points0().size()
			<< " points; in the current mesh there are " << mesh().nPoints()
			<< " points." << exit(FatalError);
	}

	// Store the motion state at the beginning of the time-stepbool
	bool firstIter = false;
	if (curTimeIndex_ != t.timeIndex())
	{
		motion_.newTime();
		curTimeIndex_ = t.timeIndex();
		firstIter = true;
	}

	dimensionedVector g("g", dimAcceleration, Zero);

	if (mesh().foundObject<uniformDimensionedVectorField>("g"))
	{
		g = mesh().lookupObject<uniformDimensionedVectorField>("g");
	}
	else if (coeffDict().found("g"))
	{
		coeffDict().lookup("g") >> g;
	}

	// scalar ramp = min(max((t.value() - 5)/10, 0), 1);
	scalar ramp = 1.0;

	if (test_)
	{
		motion_.update
		(
			firstIter,
			ramp*(motion_.mass()*g.value()),
			ramp*(motion_.mass()*(motion_.momentArm() ^ g.value())),
			t.deltaTValue(),
			t.deltaT0Value()
		);
	}
	else
	{
		dictionary forcesDict;

		forcesDict.add("type", functionObjects::forces::typeName);
		forcesDict.add("patches", patches_);
		forcesDict.add("rhoInf", rhoInf_);
		forcesDict.add("rho", rhoName_);
		forcesDict.add("CofR", motion_.centreOfRotation());

		functionObjects::forces f("forces", t, forcesDict);

		f.calcForcesMoment();

		motion_.update
		(
			firstIter,
			ramp*(f.forceEff() + motion_.mass()*g.value()),
			ramp
			*(
				f.momentEff()
				+ motion_.mass()*(motion_.momentArm() ^ g.value())
				),
			t.deltaTValue(),
			t.deltaT0Value()
		);
	}

	// Update the displacements
	pointDisplacement_.primitiveFieldRef() =
		motion_.transform(points0(), scale_) - points0();

	// Displacement has changed. Update boundary conditions
	pointConstraints::New
	(
		pointDisplacement_.mesh()
	).constrainDisplacement(pointDisplacement_);
}


bool tnbLib::sixDoFRigidBodyMotionSolver::write() const
{
	IOdictionary dict
	(
		IOobject
		(
			"sixDoFRigidBodyMotionState",
			mesh().time().timeName(),
			"uniform",
			mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	motion_.state().write(dict);

	return
		dict.regIOobject::writeObject
		(
			IOstream::ASCII,
			IOstream::currentVersion,
			mesh().time().writeCompression(),
			true
		)
		&& displacementMotionSolver::write();
}


// ************************************************************************* //