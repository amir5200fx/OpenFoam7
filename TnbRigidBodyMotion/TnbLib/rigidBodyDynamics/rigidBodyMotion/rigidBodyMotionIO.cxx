#include <rigidBodyMotion.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::RBD::rigidBodyMotion::read(const dictionary& dict)
{
	rigidBodyModel::read(dict);

	aRelax_ = dict.lookupOrDefault<scalar>("accelerationRelaxation", 1.0);
	aDamp_ = dict.lookupOrDefault<scalar>("accelerationDamping", 1.0);
	report_ = dict.lookupOrDefault<Switch>("report", false);

	return true;
}


void tnbLib::RBD::rigidBodyMotion::write(Ostream& os) const
{
	rigidBodyModel::write(os);

	writeEntry(os, "accelerationRelaxation", aRelax_);
	writeEntry(os, "accelerationDamping", aDamp_);
	writeEntry(os, "report", report_);
}


// ************************************************************************* //