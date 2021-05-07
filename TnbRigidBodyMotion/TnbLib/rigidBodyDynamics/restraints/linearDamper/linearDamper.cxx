#include <linearDamper.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace restraints
		{
			defineTypeNameAndDebug(linearDamper, 0);

			addToRunTimeSelectionTable
			(
				restraint,
				linearDamper,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::restraints::linearDamper::linearDamper
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

tnbLib::RBD::restraints::linearDamper::~linearDamper()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::restraints::linearDamper::restrain
(
	scalarField& tau,
	Field<spatialVector>& fx
) const
{
	vector force = -coeff_ * model_.v(model_.master(bodyID_)).l();

	if (model_.debug)
	{
		Info << " force " << force << endl;
	}

	// Accumulate the force for the restrained body
	fx[bodyIndex_] += model_.X0(bodyID_).T() & spatialVector(Zero, force);
}


bool tnbLib::RBD::restraints::linearDamper::read
(
	const dictionary& dict
)
{
	restraint::read(dict);

	coeffs_.lookup("coeff") >> coeff_;

	return true;
}


void tnbLib::RBD::restraints::linearDamper::write
(
	Ostream& os
) const
{
	restraint::write(os);

	writeEntry(os, "coeff", coeff_);
}


// ************************************************************************* //