#include <entry.hxx>

#include <dictionary.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

int tnbLib::entry::disableFunctionEntries
(
	tnbLib::debug::infoSwitch("disableFunctionEntries", 0)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::entry::entry(const keyType& keyword)
	:
	IDLList<entry>::link(),
	keyword_(keyword)
{}


tnbLib::entry::entry(const entry& e)
	:
	IDLList<entry>::link(),
	keyword_(e.keyword_)
{}


tnbLib::autoPtr<tnbLib::entry> tnbLib::entry::clone() const
{
	return clone(dictionary::null);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::entry::operator=(const entry& e)
{
	// check for assignment to self
	if (this == &e)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	keyword_ = e.keyword_;
}


bool tnbLib::entry::operator==(const entry& e) const
{
	if (keyword_ != e.keyword_)
	{
		return false;
	}
	else
	{
		OStringStream oss1;
		oss1 << *this;

		OStringStream oss2;
		oss2 << e;

		return oss1.str() == oss2.str();
	}
}


bool tnbLib::entry::operator!=(const entry& e) const
{
	return !operator==(e);
}


// ************************************************************************* //