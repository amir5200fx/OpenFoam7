#include <pairPotential.hxx>

#include <IOstreams.hxx>

bool tnbLib::pairPotential::writeEnergyAndForceTables(Ostream& os) const
{
	Info << "Writing energy and force tables to file for potential "
		<< name_ << endl;

	List<Pair <scalar>> eTab(energyTable());

	List<Pair <scalar>> fTab(forceTable());

	forAll(eTab, e)
	{
		os << eTab[e].first()
			<< token::SPACE
			<< eTab[e].second()
			<< token::SPACE
			<< fTab[e].second()
			<< nl;
	}

	return os.good();
}


// ************************************************************************* //