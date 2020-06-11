#include <baseIOdictionary.hxx>

#include <Pstream.hxx>
#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * * * Members Functions * * * * * * * * * * * * * //

bool tnbLib::baseIOdictionary::readData(Istream& is)
{
	is >> *this;

	if (writeDictionaries && Pstream::master() && !is.bad())
	{
		Sout << nl
			<< "--- baseIOdictionary " << name()
			<< ' ' << objectPath() << ":" << nl;
		writeHeader(Sout);
		writeData(Sout);
		Sout << "--- End of baseIOdictionary " << name() << nl << endl;
	}

	return !is.bad();
}


bool tnbLib::baseIOdictionary::writeData(Ostream& os) const
{
	dictionary::write(os, false);
	return os.good();
}


// ************************************************************************* //