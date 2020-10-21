#include <IOdictionary.hxx>

#include <Pstream.hxx>
#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * * * Members Functions * * * * * * * * * * * * * //

bool tnbLib::IOdictionary::readData(Istream& is)
{
	is >> *this;

	if (writeDictionaries && Pstream::master() && !is.bad())
	{
		Sout << nl
			<< "--- IOdictionary " << name()
			<< ' ' << objectPath() << ":" << nl;
		writeHeader(Sout);
		writeData(Sout);
		Sout << "--- End of IOdictionary " << name() << nl << endl;
	}

	return !is.bad();
}


bool tnbLib::IOdictionary::writeData(Ostream& os) const
{
	dictionary::write(os, false);
	return os.good();
}


// ************************************************************************* //