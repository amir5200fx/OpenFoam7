#include <token.hxx>

#include <error.hxx>
#include <IOstreams.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::token::token(Istream& is)
	:
	type_(UNDEFINED)
{
	is.read(*this);
}


// * * * * * * * * * * * * IOstream operators  * * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, token& t)
{
	t.clear();
	return is.read(t);
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const token& t)
{
	switch (t.type_)
	{
	case token::UNDEFINED:
		os << "UNDEFINED";
		WarningInFunction
			<< "Undefined token" << endl;
		break;

	case token::PUNCTUATION:
		os << t.punctuationToken_;
		break;

	case token::WORD:
		os << *t.wordTokenPtr_;
		break;

	case token::STRING:
	case token::VERBATIMSTRING:
		os << *t.stringTokenPtr_;
		break;

	case token::VARIABLE:
		// Behaviour differs according to stream type
		os.write(t);
		break;

	case token::LABEL:
		os << t.labelToken_;
		break;

	case token::FLOAT_SCALAR:
		os << t.floatScalarToken_;
		break;

	case token::DOUBLE_SCALAR:
		os << t.doubleScalarToken_;
		break;

	case token::LONG_DOUBLE_SCALAR:
		os << *t.longDoubleScalarTokenPtr_;
		break;

	case token::COMPOUND:
		os << *t.compoundTokenPtr_;
		break;

	case token::ERROR:
		os << "ERROR";
		WarningInFunction
			<< "Error token" << endl;
		break;

	default:
		os << "UNKNOWN";
		SeriousErrorInFunction
			<< "Unknown token"
			<< endl;
	}

	// Check state of stream
	os.check("Ostream& operator<<(Ostream&, const token&)");

	return os;
}


FoamBase_EXPORT ostream& tnbLib::operator<<(ostream& os, const token::punctuationToken& pt)
{
	return os << char(pt);
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const token::punctuationToken& pt)
{
	return os << char(pt);
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const token::compound& ct)
{
	os << ct.type() << token::SPACE;
	ct.write(os);

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

FoamBase_EXPORT ostream& tnbLib::operator<<(ostream& os, const InfoProxy<token>& ip)
{
	const token& t = ip.t_;

	os << "on line " << t.lineNumber();

	switch (t.type())
	{
	case token::UNDEFINED:
		os << " an undefined token";
		break;

	case token::PUNCTUATION:
		os << " the punctuation token " << '\'' << t.pToken() << '\'';
		break;

	case token::WORD:
		os << " the word " << '\'' << t.wordToken() << '\'';
		break;

	case token::STRING:
		os << " the string " << t.stringToken();
		break;

	case token::VARIABLE:
		os << " the variable " << t.stringToken();
		break;

	case token::VERBATIMSTRING:
		os << " the verbatim string " << t.stringToken();
		break;

	case token::LABEL:
		os << " the label " << t.labelToken();
		break;

	case token::FLOAT_SCALAR:
		os << " the floatScalar " << t.floatScalarToken();
		break;

	case token::DOUBLE_SCALAR:
		os << " the doubleScalar " << t.doubleScalarToken();
		break;

	case token::LONG_DOUBLE_SCALAR:
		os << " the longDoubleScalar " << t.longDoubleScalarToken();
		break;

	case token::COMPOUND:
	{
		if (t.compoundToken().empty())
		{
			os << " the empty compound of type "
				<< t.compoundToken().type();
		}
		else
		{
			os << " the compound of type "
				<< t.compoundToken().type();
		}
	}
	break;

	case token::ERROR:
		os << " an error";
		break;

	default:
		os << " an unknown token type " << '\'' << int(t.type()) << '\'';
	}

	return os;
}


template<>
FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<token>& ip)
{
	const token& t = ip.t_;

	os << "on line " << t.lineNumber();

	switch (t.type())
	{
	case token::UNDEFINED:
		os << " an undefined token";
		break;

	case token::PUNCTUATION:
		os << " the punctuation token " << '\'' << t.pToken() << '\'';
		break;

	case token::WORD:
		os << " the word " << '\'' << t.wordToken() << '\'';
		break;

	case token::STRING:
		os << " the string " << t.stringToken();
		break;

	case token::VARIABLE:
		os << " the variable " << t.stringToken();
		break;

	case token::VERBATIMSTRING:
		os << " the verbatim string " << t.stringToken();
		break;

	case token::LABEL:
		os << " the label " << t.labelToken();
		break;

	case token::FLOAT_SCALAR:
		os << " the floatScalar " << t.floatScalarToken();
		break;

	case token::DOUBLE_SCALAR:
		os << " the doubleScalar " << t.doubleScalarToken();
		break;

	case token::LONG_DOUBLE_SCALAR:
		os << " the longDoubleScalar " << t.longDoubleScalarToken();
		break;

	case token::COMPOUND:
	{
		if (t.compoundToken().empty())
		{
			os << " the empty compound of type "
				<< t.compoundToken().type();
		}
		else
		{
			os << " the compound of type "
				<< t.compoundToken().type();
		}
	}
	break;

	case token::ERROR:
		os << " an error";
		break;

	default:
		os << " an unknown token type " << '\'' << int(t.type()) << '\'';
	}

	return os;
}


// ************************************************************************* //