#pragma once
#include <demandDrivenData.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	coupledFvPatchField<Type>(p, iF),
	procPatch_(refCast<const processorFvPatch>(p)),
	sendBuf_(0),
	receiveBuf_(0),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(0),
	scalarReceiveBuf_(0)
{}


template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& f
)
	:
	coupledFvPatchField<Type>(p, iF, f),
	procPatch_(refCast<const processorFvPatch>(p)),
	sendBuf_(0),
	receiveBuf_(0),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(0),
	scalarReceiveBuf_(0)
{}


template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	coupledFvPatchField<Type>(p, iF, dict, dict.found("value")),
	procPatch_(refCast<const processorFvPatch>(p)),
	sendBuf_(0),
	receiveBuf_(0),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(0),
	scalarReceiveBuf_(0)
{
	if (!isA<processorFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "\n    patch type '" << p.type()
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}

	// If the value is not supplied set to the internal field
	if (!dict.found("value"))
	{
		fvPatchField<Type>::operator=(this->patchInternalField());
	}
}


template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const processorFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	coupledFvPatchField<Type>(ptf, p, iF, mapper),
	procPatch_(refCast<const processorFvPatch>(p)),
	sendBuf_(0),
	receiveBuf_(0),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(0),
	scalarReceiveBuf_(0)
{
	if (!isA<processorFvPatch>(this->patch()))
	{
		FatalErrorInFunction
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}
	if (debug && !ptf.ready())
	{
		FatalErrorInFunction
			<< "On patch " << procPatch_.name() << " outstanding request."
			<< abort(FatalError);
	}
}


template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const processorFvPatchField<Type>& ptf
)
	:
	processorLduInterfaceField(),
	coupledFvPatchField<Type>(ptf),
	procPatch_(refCast<const processorFvPatch>(ptf.patch())),
	sendBuf_(move(ptf.sendBuf_)),
	receiveBuf_(move(ptf.receiveBuf_)),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(move(ptf.scalarSendBuf_)),
	scalarReceiveBuf_(move(ptf.scalarReceiveBuf_))
{
	if (debug && !ptf.ready())
	{
		FatalErrorInFunction
			<< "On patch " << procPatch_.name() << " outstanding request."
			<< abort(FatalError);
	}
}


