#include <uint64.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const uint64_t tnbLib::pTraits<uint64_t>::zero = 0;
const uint64_t tnbLib::pTraits<uint64_t>::one = 1;
const uint64_t tnbLib::pTraits<uint64_t>::min = 0;
const uint64_t tnbLib::pTraits<uint64_t>::max = UINT64_MAX;
const uint64_t tnbLib::pTraits<uint64_t>::rootMin = 0;
const uint64_t tnbLib::pTraits<uint64_t>::rootMax = pTraits<uint64_t>::max;

const char* const tnbLib::pTraits<uint64_t>::componentNames[] = { "" };

tnbLib::pTraits<uint64_t>::pTraits(const uint64_t& p)
	:
	p_(p)
{}

tnbLib::pTraits<uint64_t>::pTraits(Istream& is)
{
	is >> p_;
}


// ************************************************************************* //