#include <rigidBodyMotion.hxx>

#include <rigidBodySolver.hxx>
#include <septernion.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::RBD::rigidBodyMotion::initialize()
{
	// Calculate the initial body-state
	forwardDynamicsCorrection(rigidBodyModelState(*this));
	X00_ = X0_;

	// Update the body-state to correspond to the current joint-state
	forwardDynamicsCorrection(motionState_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodyMotion::rigidBodyMotion()
	:
	rigidBodyModel(),
	motionState_(*this),
	motionState0_(*this),
	aRelax_(1.0),
	aDamp_(1.0),
	report_(false),
	solver_(nullptr)
{}

tnbLib::RBD::rigidBodyMotion::rigidBodyMotion
(
	const dictionary& dict
)
	:
	rigidBodyModel(dict),
	motionState_(*this, dict),
	motionState0_(motionState_),
	X00_(X0_.size()),
	aRelax_(dict.lookupOrDefault<scalar>("accelerationRelaxation", 1.0)),
	aDamp_(dict.lookupOrDefault<scalar>("accelerationDamping", 1.0)),
	report_(dict.lookupOrDefault<Switch>("report", false)),
	solver_(rigidBodySolver::New(*this, dict.subDict("solver")))
{
	if (dict.found("g"))
	{
		g() = vector(dict.lookup("g"));
	}

	initialize();
}


tnbLib::RBD::rigidBodyMotion::rigidBodyMotion
(
	const dictionary& dict,
	const dictionary& stateDict
)
	:
	rigidBodyModel(dict),
	motionState_(*this, stateDict),
	motionState0_(motionState_),
	X00_(X0_.size()),
	aRelax_(dict.lookupOrDefault<scalar>("accelerationRelaxation", 1.0)),
	aDamp_(dict.lookupOrDefault<scalar>("accelerationDamping", 1.0)),
	report_(dict.lookupOrDefault<Switch>("report", false)),
	solver_(rigidBodySolver::New(*this, dict.subDict("solver")))
{
	if (dict.found("g"))
	{
		g() = vector(dict.lookup("g"));
	}

	initialize();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodyMotion::~rigidBodyMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::spatialTransform tnbLib::RBD::rigidBodyMotion::X00
(
	const label bodyId
) const
{
	if (merged(bodyId))
	{
		const subBody& mBody = mergedBody(bodyId);
		return mBody.masterXT() & X00_[mBody.masterID()];
	}
	else
	{
		return X00_[bodyId];
	}
}


void tnbLib::RBD::rigidBodyMotion::forwardDynamics
(
	rigidBodyModelState& state,
	const scalarField& tau,
	const Field<spatialVector>& fx
) const
{
	scalarField qDdotPrev = state.qDdot();
	rigidBodyModel::forwardDynamics(state, tau, fx);
	state.qDdot() = aDamp_ * (aRelax_*state.qDdot() + (1 - aRelax_)*qDdotPrev);
}


void tnbLib::RBD::rigidBodyMotion::solve
(
	const scalar t,
	const scalar deltaT,
	const scalarField& tau,
	const Field<spatialVector>& fx
)
{
	motionState_.t() = t;
	motionState_.deltaT() = deltaT;

	if (motionState0_.deltaT() < small)
	{
		motionState0_.t() = t;
		motionState0_.deltaT() = deltaT;
	}

	if (Pstream::master())
	{
		solver_->solve(tau, fx);
	}

	Pstream::scatter(motionState_);

	// Update the body-state to correspond to the current joint-state
	forwardDynamicsCorrection(motionState_);
}


void tnbLib::RBD::rigidBodyMotion::status(const label bodyID) const
{
	const spatialTransform CofR(X0(bodyID));
	const spatialVector vCofR(v(bodyID, Zero));

	Info << "Rigid-body motion of the " << name(bodyID) << nl
		<< "    Centre of rotation: " << CofR.r() << nl
		<< "    Orientation: " << CofR.E() << nl
		<< "    Linear velocity: " << vCofR.l() << nl
		<< "    Angular velocity: " << vCofR.w()
		<< endl;
}


tnbLib::tmp<tnbLib::pointField> tnbLib::RBD::rigidBodyMotion::transformPoints
(
	const label bodyID,
	const pointField& initialPoints
) const
{
	// Calculate the transform from the initial state in the global frame
	// to the current state in the global frame
	spatialTransform X(X0(bodyID).inv() & X00(bodyID));

	tmp<pointField> tpoints(new pointField(initialPoints.size()));
	pointField& points = tpoints.ref();

	forAll(points, i)
	{
		points[i] = X.transformPoint(initialPoints[i]);
	}

	return tpoints;
}


tnbLib::tmp<tnbLib::pointField> tnbLib::RBD::rigidBodyMotion::transformPoints
(
	const label bodyID,
	const scalarField& weight,
	const pointField& initialPoints
) const
{
	// Calculate the transform from the initial state in the global frame
	// to the current state in the global frame
	spatialTransform X(X0(bodyID).inv() & X00(bodyID));

	// Calculate the septernion equivalent of the transformation for 'slerp'
	// interpolation
	septernion s(X);

	tmp<pointField> tpoints(new pointField(initialPoints));
	pointField& points = tpoints.ref();

	forAll(points, i)
	{
		// Move non-stationary points
		if (weight[i] > small)
		{
			// Use solid-body motion where weight = 1
			if (weight[i] > 1 - small)
			{
				points[i] = X.transformPoint(initialPoints[i]);
			}
			// Slerp septernion interpolation
			else
			{
				points[i] =
					slerp(septernion::I, s, weight[i])
					.transformPoint(initialPoints[i]);
			}
		}
	}

	return tpoints;
}


tnbLib::tmp<tnbLib::pointField> tnbLib::RBD::rigidBodyMotion::transformPoints
(
	const labelList& bodyIDs,
	const List<const scalarField*>& weights,
	const pointField& initialPoints
) const
{
	List<septernion> ss(bodyIDs.size() + 1);
	ss[bodyIDs.size()] = septernion::I;

	forAll(bodyIDs, bi)
	{
		const label bodyID = bodyIDs[bi];

		// Calculate the transform from the initial state in the global frame
		// to the current state in the global frame
		spatialTransform X(X0(bodyID).inv() & X00(bodyID));

		// Calculate the septernion equivalent of the transformation
		ss[bi] = septernion(X);
	}

	tmp<pointField> tpoints(new pointField(initialPoints));
	pointField& points = tpoints.ref();

	List<scalar> w(ss.size());

	forAll(points, i)
	{
		// Initialize to 1 for the far-field weight
		scalar sum1mw = 1;

		forAll(bodyIDs, bi)
		{
			w[bi] = (*(weights[bi]))[i];
			sum1mw += w[bi] / (1 + small - w[bi]);
		}

		// Calculate the limiter for wi/(1 - wi) to ensure the sum(wi) = 1
		scalar lambda = 1 / sum1mw;

		// Limit wi/(1 - wi) and sum the resulting wi
		scalar sumw = 0;
		forAll(bodyIDs, bi)
		{
			w[bi] = lambda * w[bi] / (1 + small - w[bi]);
			sumw += w[bi];
		}

		// Calculate the weight for the stationary far-field
		w[bodyIDs.size()] = 1 - sumw;

		points[i] = average(ss, w).transformPoint(initialPoints[i]);
	}

	return tpoints;
}


// ************************************************************************* //