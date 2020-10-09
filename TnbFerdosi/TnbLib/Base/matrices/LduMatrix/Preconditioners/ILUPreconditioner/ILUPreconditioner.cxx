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
			auto t = std::make_tuple(true, i);
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

void tnbLib::ILUPreconditioner::calcReciprocalLD
(
	scalarField& rD, 
	scalarField& rL,
	const lduMatrix & matrix
)
{
	auto rDPtr = rD.begin();
	auto rLPtr = rL.begin();

	const auto uPtr = matrix.lduAddr().upperAddr().begin();
	const auto lPtr = matrix.lduAddr().lowerAddr().begin();

	const auto upperPtr = matrix.upper().begin();
	const auto lowerPtr = matrix.lower().begin();
	const auto ownerStartPtr = matrix.lduAddr().ownerStartAddr().begin();
	const auto neighborStartPtr = matrix.lduAddr().losortStartAddr().begin();

	for (label row = 0; row < rD.size(); row++)
	{

		//auto rowMinusOne = row - 1;
		for (label k = 0; k < row; k++)
		{
			auto fStart = ownerStartPtr[k];
			auto fEnd = ownerStartPtr[k + 1];

			rD[row] -= 
				multiplyInColumn
				(
					row, row,
					fStart, fEnd,
					rL, matrix.lduAddr().lowerAddr()
				);
		}
		rD[row] = sqrt(rD[row]);

		auto fStart = ownerStartPtr[row];
		auto fEnd = ownerStartPtr[row + 1];

		for (label rowJ = fStart; rowJ < fEnd; rowJ++)
		{
			if (ownerStartPtr[rowJ] > row)
			{

				for (label k = 0; k < row; k++)
				{
					auto innerFStart = ownerStartPtr[k];
					auto innerFEnd = ownerStartPtr[k + 1];

					rL[ownerStartPtr[rowJ]] -= 
						multiplyInColumn
						(
							row, row, 
							innerFStart, innerFEnd,
							rL, matrix.lduAddr().lowerAddr()
						);
				}

				rL[ownerStartPtr[rowJ]] /= rD[row];
			}
		}
	}
}