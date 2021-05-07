#include <linearAxialAngularSpring.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace restraints
		{
			defineTypeNameAndDebug(linearAxialAngularSpring, 0);

			addToRunTimeSelectionTable
			(
				restraint,
				linearAxialAngularSpring,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::restraints::linearAxialAngularSpring::linearAxialAngularSpring
(
	const word& name,
	const dictionary& dict,
	const rigidBodyModel& model
)
	:
	restraint(name, dict, model)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::restraints::linearAxialAngularSpring::~linearAxialAngularSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::restraints::linearAxialAngularSpring::restrain
(
	scalarField& tau,
	Field<spatialVector>& fx
) const
{
	vector refDir = rotationTensor(vector(1, 0, 0), axis_) & vector(0, 1, 0);

	vector oldDir = refQ_ & refDir;
	vector newDir = model_.X0(bodyID_).E() & refDir;

	if (mag(oldDir & axis_) > 0.95 || mag(newDir & axis_) > 0.95)
	{
		// Directions close to the axis, changing reference
		refDir = rotationTensor(vector(1, 0, 0), axis_) & vector(0, 0, 1);
		oldDir = refQ_ & refDir;
		newDir = model_.X0(bodyID_).E() & refDir;
	}

	// Removing axis component from oldDir and newDir and normalising
	oldDir -= (axis_ & oldDir)*axis_;
	oldDir /= (mag(oldDir) + vSmall);

	newDir -= (axis_ & newDir)*axis_;
	newDir /= (mag(newDir) + vSmall);

	scalar theta = mag(acos(min(oldDir & newDir, 1.0)));

	// Temporary axis with sign information
	vector a = (oldDir ^ newDir);

	// Ensure a is in direction of axis
	a = (a & axis_)*axis_;

	scalar magA = mag(a);

	if (magA > vSmall)
	{
		a /= magA;
	}
	else
	{
		a = Zero;
	}

	// Damping of along axis angular velocity only
	vector moment
	(
		-(
			stiffness_*theta
			+ damping_ * (model_.v(model_.master(bodyID_)).w() & a)
			)*a
	);

	if (model_.debug)
	{
		Info << " angle " << theta * sign(a & axis_)
			<< " moment " << moment
			<< endl;
	}

	// Accumulate the force for the restrained body
	fx[bodyIndex_] += model_.X0(bodyID_).T() & spatialVector(moment, Zero);
}


bool tnbLib::RBD::restraints::linearAxialAngularSpring::read
(
	const dictionary& dict
)
{
	restraint::read(dict);

	refQ_ = coeffs_.lookupOrDefault<tensor>("referenceOrientation", I);

	if (mag(mag(refQ_) - sqrt(3.0)) > 1e-9)
	{
		FatalErrorInFunction
			<< "referenceOrientation " << refQ_ << " is not a rotation tensor. "
			<< "mag(referenceOrientation) - sqrt(3) = "
			<< mag(refQ_) - sqrt(3.0) << nl
			<< exit(FatalError);
	}

	axis_ = coeffs_.lookup("axis");

	scalar magAxis(mag(axis_));

	if (magAxis > vSmall)
	{
		axis_ /= magAxis;
	}
	else
	{
		FatalErrorInFunction
			<< "axis has zero length"
			<< abort(FatalError);
	}

	coeffs_.lookup("stiffness") >> stiffness_;
	coeffs_.lookup("damping") >> damping_;

	return true;
}


void tnbLib::RBD::restraints::linearAxialAngularSpring::write
(
	Ostream& os
) const
{
	restraint::write(os);

	writeEntry(os, "referenceOrientation", refQ_);

	writeEntry(os, "axis", axis_);

	writeEntry(os, "stiffness", stiffness_);

	writeEntry(os, "damping", damping_);
}


// ************************************************************************* //