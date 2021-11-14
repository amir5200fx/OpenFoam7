#include <sixDoFRigidBodyMotion.hxx>

#include <sixDoFSolver.hxx>
#include <septernion.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotion::applyRestraints()
{
	if (restraints_.empty())
	{
		return;
	}

	if (Pstream::master())
	{
		forAll(restraints_, rI)
		{
			if (report_)
			{
				Info << "Restraint " << restraints_[rI].name() << ": ";
			}

			// Restraint position
			point rP = Zero;

			// Restraint force
			vector rF = Zero;

			// Restraint moment
			vector rM = Zero;

			// Accumulate the restraints
			restraints_[rI].restrain(*this, rP, rF, rM);

			// Update the acceleration
			a() += rF / mass_;

			// Moments are returned in global axes, transforming to
			// body local to add to torque.
			tau() += Q().T() & (rM + ((rP - centreOfRotation()) ^ rF));
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotion::sixDoFRigidBodyMotion()
	:
	motionState_(),
	motionState0_(),
	restraints_(),
	constraints_(),
	tConstraints_(tensor::I),
	rConstraints_(tensor::I),
	initialCentreOfMass_(Zero),
	initialCentreOfRotation_(Zero),
	initialQ_(I),
	mass_(vSmall),
	momentOfInertia_(diagTensor::one*vSmall),
	aRelax_(1.0),
	aDamp_(1.0),
	report_(false),
	solver_(nullptr)
{}


tnbLib::sixDoFRigidBodyMotion::sixDoFRigidBodyMotion
(
	const dictionary& dict,
	const dictionary& stateDict
)
	:
	motionState_(stateDict),
	motionState0_(),
	restraints_(),
	constraints_(),
	tConstraints_(tensor::I),
	rConstraints_(tensor::I),
	initialCentreOfMass_
	(
		dict.lookupOrDefault
		(
			"initialCentreOfMass",
			vector(dict.lookup("centreOfMass"))
		)
	),
	initialCentreOfRotation_(initialCentreOfMass_),
	initialQ_
	(
		dict.lookupOrDefault
		(
			"initialOrientation",
			dict.lookupOrDefault("orientation", tensor::I)
		)
	),
	mass_(readScalar(dict.lookup("mass"))),
	momentOfInertia_(dict.lookup("momentOfInertia")),
	aRelax_(dict.lookupOrDefault<scalar>("accelerationRelaxation", 1.0)),
	aDamp_(dict.lookupOrDefault<scalar>("accelerationDamping", 1.0)),
	report_(dict.lookupOrDefault<Switch>("report", false)),
	solver_(sixDoFSolver::New(dict.subDict("solver"), *this))
{
	addRestraints(dict);

	// Set constraints and initial centre of rotation
	// if different to the centre of mass
	addConstraints(dict);

	// If the centres of mass and rotation are different ...
	vector R(initialCentreOfMass_ - initialCentreOfRotation_);
	if (magSqr(R) > vSmall)
	{
		// ... correct the moment of inertia tensor using parallel axes theorem
		momentOfInertia_ += mass_ * diag(I*magSqr(R) - sqr(R));

		// ... and if the centre of rotation is not specified for motion state
		// update it
		if (!stateDict.found("centreOfRotation"))
		{
			motionState_.centreOfRotation() = initialCentreOfRotation_;
		}
	}

	// Save the old-time motion state
	motionState0_ = motionState_;
}


tnbLib::sixDoFRigidBodyMotion::sixDoFRigidBodyMotion
(
	const sixDoFRigidBodyMotion& sDoFRBM
)
	:
	motionState_(sDoFRBM.motionState_),
	motionState0_(sDoFRBM.motionState0_),
	restraints_(sDoFRBM.restraints_),
	constraints_(sDoFRBM.constraints_),
	tConstraints_(sDoFRBM.tConstraints_),
	rConstraints_(sDoFRBM.rConstraints_),
	initialCentreOfMass_(sDoFRBM.initialCentreOfMass_),
	initialCentreOfRotation_(sDoFRBM.initialCentreOfRotation_),
	initialQ_(sDoFRBM.initialQ_),
	mass_(sDoFRBM.mass_),
	momentOfInertia_(sDoFRBM.momentOfInertia_),
	aRelax_(sDoFRBM.aRelax_),
	aDamp_(sDoFRBM.aDamp_),
	report_(sDoFRBM.report_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotion::~sixDoFRigidBodyMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotion::addRestraints
(
	const dictionary& dict
)
{
	if (dict.found("restraints"))
	{
		const dictionary& restraintDict = dict.subDict("restraints");

		label i = 0;

		restraints_.setSize(restraintDict.size());

		forAllConstIter(IDLList<entry>, restraintDict, iter)
		{
			if (iter().isDict())
			{
				restraints_.set
				(
					i++,
					sixDoFRigidBodyMotionRestraint::New
					(
						iter().keyword(),
						iter().dict()
					)
				);
			}
		}

		restraints_.setSize(i);
	}
}


void tnbLib::sixDoFRigidBodyMotion::addConstraints
(
	const dictionary& dict
)
{
	if (dict.found("constraints"))
	{
		const dictionary& constraintDict = dict.subDict("constraints");

		label i = 0;

		constraints_.setSize(constraintDict.size());

		pointConstraint pct;
		pointConstraint pcr;

		forAllConstIter(IDLList<entry>, constraintDict, iter)
		{
			if (iter().isDict())
			{
				constraints_.set
				(
					i,
					sixDoFRigidBodyMotionConstraint::New
					(
						iter().keyword(),
						iter().dict(),
						*this
					)
				);

				constraints_[i].setCentreOfRotation(initialCentreOfRotation_);
				constraints_[i].constrainTranslation(pct);
				constraints_[i].constrainRotation(pcr);

				i++;
			}
		}

		constraints_.setSize(i);

		tConstraints_ = pct.constraintTransformation();
		rConstraints_ = pcr.constraintTransformation();

		Info << "Translational constraint tensor " << tConstraints_ << nl
			<< "Rotational constraint tensor " << rConstraints_ << endl;
	}
}


void tnbLib::sixDoFRigidBodyMotion::updateAcceleration
(
	const vector& fGlobal,
	const vector& tauGlobal
)
{
	static bool first = true;

	// Save the previous iteration accelerations for relaxation
	vector aPrevIter = a();
	vector tauPrevIter = tau();

	// Calculate new accelerations
	a() = fGlobal / mass_;
	tau() = (Q().T() & tauGlobal);
	applyRestraints();

	// Relax accelerations on all but first iteration
	if (!first)
	{
		a() = aRelax_ * a() + (1 - aRelax_)*aPrevIter;
		tau() = aRelax_ * tau() + (1 - aRelax_)*tauPrevIter;
	}
	else
	{
		first = false;
	}
}


void tnbLib::sixDoFRigidBodyMotion::update
(
	bool firstIter,
	const vector& fGlobal,
	const vector& tauGlobal,
	scalar deltaT,
	scalar deltaT0
)
{
	if (Pstream::master())
	{
		solver_->solve(firstIter, fGlobal, tauGlobal, deltaT, deltaT0);

		if (report_)
		{
			status();
		}
	}

	Pstream::scatter(motionState_);
}


void tnbLib::sixDoFRigidBodyMotion::status() const
{
	Info << "6-DoF rigid body motion" << nl
		<< "    Centre of rotation: " << centreOfRotation() << nl
		<< "    Centre of mass: " << centreOfMass() << nl
		<< "    Orientation: " << orientation() << nl
		<< "    Linear velocity: " << v() << nl
		<< "    Angular velocity: " << omega()
		<< endl;
}


tnbLib::tmp<tnbLib::pointField> tnbLib::sixDoFRigidBodyMotion::transform
(
	const pointField& initialPoints
) const
{
	return
		(
			centreOfRotation()
			+ (Q() & initialQ_.T() & (initialPoints - initialCentreOfRotation_))
			);
}


tnbLib::tmp<tnbLib::pointField> tnbLib::sixDoFRigidBodyMotion::transform
(
	const pointField& initialPoints,
	const scalarField& scale
) const
{
	// Calculate the transformation septerion from the initial state
	septernion s
	(
		centreOfRotation() - initialCentreOfRotation(),
		quaternion(Q().T() & initialQ())
	);

	tmp<pointField> tpoints(new pointField(initialPoints));
	pointField& points = tpoints.ref();

	forAll(points, pointi)
	{
		// Move non-stationary points
		if (scale[pointi] > small)
		{
			// Use solid-body motion where scale = 1
			if (scale[pointi] > 1 - small)
			{
				points[pointi] = transform(initialPoints[pointi]);
			}
			// Slerp septernion interpolation
			else
			{
				septernion ss(slerp(septernion::I, s, scale[pointi]));

				points[pointi] =
					initialCentreOfRotation()
					+ ss.invTransformPoint
					(
						initialPoints[pointi]
						- initialCentreOfRotation()
					);
			}
		}
	}

	return tpoints;
}


// ************************************************************************* //