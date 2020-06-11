#include <int64.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const int64_t tnbLib::pTraits<int64_t>::zero = 0;
const int64_t tnbLib::pTraits<int64_t>::one = 1;
const int64_t tnbLib::pTraits<int64_t>::min = INT64_MIN;
const int64_t tnbLib::pTraits<int64_t>::max = INT64_MAX;
const int64_t tnbLib::pTraits<int64_t>::rootMin = pTraits<int64_t>::min;
const int64_t tnbLib::pTraits<int64_t>::rootMax = pTraits<int64_t>::max;

const char* const tnbLib::pTraits<int64_t>::componentNames[] = { "" };

tnbLib::pTraits<int64_t>::pTraits(const int64_t& p)
	:
	p_(p)
{}

tnbLib::pTraits<int64_t>::pTraits(Istream& is)
{
	is >> p_;
}


// ************************************************************************* //