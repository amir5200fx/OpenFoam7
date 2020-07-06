#include <cyclicGAMGInterface.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <labelPair.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicGAMGInterface,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicGAMGInterface,
		Istream
	);


	// Add under name cyclicSlip
	addNamedToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicGAMGInterface,
		lduInterface,
		cyclicSlip
	);
	addNamedToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicGAMGInterface,
		Istream,
		cyclicSlip
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicGAMGInterface::cyclicGAMGInterface
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
	GAMGInterface(index, coarseInterfaces),
	neighbPatchID_
	(
		refCast<const cyclicLduInterface>(fineInterface).neighbPatchID()
	),
	owner_(refCast<const cyclicLduInterface>(fineInterface).owner()),
	forwardT_(refCast<const cyclicLduInterface>(fineInterface).forwardT()),
	reverseT_(refCast<const cyclicLduInterface>(fineInterface).reverseT())
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
		if (owner())
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


tnbLib::cyclicGAMGInterface::cyclicGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	Istream& is
)
	:
	GAMGInterface(index, coarseInterfaces, is),
	neighbPatchID_(readLabel(is)),
	owner_(readBool(is)),
	forwardT_(is),
	reverseT_(is)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicGAMGInterface::~cyclicGAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicGAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes,
	const labelUList& iF
) const
{
	const cyclicGAMGInterface& nbr = neighbPatch();
	const labelUList& nbrFaceCells = nbr.faceCells();

	tmp<labelField> tpnf(new labelField(size()));
	labelField& pnf = tpnf.ref();

	forAll(pnf, facei)
	{
		pnf[facei] = iF[nbrFaceCells[facei]];
	}

	return tpnf;
}


void tnbLib::cyclicGAMGInterface::write(Ostream& os) const
{
	GAMGInterface::write(os);
	os << token::SPACE << neighbPatchID_
		<< token::SPACE << owner_
		<< token::SPACE << forwardT_
		<< token::SPACE << reverseT_;
}


// ************************************************************************* //