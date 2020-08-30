#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::label tnbLib::tetherPotentialList::tetherPotentialIndex
(
	const label a
) const
{
	label index = idMap_[a];

	if (index == -1 || a >= idMap_.size())
	{
		FatalErrorInFunction
			<< "Attempting to access an undefined tetherPotential."
			<< abort(FatalError);

		return -1;
	}
	else
	{
		return index;
	}
}


// ************************************************************************* //