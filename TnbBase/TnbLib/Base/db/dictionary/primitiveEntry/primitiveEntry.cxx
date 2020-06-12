#include <primitiveEntry.hxx>

#include <dictionary.hxx>
#include <OSspecific.hxx>
#include <stringOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveEntry::append(const UList<token>& varTokens)
{
	forAll(varTokens, i)
	{
		newElmt(tokenIndex()++) = varTokens[i];
	}
}


bool tnbLib::primitiveEntry::expandVariable
(
	const string& w,
	const dictionary& dict
)
{
	if (w.size() > 2 && w[0] == '$' && w[1] == token::BEGIN_BLOCK)
	{
		// Recursive substitution mode. Replace between {} with expansion.
		string s(w(2, w.size() - 3));
		// Substitute dictionary and environment variables. Do not allow
		// empty substitutions.
		stringOps::inplaceExpand(s, dict, true, false);
		string newW(w);
		newW.std::string::replace(1, newW.size() - 1, s);

		return expandVariable(newW, dict);
	}
	else
	{
		string varName = w(1, w.size() - 1);

		// lookup the variable name in the given dictionary....
		// Note: allow wildcards to match? For now disabled since following
		// would expand internalField to wildcard match and not expected
		// internalField:
		//      internalField XXX;
		//      boundaryField { ".*" {YYY;} movingWall {value $internalField;}
		const entry* ePtr = dict.lookupScopedEntryPtr(varName, true, false);

		// ...if defined append its tokens into this
		if (ePtr)
		{
			if (ePtr->isDict())
			{
				append(ePtr->dict().tokens());
			}
			else
			{
				append(ePtr->stream());
			}
		}
		else
		{
			// not in the dictionary - try an environment variable
			string envStr = getEnv(varName);

			if (envStr.empty())
			{
				FatalIOErrorInFunction
				(
					dict
				) << "Illegal dictionary entry or environment variable name "
					<< varName << endl << "Valid dictionary entries are "
					<< dict.toc() << exit(FatalIOError);

				return false;
			}
			append(tokenList(IStringStream('(' + envStr + ')')()));
		}
	}
	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::primitiveEntry::primitiveEntry(const keyType& key, const ITstream& is)
	:
	entry(key),
	ITstream(is)
{
	name() += '.' + keyword();
}


tnbLib::primitiveEntry::primitiveEntry(const keyType& key, const token& t)
	:
	entry(key),
	ITstream(key, tokenList(1, t))
{}


tnbLib::primitiveEntry::primitiveEntry
(
	const keyType& key,
	const UList<token>& tokens
)
	:
	entry(key),
	ITstream(key, tokens)
{}


tnbLib::primitiveEntry::primitiveEntry
(
	const keyType& key,
	List<token>&& tokens
)
	:
	entry(key),
	ITstream(key, move(tokens))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::primitiveEntry::startLineNumber() const
{
	const tokenList& tokens = *this;

	if (tokens.empty())
	{
		return -1;
	}
	else
	{
		return tokens.first().lineNumber();
	}
}


tnbLib::label tnbLib::primitiveEntry::endLineNumber() const
{
	const tokenList& tokens = *this;

	if (tokens.empty())
	{
		return -1;
	}
	else
	{
		return tokens.last().lineNumber();
	}
}


tnbLib::ITstream& tnbLib::primitiveEntry::stream() const
{
	ITstream& is = const_cast<primitiveEntry&>(*this);
	is.rewind();
	return is;
}


const tnbLib::dictionary& tnbLib::primitiveEntry::dict() const
{
	FatalErrorInFunction
		<< "Attempt to return primitive entry " << info()
		<< " as a sub-dictionary"
		<< abort(FatalError);

	return dictionary::null;
}


tnbLib::dictionary& tnbLib::primitiveEntry::dict()
{
	FatalErrorInFunction
		<< "Attempt to return primitive entry " << info()
		<< " as a sub-dictionary"
		<< abort(FatalError);

	return const_cast<dictionary&>(dictionary::null);
}


// ************************************************************************* //