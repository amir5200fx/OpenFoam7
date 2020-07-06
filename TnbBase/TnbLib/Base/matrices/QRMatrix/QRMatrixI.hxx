#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class MatrixType>
inline tnbLib::QRMatrix<MatrixType>::QRMatrix()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class MatrixType>
inline const typename tnbLib::QRMatrix<MatrixType>::QMatrixType&
tnbLib::QRMatrix<MatrixType>::Q() const
{
	return Q_;
}


template<class MatrixType>
inline const typename tnbLib::QRMatrix<MatrixType>::RMatrixType&
tnbLib::QRMatrix<MatrixType>::R() const
{
	return R_;
}


// ************************************************************************* //