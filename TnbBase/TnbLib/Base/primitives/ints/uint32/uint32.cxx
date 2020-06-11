#include <uint32.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const uint32_t tnbLib::pTraits<uint32_t>::zero = 0;
const uint32_t tnbLib::pTraits<uint32_t>::one = 1;
const uint32_t tnbLib::pTraits<uint32_t>::min = 0;
const uint32_t tnbLib::pTraits<uint32_t>::max = UINT32_MAX;
const uint32_t tnbLib::pTraits<uint32_t>::rootMin = 0;
const uint32_t tnbLib::pTraits<uint32_t>::rootMax = pTraits<uint32_t>::max;

const char* const tnbLib::pTraits<uint32_t>::componentNames[] = { "" };

tnbLib::pTraits<uint32_t>::pTraits(const uint32_t& p)
	:
	p_(p)
{}

tnbLib::pTraits<uint32_t>::pTraits(Istream& is)
{
	is >> p_;
}


// ************************************************************************* //