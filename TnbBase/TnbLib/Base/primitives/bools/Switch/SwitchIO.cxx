#include <Switch.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Switch::Switch(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, Switch& s)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isLabel())
	{
		s = bool(t.labelToken());
	}
	else if (t.isWord())
	{
		// allow invalid values, but catch after for correct error message
		Switch sw(t.wordToken(), true);

		if (sw.valid())
		{
			s = sw;
		}
		else
		{
			is.setBad();
			FatalIOErrorInFunction(is)
				<< "expected 'true/false', 'on/off' ... found " << t.wordToken()
				<< exit(FatalIOError);

			return is;
		}
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected bool, found " << t
			<< exit(FatalIOError);

		return is;
	}


	// Check state of Istream
	is.check("Istream& operator>>(Istream&, Switch&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Switch& s)
{
	os << Switch::names[int(s.switch_)];
	os.check("Ostream& operator<<(Ostream&, const Switch&)");
	return os;
}


// ************************************************************************* //