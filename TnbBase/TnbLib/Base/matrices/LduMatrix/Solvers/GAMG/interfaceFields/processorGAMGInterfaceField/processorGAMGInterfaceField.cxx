#include <processorGAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

#include <IPstream.hxx>  // added by amir
#include <OPstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorGAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		processorGAMGInterfaceField,
		lduInterface
	);
	addToRunTimeSelectionTable
	(
		GAMGInterfaceField,
		processorGAMGInterfaceField,
		lduInterfaceField
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorGAMGInterfaceField::processorGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const lduInterfaceField& fineInterface
)
	:
	GAMGInterfaceField(GAMGCp, fineInterface),
	procInterface_(refCast<const processorGAMGInterface>(GAMGCp)),
	doTransform_(false),
	rank_(0)
{
	const processorLduInterfaceField& p =
		refCast<const processorLduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


tnbLib::processorGAMGInterfaceField::processorGAMGInterfaceField
(
	const GAMGInterface& GAMGCp,
	const bool doTransform,
	const int rank
)
	:
	GAMGInterfaceField(GAMGCp, doTransform, rank),
	procInterface_(refCast<const processorGAMGInterface>(GAMGCp)),
	doTransform_(doTransform),
	rank_(rank)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorGAMGInterfaceField::~processorGAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::processorGAMGInterfaceField::initInterfaceMatrixUpdate
(
	scalarField&,
	const scalarField& psiInternal,
	const scalarField&,
	const direction,
	const Pstream::commsTypes commsType
) const
{
	procInterface_.interfaceInternalField(psiInternal, scalarSendBuf_);

	if
		(
			commsType == Pstream::commsTypes::nonBlocking
			&& !Pstream::floatTransfer
			)
	{
		// Fast path.
		scalarReceiveBuf_.setSize(scalarSendBuf_.size());
		outstandingRecvRequest_ = UPstream::nRequests();
		IPstream::read
		(
			Pstream::commsTypes::nonBlocking,
			procInterface_.neighbProcNo(),
			reinterpret_cast<char*>(scalarReceiveBuf_.begin()),
			scalarReceiveBuf_.byteSize(),
			procInterface_.tag(),
			comm()
		);

		outstandingSendRequest_ = UPstream::nRequests();
		OPstream::write
		(
			Pstream::commsTypes::nonBlocking,
			procInterface_.neighbProcNo(),
			reinterpret_cast<const char*>(scalarSendBuf_.begin()),
			scalarSendBuf_.byteSize(),
			procInterface_.tag(),
			comm()
		);
	}
	else
	{
		procInterface_.compressedSend(commsType, scalarSendBuf_);
	}

	const_cast<processorGAMGInterfaceField&>(*this).updatedMatrix() = false;
}


void tnbLib::processorGAMGInterfaceField::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField&,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType
) const
{
	if (updatedMatrix())
	{
		return;
	}

	const labelUList& faceCells = procInterface_.faceCells();

	if
		(
			commsType == Pstream::commsTypes::nonBlocking
			&& !Pstream::floatTransfer
			)
	{
		// Fast path.
		if
			(
				outstandingRecvRequest_ >= 0
				&& outstandingRecvRequest_ < Pstream::nRequests()
				)
		{
			UPstream::waitRequest(outstandingRecvRequest_);
		}
		// Recv finished so assume sending finished as well.
		outstandingSendRequest_ = -1;
		outstandingRecvRequest_ = -1;

		// Consume straight from scalarReceiveBuf_

		// Transform according to the transformation tensor
		transformCoupleField(scalarReceiveBuf_, cmpt);

		// Multiply the field by coefficients and add into the result
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * scalarReceiveBuf_[elemI];
		}
	}
	else
	{
		scalarField pnf
		(
			procInterface_.compressedReceive<scalar>(commsType, coeffs.size())
		);
		transformCoupleField(pnf, cmpt);

		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
		}
	}

	const_cast<processorGAMGInterfaceField&>(*this).updatedMatrix() = true;
}


// ************************************************************************* //