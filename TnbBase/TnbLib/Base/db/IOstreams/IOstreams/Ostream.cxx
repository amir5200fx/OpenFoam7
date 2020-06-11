#include <Ostream.hxx>

#include <word.hxx>
#include <token.hxx>
#include <keyType.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::Ostream::decrIndent()
{
	if (indentLevel_ == 0)
	{
		cerr << "Ostream::decrIndent() : attempt to decrement 0 indent level"
			<< std::endl;
	}
	else
	{
		indentLevel_--;
	}
}


tnbLib::Ostream& tnbLib::Ostream::write(const keyType& kw)
{
	return writeQuoted(kw, kw.isPattern());
}


tnbLib::Ostream& tnbLib::Ostream::writeKeyword(const keyType& kw)
{
	indent();
	write(kw);

	label nSpaces = entryIndentation_ - label(kw.size());

	// pattern is surrounded by quotes
	if (kw.isPattern())
	{
		nSpaces -= 2;
	}

	// could also increment by indentSize_ ...
	if (nSpaces < 1)
	{
		nSpaces = 1;
	}

	while (nSpaces--)
	{
		write(char(token::SPACE));
	}

	return *this;
}


// ************************************************************************* //