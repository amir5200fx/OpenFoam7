#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline label sign(const label s)
	{
		return (s >= 0) ? 1 : -1;
	}

	inline label pos0(const label s)
	{
		return (s >= 0) ? 1 : 0;
	}

	inline label neg(const label s)
	{
		return (s < 0) ? 1 : 0;
	}

	inline label posPart(const label s)
	{
		return (s > 0) ? s : 0;
	}

	inline label negPart(const label s)
	{
		return (s < 0) ? s : 0;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //