#include <GAMGInterfaceField.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::GAMGInterfaceField> tnbLib::GAMGInterfaceField::New
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
{
	const word coupleType(fineInterface.interfaceFieldType());

	lduInterfaceFieldConstructorTable::iterator cstrIter =
		lduInterfaceFieldConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceFieldConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown GAMGInterfaceField type "
			<< coupleType << nl
			<< "Valid GAMGInterfaceField types are :"
			<< lduInterfaceFieldConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<GAMGInterfaceField>(cstrIter()(GAMGCp, fineInterface));
}


tnbLib::autoPtr<tnbLib::GAMGInterfaceField> tnbLib::GAMGInterfaceField::New
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
{
	const word coupleType(GAMGCp.type());

	lduInterfaceConstructorTable::iterator cstrIter =
		lduInterfaceConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown GAMGInterfaceField type "
			<< coupleType << nl
			<< "Valid GAMGInterfaceField types are :"
			<< lduInterfaceConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<GAMGInterfaceField>(cstrIter()(GAMGCp, doTransform, rank));
}


// ************************************************************************* //