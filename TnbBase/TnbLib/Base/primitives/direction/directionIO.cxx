#include <direction.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::direction tnbLib::readDirection(Istream& is)
{
	direction val;
	is >> val;

	return val;
}


FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, direction& d)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		d = direction(t.labelToken());
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected direction, found " << t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, direction&)");

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const direction d)
{
	os.write(label(d));
	os.check("Ostream& operator<<(Ostream&, const direction)");
	return os;
}


FoamBase_EXPORT std::ostream& tnbLib::operator<<(std::ostream& os, const direction d)
{
	os << int(d);
	return os;
}


// ************************************************************************* //