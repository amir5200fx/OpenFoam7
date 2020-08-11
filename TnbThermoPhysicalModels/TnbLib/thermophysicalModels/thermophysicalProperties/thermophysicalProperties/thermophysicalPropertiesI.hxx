#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::thermophysicalProperties::limit(const scalar T) const
{
	return T;
}


inline tnbLib::scalar tnbLib::thermophysicalProperties::W() const
{
	return W_;
}


// ************************************************************************* //