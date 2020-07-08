#pragma once
// * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * * //

template<class T>
inline const T tnbLib::SVD::sign(const T& a, const T& b)
{
	// return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
	return b >= 0 ? a : -a;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::scalarRectangularMatrix& tnbLib::SVD::U() const
{
	return U_;
}


inline const tnbLib::scalarRectangularMatrix& tnbLib::SVD::V() const
{
	return V_;
}


inline const tnbLib::scalarDiagonalMatrix& tnbLib::SVD::S() const
{
	return S_;
}


inline bool tnbLib::SVD::converged() const
{
	return converged_;
}


inline tnbLib::label tnbLib::SVD::nZeros() const
{
	return nZeros_;
}


inline tnbLib::scalar tnbLib::SVD::minNonZeroS() const
{
	scalar minS = S_[0];
	for (label i = 1; i < S_.size(); i++)
	{
		scalar s = S_[i];
		if (s > vSmall && s < minS) minS = s;
	}
	return minS;
}


// ************************************************************************* //