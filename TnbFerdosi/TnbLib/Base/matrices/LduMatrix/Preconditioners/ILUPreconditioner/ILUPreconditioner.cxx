#include <ILUPreconditioner.hxx>

void tnbLib::ILUPreconditioner::calcReciprocalD
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

	for (label face = 0; face < matrix.lower().size(); face++)
	{
		rDPtr[lPtr[face]] -= lowerPtr[face] * lowerPtr[face];
	}

	for (label i = 0; i < rD.size(); i++)
	{
		rDPtr[i] = sqrt(rDPtr[i]);
	}

	for (label row = 0; row < rD.size(); row++)
	{
		// Start and end of this row
		auto fFirst = ownerStartPtr[row];
		auto fLast = ownerStartPtr[row + 1];

		for (label face = fFirst; face < fLast; face++)
		{

		}
	}
}