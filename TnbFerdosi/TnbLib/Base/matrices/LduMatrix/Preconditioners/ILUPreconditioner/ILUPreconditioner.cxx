#include <ILUPreconditioner.hxx>

std::tuple<bool, tnbLib::label> 
tnbLib::ILUPreconditioner::isZero
(
	const label row, 
	const label start, 
	const label end,
	const labelUList & addr
)
{
	for (label i = start; i < end; i++)
	{
		if (addr[i] > row)
		{
			auto t = std::make_tuple(true, 0);
			return std::move(t);
		}
		if (addr[i] == row)
		{
			auto t = std::make_tuple(false, i);
			return std::move(t);
		}
	}
	auto t = std::make_tuple(true, 0);
	return std::move(t);
}

tnbLib::scalar
tnbLib::ILUPreconditioner::multiplyInColumn
(
	const label i,
	const label j, 
	const label start,
	const label end,
	const scalarField & rL,
	const labelUList & addr
)
{
	auto[isZeroLi, LiId] = isZero(i, start, end, addr);
	if (isZeroLi) return 0;

	auto[isZeroLj, LjId] = isZero(j, start, end, addr);
	if (isZeroLj) return 0;

	return rL[LiId] * rL[LjId];
}

tnbLib::ILUPreconditioner::bandMatrix 
tnbLib::ILUPreconditioner::allocateBandMatrix
(
	const lduMatrix & matrix
)
{
	const auto& diag = matrix.diag();
	const auto lPtr = matrix.lduAddr().lowerAddr().begin();
	const auto lowerPtr = matrix.lower().begin();
	const auto ownerStartPtr = matrix.lduAddr().ownerStartAddr().begin();

	bandMatrix bm;
	auto& a = bm.Array;
	auto& b = bm.band;
	a = new scalar*[diag.size()];
	b = new label[diag.size()];

	const auto lPtr = matrix.lduAddr().lowerAddr().begin();

	for (label i = 0; i < diag.size(); i++)
	{
		auto fStart = ownerStartPtr[i];
		auto fEnd = ownerStartPtr[i + 1];

		b[i] = lPtr[fEnd - 1] - i;
		a[i] = new scalar[b[i] + 1];
		a[i] += b[i];

		a[i][0] = diag[i];

		for (label j = 0; j < b[i]; j++)
		{
			a[i][j] = (scalar)0.0;
		}

		for (label j = fStart; j < fEnd; j++)
		{
#ifdef _DEBUG
			if (lPtr[j] - i >= b[i])
			{
				FatalErrorIn(FUNCTION_NAME)
					<< "out of boundry:" << endl
					<< " - band = " << b[i] << endl
					<< " - j = " << lPtr[j] << endl
					<< abort(FatalError);
			}
#endif // _DEBUG
			
			a[i][i - lPtr[j]] = lowerPtr[j];
		}
	}
	return std::move(bm);
}

namespace tnbLib
{
	scalar maxNorm1(const label row, const lduMatrix & matrix)
	{
		const auto ownerStartPtr = matrix.lduAddr().ownerStartAddr().begin();
		const auto lowerPtr = matrix.lower().begin();

		auto fStart = ownerStartPtr[row];
		auto fEnd = ownerStartPtr[row + 1];

		auto maxNorm = (scalar)0;
		for (size_t i = fStart; i < fEnd; i++)
		{
			if (abs(lowerPtr[fStart]) > maxNorm)
			{
				maxNorm = abs(lowerPtr[fStart]);
			}
		}
		return maxNorm;
	}
}

//namespace tnbLib
//{
//
//	scalar retrieveArray(const label i, const label j, const label* b, const scalar** a)
//	{
//		if (j < -b[i])
//		{
//			return 0;
//		}
//		else
//		{
//			return a[i][j];
//		}
//	}
//}

void tnbLib::ILUPreconditioner::calcReciprocalLD
(
	bandMatrix & bnd,
	const lduMatrix & matrix,
	const scalar epsilon
)
{
	auto& a = bnd.Array;
	auto& b = bnd.band;

	const auto uPtr = matrix.lduAddr().upperAddr().begin();
	const auto lPtr = matrix.lduAddr().lowerAddr().begin();

	const auto upperPtr = matrix.upper().begin();
	const auto lowerPtr = matrix.lower().begin();
	const auto ownerStartPtr = matrix.lduAddr().ownerStartAddr().begin();

	for (label i = 0; i < matrix.diag().size(); i++)
	{
		auto ip = max(i - b[i], 0);
		for (label k = ip; k < i; k++)
		{
			a[i][i] -= a[i][k - i] * a[i][k - i];
		}
		a[i][i] = sqrt(a[i][i]);

		auto criterion = maxNorm1(i, matrix);

		for (label row = i + 1; row <= i + ip; row++)
		{
			auto ipw = max(row - b[row], 0);
			if (ip < ipw)
			{
				continue;
			}

			auto t = a[row][i - row];
			for (label k = ip; k < row; k++)
			{
				t -= a[i][k - row] * a[row][k - row];
			}

			t /= a[i][i];
			if (abs(t) > criterion)
			{
				a[row][i - row] = t;
			}
		}
	}
}

//void tnbLib::ILUPreconditioner::calcReciprocalLD
//(
//	scalarField& rD, 
//	scalarField& rL,
//	const lduMatrix & matrix
//)
//{
//	auto rDPtr = rD.begin();
//	auto rLPtr = rL.begin();
//
//	const auto uPtr = matrix.lduAddr().upperAddr().begin();
//	const auto lPtr = matrix.lduAddr().lowerAddr().begin();
//
//	const auto upperPtr = matrix.upper().begin();
//	const auto lowerPtr = matrix.lower().begin();
//	const auto ownerStartPtr = matrix.lduAddr().ownerStartAddr().begin();
//	const auto neighborStartPtr = matrix.lduAddr().losortStartAddr().begin();
//
//	for (label row = 0; row < rD.size(); row++)
//	{
//
//		//auto rowMinusOne = row - 1;
//		for (label k = 0; k < row; k++)
//		{
//			auto fStart = ownerStartPtr[k];
//			auto fEnd = ownerStartPtr[k + 1];
//
//			rD[row] -= 
//				multiplyInColumn
//				(
//					row, row,
//					fStart, fEnd,
//					rL, matrix.lduAddr().lowerAddr()
//				);
//		}
//		rD[row] = sqrt(rD[row]);
//
//		auto fStart = ownerStartPtr[row];
//		auto fEnd = ownerStartPtr[row + 1];
//
//		for (label rowJ = fStart; rowJ < fEnd; rowJ++)
//		{
//			if (ownerStartPtr[rowJ] > row)
//			{
//
//				for (label k = 0; k < row; k++)
//				{
//					auto innerFStart = ownerStartPtr[k];
//					auto innerFEnd = ownerStartPtr[k + 1];
//
//					rL[ownerStartPtr[rowJ]] -= 
//						multiplyInColumn
//						(
//							row, row, 
//							innerFStart, innerFEnd,
//							rL, matrix.lduAddr().lowerAddr()
//						);
//				}
//
//				rL[ownerStartPtr[rowJ]] /= rD[row];
//			}
//		}
//	}
//}