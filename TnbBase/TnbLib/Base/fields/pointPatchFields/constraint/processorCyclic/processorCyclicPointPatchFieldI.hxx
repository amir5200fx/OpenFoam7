#pragma once
#include <transformField.hxx>
#include <processorPolyPatch.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorCyclicPointPatchField<Type>::processorCyclicPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	coupledPointPatchField<Type>(p, iF),
	procPatch_(refCast<const processorCyclicPointPatch>(p)),
	receiveBuf_(0)
{}


template<class Type>
tnbLib::processorCyclicPointPatchField<Type>::processorCyclicPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	coupledPointPatchField<Type>(p, iF, dict),
	procPatch_(refCast<const processorCyclicPointPatch>(p)),
	receiveBuf_(0)
{}


template<class Type>
tnbLib::processorCyclicPointPatchField<Type>::processorCyclicPointPatchField
(
	const processorCyclicPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	coupledPointPatchField<Type>(ptf, p, iF, mapper),
	procPatch_(refCast<const processorCyclicPointPatch>(ptf.patch())),
	receiveBuf_(0)
{}


template<class Type>
tnbLib::processorCyclicPointPatchField<Type>::processorCyclicPointPatchField
(
	const processorCyclicPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	coupledPointPatchField<Type>(ptf, iF),
	procPatch_(refCast<const processorCyclicPointPatch>(ptf.patch())),
	receiveBuf_(0)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::processorCyclicPointPatchField<Type>::~processorCyclicPointPatchField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::processorCyclicPointPatchField<Type>::initSwapAddSeparated
(
	const Pstream::commsTypes commsType,
	Field<Type>& pField
) const
{
	if (Pstream::parRun())
	{
		// Get internal field into correct order for opposite side
		Field<Type> pf
		(
			this->patchInternalField
			(
				pField,
				procPatch_.reverseMeshPoints()
			)
		);

		if (commsType == Pstream::commsTypes::nonBlocking)
		{
			receiveBuf_.setSize(pf.size());
			IPstream::read
			(
				commsType,
				procPatch_.neighbProcNo(),
				reinterpret_cast<char*>(receiveBuf_.begin()),
				receiveBuf_.byteSize(),
				procPatch_.tag(),
				procPatch_.comm()
			);
		}
		OPstream::write
		(
			commsType,
			procPatch_.neighbProcNo(),
			reinterpret_cast<const char*>(pf.begin()),
			pf.byteSize(),
			procPatch_.tag(),
			procPatch_.comm()
		);
	}
}


template<class Type>
void tnbLib::processorCyclicPointPatchField<Type>::swapAddSeparated
(
	const Pstream::commsTypes commsType,
	Field<Type>& pField
) const
{
	if (Pstream::parRun())
	{
		// If nonblocking data has already been received into receiveBuf_
		if (commsType != Pstream::commsTypes::nonBlocking)
		{
			receiveBuf_.setSize(this->size());
			IPstream::read
			(
				commsType,
				procPatch_.neighbProcNo(),
				reinterpret_cast<char*>(receiveBuf_.begin()),
				receiveBuf_.byteSize(),
				procPatch_.tag(),
				procPatch_.comm()
			);
		}

		if (doTransform())
		{
			const processorCyclicPolyPatch& ppp =
				procPatch_.procCyclicPolyPatch();
			const tensor& forwardT = ppp.forwardT()[0];

			transform(receiveBuf_, forwardT, receiveBuf_);
		}

		// All points are separated
		this->addToInternalField(pField, receiveBuf_);
	}
}


// ************************************************************************* //