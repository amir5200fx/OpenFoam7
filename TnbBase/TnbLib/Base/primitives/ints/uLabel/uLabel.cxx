#include <uLabel.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#if WM_LABEL_SIZE == 32
const char* const tnbLib::pTraits<uint64_t>::typeName = "uint64";
const char* const tnbLib::pTraits<uint32_t>::typeName = "uLabel";
#elif WM_LABEL_SIZE == 64
const char* const tnbLib::pTraits<uint64_t>::typeName = "uLabel";
const char* const tnbLib::pTraits<uint32_t>::typeName = "uint32";
#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::uLabel tnbLib::pow(uLabel a, uLabel b)
{
	uLabel ans = 1;
	for (uLabel i = 0; i < b; i++)
	{
		ans *= a;
	}

	return ans;
}


tnbLib::uLabel tnbLib::factorial(uLabel n)
{
	static uLabel factTable[13] =
	{
		1, 1, 2, 6, 24, 120, 720, 5040, 40320,
		362880, 3628800, 39916800, 479001600
	};

#ifdef FULLDEBUG
	if (n > 12)
	{
		FatalErrorInFunction
			<< "n value out of range (> 12)"
			<< abort(FatalError);
	}
#endif

	return factTable[n];
}


// ************************************************************************* //