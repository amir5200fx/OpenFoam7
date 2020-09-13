#pragma once
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const char* const
tnbLib::bufferedAccumulator<Type>::typeName("bufferedAccumulator");


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::bufferedAccumulator<Type>::accumulateAndResetBuffer(const label b)
{
	accumulationBuffer() += (*this)[b];

	averagesTaken_++;

	(*this)[b] = Field<Type>(bufferLength(), Zero);

	bufferOffsets_[b] = 0;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::bufferedAccumulator<Type>::bufferedAccumulator()
	:
	List<Field<Type>>(),
	averagesTaken_(),
	bufferOffsets_()
{}


template<class Type>
tnbLib::bufferedAccumulator<Type>::bufferedAccumulator
(
	const label nBuffers,
	const label bufferLength,
	const label bufferingInterval
)
	:
	List<Field<Type>>(),
	averagesTaken_(),
	bufferOffsets_()
{
	setSizes
	(
		nBuffers,
		bufferLength,
		bufferingInterval
	);
}


template<class Type>
tnbLib::bufferedAccumulator<Type>::bufferedAccumulator
(
	const bufferedAccumulator<Type>& bA
)
	:
	List<Field<Type>>(static_cast<List<Field<Type>>>(bA)),
	averagesTaken_(bA.averagesTaken()),
	bufferOffsets_(bA.bufferOffsets())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::bufferedAccumulator<Type>::~bufferedAccumulator()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::bufferedAccumulator<Type>::setSizes
(
	const label nBuffers,
	const label bufferLength,
	const label bufferingInterval
)
{
	(*this).setSize(nBuffers + 1);

	forAll((*this), b)
	{
		(*this)[b] = Field<Type>(bufferLength, Zero);
	}

	averagesTaken_ = 0;

	bufferOffsets_.setSize(nBuffers);

	forAll(bufferOffsets_, bO)
	{
		bufferOffsets_[bO] = -bufferingInterval * bO - 1;
	}
}


template<class Type>
tnbLib::label tnbLib::bufferedAccumulator<Type>::addToBuffers
(
	const List<Type>& valuesToAdd
)
{
	label bufferToRefill = -1;

	for (label b = 0; b < nBuffers(); b++)
	{
		Field<Type>& buf((*this)[b]);

		label& bO = bufferOffsets_[b];

		if (bO >= 0)
		{
			buf[bO] = valuesToAdd[b];
		}

		bO++;

		if (bO == bufferLength())
		{
			accumulateAndResetBuffer(b);
		}

		if (bO == 0)
		{
			if (bufferToRefill != -1)
			{
				FatalErrorInFunction
					<< "More than one bufferedAccumulator accumulation "
					<< "buffer filled at once, this is considered an error."
					<< abort(FatalError);
			}

			bufferToRefill = b;
		}
	}

	return bufferToRefill;
}


template<class Type>
tnbLib::Field<Type> tnbLib::bufferedAccumulator<Type>::averaged() const
{
	if (averagesTaken_)
	{
		Field<Type> bA = accumulationBuffer() / averagesTaken_;

		return bA;
	}
	else
	{
		WarningInFunction
			<< "Averaged correlation function requested but averagesTaken = "
			<< averagesTaken_
			<< ". Returning empty field."
			<< endl;

		return Field<Type>(bufferLength(), Zero);
	}
}


template<class Type>
void tnbLib::bufferedAccumulator<Type>::resetAveraging()
{
	accumulationBuffer() = Field<Type>(bufferLength(), Zero);

	averagesTaken_ = 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::bufferedAccumulator<Type>::operator=
(
	const bufferedAccumulator<Type>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	List<Field<Type>>::operator=(rhs);

	averagesTaken_ = rhs.averagesTaken();

	bufferOffsets_ = rhs.bufferOffsets();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //