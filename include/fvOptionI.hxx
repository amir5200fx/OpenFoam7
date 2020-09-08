#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::word& tnbLib::fv::option::name() const
{
	return name_;
}


inline const tnbLib::fvMesh& tnbLib::fv::option::mesh() const
{
	return mesh_;
}


inline const tnbLib::dictionary& tnbLib::fv::option::coeffs() const
{
	return coeffs_;
}


inline bool tnbLib::fv::option::active() const
{
	return active_;
}


inline void tnbLib::fv::option::setApplied(const label fieldi)
{
	applied_[fieldi] = true;
}


inline tnbLib::Switch& tnbLib::fv::option::active()
{
	return active_;
}


// ************************************************************************* //