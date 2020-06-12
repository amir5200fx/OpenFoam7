#include <token.hxx>

#include <wordList.hxx> // added by amir
#include <IOstreams.hxx> // added by amir
#include <Istream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	const char* const token::typeName = "token";
	token token::undefinedToken;

	typedef token::compound tokenCompound;
	defineTypeNameAndDebug(tokenCompound, 0);
	defineRunTimeSelectionTable(tokenCompound, Istream);
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::token::parseError(const char* expected) const
{
	FatalIOError
		<< "Parse error, expected a " << expected
		<< ", found \n    " << info() << endl;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::token::compound::~compound()
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::token::compound> tnbLib::token::compound::New
(
	const word& compoundType,
	Istream& is
)
{
	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(compoundType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction(is)
			<< "Unknown compound type " << compoundType << nl << nl
			<< "Valid compound types:" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< abort(FatalIOError);
	}

	return autoPtr<tnbLib::token::compound>(cstrIter()(is));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::token::compound::isCompound(const word& name)
{
	return
		(
			IstreamConstructorTablePtr_
			&& IstreamConstructorTablePtr_->found(name)
			);
}


tnbLib::token::compound& tnbLib::token::transferCompoundToken(const Istream& is)
{
	if (type_ == COMPOUND)
	{
		if (compoundTokenPtr_->empty())
		{
			FatalIOErrorInFunction(is)
				<< "compound has already been transferred from token\n    "
				<< info() << abort(FatalIOError);
		}
		else
		{
			compoundTokenPtr_->empty() = true;
		}

		return *compoundTokenPtr_;
	}
	else
	{
		parseError("compound");
		return *compoundTokenPtr_;
	}
}


// ************************************************************************* //
