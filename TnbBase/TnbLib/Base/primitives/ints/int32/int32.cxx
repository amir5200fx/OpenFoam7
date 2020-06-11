#include <int32.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const int32_t tnbLib::pTraits<int32_t>::zero = 0;
const int32_t tnbLib::pTraits<int32_t>::one = 1;
const int32_t tnbLib::pTraits<int32_t>::min = INT32_MIN;
const int32_t tnbLib::pTraits<int32_t>::max = INT32_MAX;
const int32_t tnbLib::pTraits<int32_t>::rootMin = pTraits<int32_t>::min;
const int32_t tnbLib::pTraits<int32_t>::rootMax = pTraits<int32_t>::max;

const char* const tnbLib::pTraits<int32_t>::componentNames[] = { "" };

tnbLib::pTraits<int32_t>::pTraits(const int32_t& p)
	:
	p_(p)
{}

tnbLib::pTraits<int32_t>::pTraits(Istream& is)
{
	is >> p_;
}


// ************************************************************************* //