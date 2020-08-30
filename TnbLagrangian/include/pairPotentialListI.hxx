#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::label tnbLib::pairPotentialList::pairPotentialIndex
(
	const label a,
	const label b
) const
{
	label index;

	if (a < b)
	{
		index = a * (2 * nIds_ - a - 1) / 2 + b;
	}

	else
	{
		index = b * (2 * nIds_ - b - 1) / 2 + a;
	}

	if (index > size() - 1)
	{
		FatalErrorInFunction
			<< "Attempting to access a pairPotential with too high an index."
			<< nl << "a = " << a << ", b = " << b << ", index = " << index
			<< nl << "max index = " << size() - 1
			<< nl << abort(FatalError);
	}

	return index;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::pairPotentialList::rCutMax() const
{
	return rCutMax_;
}


inline tnbLib::scalar tnbLib::pairPotentialList::rCutMaxSqr() const
{
	return rCutMaxSqr_;
}


inline const tnbLib::pairPotential& tnbLib::pairPotentialList::electrostatic() const
{
	return electrostaticPotential_;
}


// ************************************************************************* //