template<class Type>
tnbLib::processorFvPatchField<Type>::processorFvPatchField
(
	const processorFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	coupledFvPatchField<Type>(ptf, iF),
	procPatch_(refCast<const processorFvPatch>(ptf.patch())),
	sendBuf_(0),
	receiveBuf_(0),
	outstandingSendRequest_(-1),
	outstandingRecvRequest_(-1),
	scalarSendBuf_(0),
	scalarReceiveBuf_(0)
{
	if (debug && !ptf.ready())
	{
		FatalErrorInFunction
			<< "On patch " << procPatch_.name() << " outstanding request."
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorFvPatchField<Type>::~processorFvPatchField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::processorFvPatchField<Type>::patchNeighbourField() const
{
	if (debug && !this->ready())
	{
		FatalErrorInFunction
			<< "On patch " << procPatch_.name()
			<< " outstanding request."
			<< abort(FatalError);
	}
	return *this;
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::initEvaluate
(
	const Pstream::commsTypes commsType
)
{
	if (Pstream::parRun())
	{
		this->patchInternalField(sendBuf_);

		if
			(
				commsType == Pstream::commsTypes::nonBlocking
				&& !Pstream::floatTransfer
				)
		{
			// Fast path. Receive into *this
			this->setSize(sendBuf_.size());
			outstandingRecvRequest_ = UPstream::nRequests();
			UIPstream::read
			(
				Pstream::commsTypes::nonBlocking,
				procPatch_.neighbProcNo(),
				reinterpret_cast<char*>(this->begin()),
				this->byteSize(),
				procPatch_.tag(),
				procPatch_.comm()
			);

			outstandingSendRequest_ = UPstream::nRequests();
			UOPstream::write
			(
				Pstream::commsTypes::nonBlocking,
				procPatch_.neighbProcNo(),
				reinterpret_cast<const char*>(sendBuf_.begin()),
				this->byteSize(),
				procPatch_.tag(),
				procPatch_.comm()
			);
		}
		else
		{
			procPatch_.compressedSend(commsType, sendBuf_);
		}
	}
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes commsType
)
{
	if (Pstream::parRun())
	{
		if
			(
				commsType == Pstream::commsTypes::nonBlocking
				&& !Pstream::floatTransfer
				)
		{
			// Fast path. Received into *this

			if
				(
					outstandingRecvRequest_ >= 0
					&& outstandingRecvRequest_ < Pstream::nRequests()
					)
			{
				UPstream::waitRequest(outstandingRecvRequest_);
			}
			outstandingSendRequest_ = -1;
			outstandingRecvRequest_ = -1;
		}
		else
		{
			procPatch_.compressedReceive<Type>(commsType, *this);
		}

		if (doTransform())
		{
			transform(*this, procPatch_.forwardT(), *this);
		}
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::processorFvPatchField<Type>::snGrad
(
	const scalarField& deltaCoeffs
) const
{
	return deltaCoeffs * (*this - this->patchInternalField());
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::initInterfaceMatrixUpdate
(
	scalarField&,
	const scalarField& psiInternal,
	const scalarField&,
	const direction,
	const Pstream::commsTypes commsType
) const
{
	this->patch().patchInternalField(psiInternal, scalarSendBuf_);

	if
		(
			commsType == Pstream::commsTypes::nonBlocking
			&& !Pstream::floatTransfer
			)
	{
		// Fast path.
		if (debug && !this->ready())
		{
			FatalErrorInFunction
				<< "On patch " << procPatch_.name()
				<< " outstanding request."
				<< abort(FatalError);
		}


		scalarReceiveBuf_.setSize(scalarSendBuf_.size());
		outstandingRecvRequest_ = UPstream::nRequests();
		UIPstream::read
		(
			Pstream::commsTypes::nonBlocking,
			procPatch_.neighbProcNo(),
			reinterpret_cast<char*>(scalarReceiveBuf_.begin()),
			scalarReceiveBuf_.byteSize(),
			procPatch_.tag(),
			procPatch_.comm()
		);

		outstandingSendRequest_ = UPstream::nRequests();
		UOPstream::write
		(
			Pstream::commsTypes::nonBlocking,
			procPatch_.neighbProcNo(),
			reinterpret_cast<const char*>(scalarSendBuf_.begin()),
			scalarSendBuf_.byteSize(),
			procPatch_.tag(),
			procPatch_.comm()
		);
	}
	else
	{
		procPatch_.compressedSend(commsType, scalarSendBuf_);
	}

	const_cast<processorFvPatchField<Type>&>(*this).updatedMatrix() = false;
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::updateInterfaceMatrix
(
	scalarField& result,
	const scalarField&,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType
) const
{
	if (this->updatedMatrix())
	{
		return;
	}

	const labelUList& faceCells = this->patch().faceCells();

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
			procPatch_.compressedReceive<scalar>(commsType, this->size())()
		);

		// Transform according to the transformation tensor
		transformCoupleField(pnf, cmpt);

		// Multiply the field by coefficients and add into the result
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
		}
	}

	const_cast<processorFvPatchField<Type>&>(*this).updatedMatrix() = true;
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::initInterfaceMatrixUpdate
(
	Field<Type>&,
	const Field<Type>& psiInternal,
	const scalarField&,
	const Pstream::commsTypes commsType
) const
{
	this->patch().patchInternalField(psiInternal, sendBuf_);

	if
		(
			commsType == Pstream::commsTypes::nonBlocking
			&& !Pstream::floatTransfer
			)
	{
		// Fast path.
		if (debug && !this->ready())
		{
			FatalErrorInFunction
				<< "On patch " << procPatch_.name()
				<< " outstanding request."
				<< abort(FatalError);
		}


		receiveBuf_.setSize(sendBuf_.size());
		outstandingRecvRequest_ = UPstream::nRequests();
		IPstream::read
		(
			Pstream::commsTypes::nonBlocking,
			procPatch_.neighbProcNo(),
			reinterpret_cast<char*>(receiveBuf_.begin()),
			receiveBuf_.byteSize(),
			procPatch_.tag(),
			procPatch_.comm()
		);

		outstandingSendRequest_ = UPstream::nRequests();
		OPstream::write
		(
			Pstream::commsTypes::nonBlocking,
			procPatch_.neighbProcNo(),
			reinterpret_cast<const char*>(sendBuf_.begin()),
			sendBuf_.byteSize(),
			procPatch_.tag(),
			procPatch_.comm()
		);
	}
	else
	{
		procPatch_.compressedSend(commsType, sendBuf_);
	}

	const_cast<processorFvPatchField<Type>&>(*this).updatedMatrix() = false;
}


template<class Type>
void tnbLib::processorFvPatchField<Type>::updateInterfaceMatrix
(
	Field<Type>& result,
	const Field<Type>&,
	const scalarField& coeffs,
	const Pstream::commsTypes commsType
) const
{
	if (this->updatedMatrix())
	{
		return;
	}

	const labelUList& faceCells = this->patch().faceCells();

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

		// Consume straight from receiveBuf_

		// Transform according to the transformation tensor
		transformCoupleField(receiveBuf_);

		// Multiply the field by coefficients and add into the result
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * receiveBuf_[elemI];
		}
	}
	else
	{
		Field<Type> pnf
		(
			procPatch_.compressedReceive<Type>(commsType, this->size())()
		);

		// Transform according to the transformation tensor
		transformCoupleField(pnf);

		// Multiply the field by coefficients and add into the result
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
		}
	}

	const_cast<processorFvPatchField<Type>&>(*this).updatedMatrix() = true;
}


template<class Type>
bool tnbLib::processorFvPatchField<Type>::ready() const
{
	if
		(
			outstandingSendRequest_ >= 0
			&& outstandingSendRequest_ < Pstream::nRequests()
			)
	{
		bool finished = UPstream::finishedRequest(outstandingSendRequest_);
		if (!finished)
		{
			return false;
		}
	}
	outstandingSendRequest_ = -1;

	if
		(
			outstandingRecvRequest_ >= 0
			&& outstandingRecvRequest_ < Pstream::nRequests()
			)
	{
		bool finished = UPstream::finishedRequest(outstandingRecvRequest_);
		if (!finished)
		{
			return false;
		}
	}
	outstandingRecvRequest_ = -1;

	return true;
}


// ************************************************************************* //