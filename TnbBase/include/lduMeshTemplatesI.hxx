#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, class BinaryOp>
void tnbLib::lduMesh::reduce
(
	T& Value,
	const BinaryOp& bop
) const
{
	tnbLib::reduce(Value, bop, Pstream::msgType(), comm());
}


// ************************************************************************* //