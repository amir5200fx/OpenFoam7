#include <keyType.hxx>

#include <regExp.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::keyType tnbLib::keyType::null;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::keyType::keyType(Istream& is)
	:
	word(),
	isPattern_(false)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::keyType::match
(
	const std::string& str,
	bool literalMatch
) const
{
	if (literalMatch || !isPattern_)
	{
		// check as string
		return (str == *this);
	}
	else
	{
		// check as regex
		return regExp(*this).match(str);
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, keyType& kw)
{
	token t(is);

	if (!t.good())
	{
		is.setBad();
		return is;
	}

	if (t.isWord())
	{
		kw = t.wordToken();
	}
	else if (t.isString())
	{
		// Assign from string. Set as regular expression.
		kw = t.stringToken();
		kw.isPattern_ = true;

		// flag empty strings as an error
		if (kw.empty())
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
	is.check("Istream& operator>>(Istream&, keyType&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const keyType& kw)
{
	os.write(kw);
	os.check("Ostream& operator<<(Ostream&, const keyType&)");
	return os;
}


// ************************************************************************* //