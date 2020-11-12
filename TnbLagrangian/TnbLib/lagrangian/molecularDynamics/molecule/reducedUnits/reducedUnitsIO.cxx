#include <reducedUnits.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const reducedUnits& rU)
{
	os << nl << "Defined: " << nl
		<< tab << "refLength = " << rU.refLength() << " m" << nl
		<< tab << "refTime = " << rU.refTime() << " s" << nl
		<< tab << "refMass = " << rU.refMass() << " kg" << nl
		<< tab << "Boltzmann constant, kb = " << reducedUnits::kb << " J/K"
		<< nl << "Calculated: " << nl
		<< tab << "refEnergy = " << rU.refEnergy() << " J" << nl
		<< tab << "refTemp = " << rU.refTemp() << " K" << nl
		<< tab << "refForce = " << rU.refForce() << " N" << nl
		<< tab << "refVelocity = " << rU.refVelocity() << " m/s" << nl
		<< tab << "refVolume = " << rU.refVolume() << " m^3" << nl
		<< tab << "refPressure = " << rU.refPressure() << " N/m^2" << nl
		<< tab << "refMassDensity = " << rU.refMassDensity() << " kg/m^3" << nl
		<< tab << "refNumberDensity = " << rU.refNumberDensity() << " m^-3"
		<< endl;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::reducedUnits&)"
	);

	return os;
}


// ************************************************************************* //