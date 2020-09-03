#pragma once
#include <IPstream.hxx>
#include <OPstream.hxx>

// * * * * * * * * * * * * * * * Member Functions * * *  * * * * * * * * * * //

template<class Type>
void tnbLib::processorLduInterface::send
(
	const Pstream::commsTypes commsType,
	const UList<Type>& f
) const
{
	label nBytes = f.byteSize();

	if
		(
			commsType == Pstream::commsTypes::blocking
			|| commsType == Pstream::commsTypes::scheduled
			)
	{
		OPstream::write
		(
			commsType,
			neighbProcNo(),
			reinterpret_cast<const char*>(f.begin()),
			nBytes,
			tag(),
			comm()
		);
	}
	else if (commsType == Pstream::commsTypes::nonBlocking)
	{
		resizeBuf(receiveBuf_, nBytes);

		IPstream::read
		(
			commsType,
			neighbProcNo(),
			receiveBuf_.begin(),
			nBytes,
			tag(),
			comm()
		);

		resizeBuf(sendBuf_, nBytes);
		memcpy(sendBuf_.begin(), f.begin(), nBytes);

		OPstream::write
		(
			commsType,
			neighbProcNo(),
			sendBuf_.begin(),
			nBytes,
			tag(),
			comm()
		);
	}
	else
	{
		FatalErrorInFunction
			<< "Unsupported communications type " << int(commsType)
			<< exit(FatalError);
	}
}


template<class Type>
void tnbLib::processorLduInterface::receive
(
	const Pstream::commsTypes commsType,
	UList<Type>& f
) const
{
	if
		(
			commsType == Pstream::commsTypes::blocking
			|| commsType == Pstream::commsTypes::scheduled
			)
	{
		IPstream::read
		(
			commsType,
			neighbProcNo(),
			reinterpret_cast<char*>(f.begin()),
			f.byteSize(),
			tag(),
			comm()
		);
	}
	else if (commsType == Pstream::commsTypes::nonBlocking)
	{
		memcpy(f.begin(), receiveBuf_.begin(), f.byteSize());
	}
	else
	{
		FatalErrorInFunction
			<< "Unsupported communications type " << int(commsType)
			<< exit(FatalError);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::processorLduInterface::receive
(
	const Pstream::commsTypes commsType,
	const label size
) const
{
	tmp<Field<Type>> tf(new Field<Type>(size));
	receive(commsType, tf.ref());
	return tf;
}


template<class Type>
void tnbLib::processorLduInterface::compressedSend
(
	const Pstream::commsTypes commsType,
	const UList<Type>& f
) const
{
	if (sizeof(scalar) != sizeof(float) && Pstream::floatTransfer && f.size())
	{
		static const label nCmpts = sizeof(Type) / sizeof(scalar);
		label nm1 = (f.size() - 1)*nCmpts;
		label nlast = sizeof(Type) / sizeof(float);
		label nFloats = nm1 + nlast;
		label nBytes = nFloats * sizeof(float);

		const scalar *sArray = reinterpret_cast<const scalar*>(f.begin());
		const scalar *slast = &sArray[nm1];
		resizeBuf(sendBuf_, nBytes);
		float *fArray = reinterpret_cast<float*>(sendBuf_.begin());

		for (label i = 0; i < nm1; i++)
		{
			fArray[i] = sArray[i] - slast[i%nCmpts];
		}

		reinterpret_cast<Type&>(fArray[nm1]) = f.last();

		if
			(
				commsType == Pstream::commsTypes::blocking
				|| commsType == Pstream::commsTypes::scheduled
				)
		{
			OPstream::write
			(
				commsType,
				neighbProcNo(),
				sendBuf_.begin(),
				nBytes,
				tag(),
				comm()
			);
		}
		else if (commsType == Pstream::commsTypes::nonBlocking)
		{
			resizeBuf(receiveBuf_, nBytes);

			IPstream::read
			(
				commsType,
				neighbProcNo(),
				receiveBuf_.begin(),
				nBytes,
				tag(),
				comm()
			);

			OPstream::write
			(
				commsType,
				neighbProcNo(),
				sendBuf_.begin(),
				nBytes,
				tag(),
				comm()
			);
		}
		else
		{
			FatalErrorInFunction
				<< "Unsupported communications type " << int(commsType)
				<< exit(FatalError);
		}
	}
	else
	{
		this->send(commsType, f);
	}
}

template<class Type>
void tnbLib::processorLduInterface::compressedReceive
(
	const Pstream::commsTypes commsType,
	UList<Type>& f
) const
{
	if (sizeof(scalar) != sizeof(float) && Pstream::floatTransfer && f.size())
	{
		static const label nCmpts = sizeof(Type) / sizeof(scalar);
		label nm1 = (f.size() - 1)*nCmpts;
		label nlast = sizeof(Type) / sizeof(float);
		label nFloats = nm1 + nlast;
		label nBytes = nFloats * sizeof(float);

		if
			(
				commsType == Pstream::commsTypes::blocking
				|| commsType == Pstream::commsTypes::scheduled
				)
		{
			resizeBuf(receiveBuf_, nBytes);

			IPstream::read
			(
				commsType,
				neighbProcNo(),
				receiveBuf_.begin(),
				nBytes,
				tag(),
				comm()
			);
		}
		else if (commsType != Pstream::commsTypes::nonBlocking)
		{
			FatalErrorInFunction
				<< "Unsupported communications type " << int(commsType)
				<< exit(FatalError);
		}

		const float *fArray =
			reinterpret_cast<const float*>(receiveBuf_.begin());
		f.last() = reinterpret_cast<const Type&>(fArray[nm1]);
		scalar *sArray = reinterpret_cast<scalar*>(f.begin());
		const scalar *slast = &sArray[nm1];

		for (label i = 0; i < nm1; i++)
		{
			sArray[i] = fArray[i] + slast[i%nCmpts];
		}
	}
	else
	{
		this->receive<Type>(commsType, f);
	}
}

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::processorLduInterface::compressedReceive
(
	const Pstream::commsTypes commsType,
	const label size
) const
{
	tmp<Field<Type>> tf(new Field<Type>(size));
	compressedReceive(commsType, tf.ref());
	return tf;
}


// ************************************************************************* //