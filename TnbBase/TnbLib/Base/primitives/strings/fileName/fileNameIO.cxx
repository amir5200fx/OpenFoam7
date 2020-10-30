#include <fileName.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::fileName::fileName(Istream& is)
	:
	string()
{
	is >> *this;
}


FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, fileName& fn)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isString())
	{
		fn = t.stringToken();
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected string, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	fn.stripInvalid();

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, fileName&)");

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const fileName& fn)
{
	os.write(fn);
	os.check("Ostream& operator<<(Ostream&, const fileName&)");
	return os;
}


// ************************************************************************* //