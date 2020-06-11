#include <bool.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const char* const tnbLib::pTraits<bool>::typeName = "bool";
const bool tnbLib::pTraits<bool>::zero = false;
const bool tnbLib::pTraits<bool>::one = true;

const char* const tnbLib::pTraits<bool>::componentNames[] = { "" };

tnbLib::pTraits<bool>::pTraits(const bool& p)
	:
	p_(p)
{}


tnbLib::pTraits<bool>::pTraits(Istream& is)
{
	is >> p_;
}

// ************************************************************************* //