#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	inline specie::specie
	(
		const word& name,
		const scalar Y,
		const scalar molWeight
	)
		:
		name_(name),
		Y_(Y),
		molWeight_(molWeight)
	{}


	inline specie::specie
	(
		const scalar Y,
		const scalar molWeight
	)
		:
		Y_(Y),
		molWeight_(molWeight)
	{}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	inline specie::specie(const word& name, const specie& st)
		:
		name_(name),
		Y_(st.Y_),
		molWeight_(st.molWeight_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	inline const word& specie::name() const
	{
		return name_;
	}


	inline scalar specie::W() const
	{
		return molWeight_;
	}


	inline scalar specie::Y() const
	{
		return Y_;
	}


	inline scalar specie::R() const
	{
		return RR / molWeight_;
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	inline void specie::operator=(const specie& st)
	{
		// name_ = st.name_;
		Y_ = st.Y_;
		molWeight_ = st.molWeight_;
	}


	inline void specie::operator+=(const specie& st)
	{
		const scalar sumY = Y_ + st.Y_;
		if (mag(sumY) > small)
		{
			molWeight_ = sumY / (Y_ / molWeight_ + st.Y_ / st.molWeight_);
		}

		Y_ = sumY;
	}


	inline void specie::operator*=(const scalar s)
	{
		Y_ *= s;
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	inline specie operator+(const specie& st1, const specie& st2)
	{
		const scalar sumY = max(st1.Y_ + st2.Y_, small);

		if (mag(sumY) > small)
		{
			return specie
			(
				sumY,
				sumY / (st1.Y_ / st1.molWeight_ + st2.Y_ / st2.molWeight_)
			);
		}
		else
		{
			return st1;
		}
	}


	inline specie operator*(const scalar s, const specie& st)
	{
		return specie
		(
			s*st.Y_,
			st.molWeight_
		);
	}


	inline specie operator==(const specie& st1, const specie& st2)
	{
		scalar diffY = st2.Y_ - st1.Y_;
		if (mag(diffY) < small)
		{
			diffY = small;
		}

		const scalar diffRW =
			st2.Y_ / st2.molWeight_ - st1.Y_ / st1.molWeight_;

		scalar molWeight = great;
		if (mag(diffRW) > small)
		{
			molWeight = diffY / diffRW;
		}

		return specie(diffY, molWeight);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //