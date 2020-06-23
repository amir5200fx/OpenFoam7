#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(lduMatrix::smoother, symMatrix);
	defineRunTimeSelectionTable(lduMatrix::smoother, asymMatrix);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word
tnbLib::lduMatrix::smoother::getName
(
	const dictionary& solverControls
)
{
	word name;

	// handle primitive or dictionary entry
	const entry& e = solverControls.lookupEntry("smoother", false, false);
	if (e.isDict())
	{
		e.dict().lookup("smoother") >> name;
	}
	else
	{
		e.stream() >> name;
	}

	return name;
}


tnbLib::autoPtr<tnbLib::lduMatrix::smoother> tnbLib::lduMatrix::smoother::New
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& solverControls
)
{
	word name;

	// handle primitive or dictionary entry
	const entry& e = solverControls.lookupEntry("smoother", false, false);
	if (e.isDict())
	{
		e.dict().lookup("smoother") >> name;
	}
	else
	{
		e.stream() >> name;
	}

	// not (yet?) needed:
	// const dictionary& controls = e.isDict() ? e.dict() : dictionary::null;

	if (matrix.symmetric())
	{
		symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(name);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(solverControls)
				<< "Unknown symmetric matrix smoother "
				<< name << nl << nl
				<< "Valid symmetric matrix smoothers are :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduMatrix::smoother>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					interfaceBouCoeffs,
					interfaceIntCoeffs,
					interfaces
					)
				);
	}
	else if (matrix.asymmetric())
	{
		asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(name);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(solverControls)
				<< "Unknown asymmetric matrix smoother "
				<< name << nl << nl
				<< "Valid asymmetric matrix smoothers are :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduMatrix::smoother>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					interfaceBouCoeffs,
					interfaceIntCoeffs,
					interfaces
					)
				);
	}
	else
	{
		FatalIOErrorInFunction(solverControls)
			<< "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<lduMatrix::smoother>(nullptr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::lduMatrix::smoother::smoother
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	fieldName_(fieldName),
	matrix_(matrix),
	interfaceBouCoeffs_(interfaceBouCoeffs),
	interfaceIntCoeffs_(interfaceIntCoeffs),
	interfaces_(interfaces)
{}


// ************************************************************************* //