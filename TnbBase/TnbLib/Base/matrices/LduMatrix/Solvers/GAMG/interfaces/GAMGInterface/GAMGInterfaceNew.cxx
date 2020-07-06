#include <GAMGInterface.hxx>

#include <GAMGAgglomeration.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::GAMGInterface> tnbLib::GAMGInterface::New
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing,
	const label fineLevelIndex,
	const label coarseComm
)
{
	const word coupleType(fineInterface.type());

	lduInterfaceConstructorTable::iterator cstrIter =
		lduInterfaceConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown GAMGInterface type " << coupleType << ".\n"
			<< "Valid GAMGInterface types are :"
			<< lduInterfaceConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<GAMGInterface>
		(
			cstrIter()
			(
				index,
				coarseInterfaces,
				fineInterface,
				localRestrictAddressing,
				neighbourRestrictAddressing,
				fineLevelIndex,
				coarseComm
				)
			);
}


tnbLib::autoPtr<tnbLib::GAMGInterface> tnbLib::GAMGInterface::New
(
	const word& coupleType,
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	Istream& is
)
{
	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(coupleType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown GAMGInterface type " << coupleType << ".\n"
			<< "Valid GAMGInterface types are :"
			<< IstreamConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<GAMGInterface>(cstrIter()(index, coarseInterfaces, is));
}


// ************************************************************************* //