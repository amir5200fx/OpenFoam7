#include <rigidBodyMeshMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <polyMesh.hxx>
#include <pointPatchDist.hxx>
#include <pointConstraints.hxx>
#include <uniformDimensionedFields.hxx>
#include <forces.hxx>
#include <OneConstant.hxx>
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(rigidBodyMeshMotion, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		rigidBodyMeshMotion,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rigidBodyMeshMotion::bodyMesh::bodyMesh
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
	patchSet_(mesh.boundaryMesh().patchSet(patches_)),
	di_(readScalar(dict.lookup("innerDistance"))),
	do_(readScalar(dict.lookup("outerDistance"))),
	weight_
	(
		IOobject
		(
			name_ + ".motionScale",
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		pointMesh::New(mesh),
		dimensionedScalar(dimless, 0)
	)
{}


tnbLib::rigidBodyMeshMotion::rigidBodyMeshMotion
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	displacementMotionSolver(mesh, dict, typeName),
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
	ramp_(nullptr),
	curTimeIndex_(-1)
{
	if (rhoName_ == "rhoInf")
	{
		rhoInf_ = readScalar(coeffDict().lookup("rhoInf"));
	}

	if (coeffDict().found("ramp"))
	{
		ramp_ = Function1<scalar>::New("ramp", coeffDict());
	}
	else
	{
		ramp_ = new Function1Types::OneConstant<scalar>("ramp");
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

	// Calculate scaling factor everywhere for each meshed body
	forAll(bodyMeshes_, bi)
	{
		const pointMesh& pMesh = pointMesh::New(mesh);

		pointPatchDist pDist(pMesh, bodyMeshes_[bi].patchSet_, points0());

		pointScalarField& scale = bodyMeshes_[bi].weight_;

		// Scaling: 1 up to di then linear down to 0 at do away from patches
		scale.primitiveFieldRef() =
			min
			(
				max
				(
				(bodyMeshes_[bi].do_ - pDist.primitiveField())
					/ (bodyMeshes_[bi].do_ - bodyMeshes_[bi].di_),
					scalar(0)
				),
				scalar(1)
			);

		// Convert the scale function to a cosine
		scale.primitiveFieldRef() =
			min
			(
				max
				(
					0.5
					- 0.5
					*cos(scale.primitiveField()
						*tnbLib::constant::mathematical::pi),
					scalar(0)
				),
				scalar(1)
			);

		pointConstraints::New(pMesh).constrain(scale);
		// scale.write();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::rigidBodyMeshMotion::~rigidBodyMeshMotion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::rigidBodyMeshMotion::curPoints() const
{
	return points0() + pointDisplacement_.primitiveField();
}


void tnbLib::rigidBodyMeshMotion::solve()
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

	// Store the motion state at the beginning of the time-step
	if (curTimeIndex_ != t.timeIndex())
	{
		newTime();
		curTimeIndex_ = t.timeIndex();
	}

	const scalar ramp = ramp_->value(t.value());

	if (mesh().foundObject<uniformDimensionedVectorField>("g"))
	{
		g() =
			ramp
			* mesh().lookupObject<uniformDimensionedVectorField>("g").value();
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

			fx[bodyID] = ramp * spatialVector(f.momentEff(), f.forceEff());
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
	if (bodyMeshes_.size() == 1)
	{
		pointDisplacement_.primitiveFieldRef() = transformPoints
		(
			bodyMeshes_[0].bodyID_,
			bodyMeshes_[0].weight_,
			points0()
		) - points0();
	}
	else
	{
		labelList bodyIDs(bodyMeshes_.size());
		List<const scalarField*> weights(bodyMeshes_.size());
		forAll(bodyIDs, bi)
		{
			bodyIDs[bi] = bodyMeshes_[bi].bodyID_;
			weights[bi] = &bodyMeshes_[bi].weight_;
		}

		pointDisplacement_.primitiveFieldRef() =
			transformPoints(bodyIDs, weights, points0()) - points0();
	}

	// Displacement has changed. Update boundary conditions
	pointConstraints::New
	(
		pointDisplacement_.mesh()
	).constrainDisplacement(pointDisplacement_);
}


bool tnbLib::rigidBodyMeshMotion::write() const
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
		&& displacementMotionSolver::write();
}


// ************************************************************************* //