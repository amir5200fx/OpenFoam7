#include <procLduMatrix.hxx>

#include <procLduInterface.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::procLduMatrix::procLduMatrix
(
	const lduMatrix& ldum,
	const FieldField<Field, scalar>& interfaceCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	upperAddr_(ldum.lduAddr().upperAddr()),
	lowerAddr_(ldum.lduAddr().lowerAddr()),
	diag_(ldum.diag()),
	upper_(ldum.upper()),
	lower_(ldum.lower())
{
	label nInterfaces = 0;

	forAll(interfaces, i)
	{
		if (interfaces.set(i))
		{
			nInterfaces++;
		}
	}

	interfaces_.setSize(nInterfaces);

	nInterfaces = 0;

	forAll(interfaces, i)
	{
		if (interfaces.set(i))
		{
			interfaces_.set
			(
				nInterfaces++,
				new procLduInterface
				(
					interfaces[i],
					interfaceCoeffs[i]
				)
			);
		}
	}

}


tnbLib::procLduMatrix::procLduMatrix(Istream& is)
	:
	upperAddr_(is),
	lowerAddr_(is),
	diag_(is),
	upper_(is),
	lower_(is),
	interfaces_(is)
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const procLduMatrix& cldum)
{
	os << cldum.upperAddr_
		<< cldum.lowerAddr_
		<< cldum.diag_
		<< cldum.upper_
		<< cldum.lower_
		<< cldum.interfaces_;

	return os;
}


// ************************************************************************* //