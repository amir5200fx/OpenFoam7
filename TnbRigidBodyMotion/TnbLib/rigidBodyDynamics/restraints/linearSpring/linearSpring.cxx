#include <linearSpring.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace restraints
		{
			defineTypeNameAndDebug(linearSpring, 0);

			addToRunTimeSelectionTable
			(
				restraint,
				linearSpring,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::restraints::linearSpring::linearSpring
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

tnbLib::RBD::restraints::linearSpring::~linearSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::restraints::linearSpring::restrain
(
	scalarField& tau,
	Field<spatialVector>& fx
) const
{
	point attachmentPt = bodyPoint(refAttachmentPt_);

	// Current axis of the spring
	vector r = attachmentPt - anchor_;
	scalar magR = mag(r);
	r /= (magR + vSmall);

	// Velocity of the attached end of the spring
	vector v = bodyPointVelocity(refAttachmentPt_).l();

	// Force and moment on the master body including optional damping
	vector force
	(
		(-stiffness_ * (magR - restLength_) - damping_ * (r & v))*r
	);

	vector moment(attachmentPt ^ force);

	if (model_.debug)
	{
		Info << " attachmentPt " << attachmentPt
			<< " attachmentPt - anchor " << r * magR
			<< " spring length " << magR
			<< " force " << force
			<< " moment " << moment
			<< endl;
	}

	// Accumulate the force for the restrained body
	fx[bodyIndex_] += spatialVector(moment, force);
}


bool tnbLib::RBD::restraints::linearSpring::read
(
	const dictionary& dict
)
{
	restraint::read(dict);

	coeffs_.lookup("anchor") >> anchor_;
	coeffs_.lookup("refAttachmentPt") >> refAttachmentPt_;
	coeffs_.lookup("stiffness") >> stiffness_;
	coeffs_.lookup("damping") >> damping_;
	coeffs_.lookup("restLength") >> restLength_;

	return true;
}


void tnbLib::RBD::restraints::linearSpring::write
(
	Ostream& os
) const
{
	restraint::write(os);

	writeEntry(os, "anchor", anchor_);

	writeEntry(os, "refAttachmentPt", refAttachmentPt_);

	writeEntry(os, "stiffness", stiffness_);

	writeEntry(os, "damping", damping_);

	writeEntry(os, "restLength", restLength_);
}


// ************************************************************************* //