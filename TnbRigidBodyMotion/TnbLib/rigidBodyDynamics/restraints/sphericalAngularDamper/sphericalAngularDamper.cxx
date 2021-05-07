#include <sphericalAngularDamper.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace restraints
		{
			defineTypeNameAndDebug(sphericalAngularDamper, 0);

			addToRunTimeSelectionTable
			(
				restraint,
				sphericalAngularDamper,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::restraints::sphericalAngularDamper::sphericalAngularDamper
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

tnbLib::RBD::restraints::sphericalAngularDamper::~sphericalAngularDamper()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::restraints::sphericalAngularDamper::restrain
(
	scalarField& tau,
	Field<spatialVector>& fx
) const
{
	vector moment = -coeff_ * model_.v(model_.master(bodyID_)).w();

	if (model_.debug)
	{
		Info << " moment " << moment << endl;
	}

	// Accumulate the force for the restrained body
	fx[bodyIndex_] += model_.X0(bodyID_).T() & spatialVector(moment, Zero);
}


bool tnbLib::RBD::restraints::sphericalAngularDamper::read
(
	const dictionary& dict
)
{
	restraint::read(dict);

	coeffs_.lookup("coeff") >> coeff_;

	return true;
}


void tnbLib::RBD::restraints::sphericalAngularDamper::write
(
	Ostream& os
) const
{
	restraint::write(os);

	writeEntry(os, "coeff", coeff_);
}


// ************************************************************************* //