#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


inline tnbLib::label tnbLib::ODESolver::nEqns() const
{
	return n_;
}


inline tnbLib::scalarField& tnbLib::ODESolver::absTol()
{
	return absTol_;
}


inline tnbLib::scalarField& tnbLib::ODESolver::relTol()
{
	return relTol_;
}


template<class Type>
inline void tnbLib::ODESolver::resizeField(UList<Type>& f, const label n)
{
	f.shallowCopy(UList<Type>(f.begin(), n));
}


template<class Type>
inline void tnbLib::ODESolver::resizeField(UList<Type>& f) const
{
	resizeField(f, n_);
}


inline void tnbLib::ODESolver::resizeMatrix(scalarSquareMatrix& m) const
{
	m.shallowResize(n_);
}


// ************************************************************************* //