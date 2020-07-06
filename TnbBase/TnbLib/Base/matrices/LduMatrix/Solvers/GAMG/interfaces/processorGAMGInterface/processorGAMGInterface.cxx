#include <processorGAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <HashTable.hxx>
#include <labelPair.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		processorGAMGInterface,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		processorGAMGInterface,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorGAMGInterface::processorGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing,
	const label fineLevelIndex,
	const label coarseComm
)
	:
	GAMGInterface
	(
		index,
		coarseInterfaces
	),
	comm_(coarseComm),
	myProcNo_(refCast<const processorLduInterface>(fineInterface).myProcNo()),
	neighbProcNo_
	(
		refCast<const processorLduInterface>(fineInterface).neighbProcNo()
	),
	forwardT_(refCast<const processorLduInterface>(fineInterface).forwardT()),
	tag_(refCast<const processorLduInterface>(fineInterface).tag())
{
	// From coarse face to coarse cell
	DynamicList<label> dynFaceCells(localRestrictAddressing.size());
	// From fine face to coarse face
	DynamicList<label> dynFaceRestrictAddressing
	(
		localRestrictAddressing.size()
	);

	// From coarse cell pair to coarse face
	HashTable<label, labelPair, labelPair::Hash<>> cellsToCoarseFace
	(
		2 * localRestrictAddressing.size()
	);

	forAll(localRestrictAddressing, ffi)
	{
		labelPair cellPair;

		// Do switching on master/slave indexes based on the owner/neighbour of
		// the processor index such that both sides get the same answer.
		if (myProcNo() < neighbProcNo())
		{
			// Master side
			cellPair = labelPair
			(
				localRestrictAddressing[ffi],
				neighbourRestrictAddressing[ffi]
			);
		}
		else
		{
			// Slave side
			cellPair = labelPair
			(
				neighbourRestrictAddressing[ffi],
				localRestrictAddressing[ffi]
			);
		}

		HashTable<label, labelPair, labelPair::Hash<>>::const_iterator fnd =
			cellsToCoarseFace.find(cellPair);

		if (fnd == cellsToCoarseFace.end())
		{
			// New coarse face
			label coarseI = dynFaceCells.size();
			dynFaceRestrictAddressing.append(coarseI);
			dynFaceCells.append(localRestrictAddressing[ffi]);
			cellsToCoarseFace.insert(cellPair, coarseI);
		}
		else
		{
			// Already have coarse face
			dynFaceRestrictAddressing.append(fnd());
		}
	}

	faceCells_.transfer(dynFaceCells);
	faceRestrictAddressing_.transfer(dynFaceRestrictAddressing);
}


tnbLib::processorGAMGInterface::processorGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	const labelUList& faceCells,
	const labelUList& faceRestrictAddresssing,
	const label coarseComm,
	const label myProcNo,
	const label neighbProcNo,
	const tensorField& forwardT,
	const int tag
)
	:
	GAMGInterface
	(
		index,
		coarseInterfaces,
		faceCells,
		faceRestrictAddresssing
	),
	comm_(coarseComm),
	myProcNo_(myProcNo),
	neighbProcNo_(neighbProcNo),
	forwardT_(forwardT),
	tag_(tag)
{}


tnbLib::processorGAMGInterface::processorGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	Istream& is
)
	:
	GAMGInterface(index, coarseInterfaces, is),
	comm_(readLabel(is)),
	myProcNo_(readLabel(is)),
	neighbProcNo_(readLabel(is)),
	forwardT_(is),
	tag_(readLabel(is))
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::processorGAMGInterface::~processorGAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::processorGAMGInterface::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	send(commsType, interfaceInternalField(iF)());
}


tnbLib::tmp<tnbLib::labelField> tnbLib::processorGAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	tmp<Field<label>> tfld(receive<label>(commsType, this->size()));

	return tfld;
}


void tnbLib::processorGAMGInterface::write(Ostream& os) const
{
	GAMGInterface::write(os);
	os << token::SPACE << comm_
		<< token::SPACE << myProcNo_
		<< token::SPACE << neighbProcNo_
		<< token::SPACE << forwardT_
		<< token::SPACE << tag_;
}


// ************************************************************************* //