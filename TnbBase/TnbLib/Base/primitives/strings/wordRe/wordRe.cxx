#include <wordRe.hxx>

#include <IOstreams.hxx>
#include <InfoProxy.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::wordRe tnbLib::wordRe::null;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wordRe::wordRe(Istream& is)
	:
	word(),
	re_(nullptr)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, wordRe& w)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isWord())
	{
		w = t.wordToken();
	}
	else if (t.isString())
	{
		// Auto-tests for regular expression
		w = t.stringToken();

		// flag empty strings as an error
		if (w.empty())
		{
			is.setBad();
			FatalIOErrorInFunction(is)
				<< "empty word/expression "
				<< exit(FatalIOError);
			return is;
		}
	}
	else
	{
		is.setBad();
		FatalIOErrorInFunction(is)
			<< "wrong token type - expected word or string, found "
			<< t.info()
			<< exit(FatalIOError);

		return is;
	}

	// Check state of IOstream
	is.check("Istream& operator>>(Istream&, wordRe&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const wordRe& w)
{
	os.writeQuoted(w, w.isPattern());
	os.check("Ostream& operator<<(Ostream&, const wordRe&)");
	return os;
}


tnbLib::Ostream& tnbLib::wordRe::info(Ostream& os) const
{
	if (isPattern())
	{
		os << "wordRe(regex) " << *this;
	}
	else
	{
		os << "wordRe(plain) \"" << *this << '"';
	}
	os.flush();

	return os;
}


// ************************************************************************* //