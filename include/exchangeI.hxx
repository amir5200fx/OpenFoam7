#pragma once
#include <contiguous.hxx>
#include <PstreamCombineReduceOps.hxx>
#include <UPstream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Container, class T>
void tnbLib::Pstream::exchange
(
	const UList<Container>& sendBufs,
	const labelUList& recvSizes,
	List<Container>& recvBufs,
	const int tag,
	const label comm,
	const bool block
)
{
	if (!contiguous<T>())
	{
		FatalErrorInFunction
			<< "Continuous data only." << sizeof(T) << tnbLib::abort(FatalError);
	}

	if (sendBufs.size() != UPstream::nProcs(comm))
	{
		FatalErrorInFunction
			<< "Size of list " << sendBufs.size()
			<< " does not equal the number of processors "
			<< UPstream::nProcs(comm)
			<< tnbLib::abort(FatalError);
	}

	recvBufs.setSize(sendBufs.size());

	if (UPstream::parRun() && UPstream::nProcs(comm) > 1)
	{
		label startOfRequests = Pstream::nRequests();

		// Set up receives
		// ~~~~~~~~~~~~~~~

		forAll(recvSizes, proci)
		{
			label nRecv = recvSizes[proci];

			if (proci != Pstream::myProcNo(comm) && nRecv > 0)
			{
				recvBufs[proci].setSize(nRecv);
				UIPstream::read
				(
					UPstream::commsTypes::nonBlocking,
					proci,
					reinterpret_cast<char*>(recvBufs[proci].begin()),
					nRecv * sizeof(T),
					tag,
					comm
				);
			}
		}


		// Set up sends
		// ~~~~~~~~~~~~

		forAll(sendBufs, proci)
		{
			if (proci != Pstream::myProcNo(comm) && sendBufs[proci].size() > 0)
			{
				if
					(
						!UOPstream::write
						(
							UPstream::commsTypes::nonBlocking,
							proci,
							reinterpret_cast<const char*>(sendBufs[proci].begin()),
							sendBufs[proci].size() * sizeof(T),
							tag,
							comm
						)
						)
				{
					FatalErrorInFunction
						<< "Cannot send outgoing message. "
						<< "to:" << proci << " nBytes:"
						<< label(sendBufs[proci].size() * sizeof(T))
						<< tnbLib::abort(FatalError);
				}
			}
		}


		// Wait for all to finish
		// ~~~~~~~~~~~~~~~~~~~~~~

		if (block)
		{
			Pstream::waitRequests(startOfRequests);
		}
	}

	// Do myself
	recvBufs[Pstream::myProcNo(comm)] = sendBufs[Pstream::myProcNo(comm)];
}


template<class Container>
void tnbLib::Pstream::exchangeSizes
(
	const Container& sendBufs,
	labelList& recvSizes,
	const label comm
)
{
	if (sendBufs.size() != UPstream::nProcs(comm))
	{
		FatalErrorInFunction
			<< "Size of container " << sendBufs.size()
			<< " does not equal the number of processors "
			<< UPstream::nProcs(comm)
			<< tnbLib::abort(FatalError);
	}

	labelList sendSizes(sendBufs.size());
	forAll(sendBufs, proci)
	{
		sendSizes[proci] = sendBufs[proci].size();
	}
	recvSizes.setSize(sendSizes.size());
	allToAll(sendSizes, recvSizes, comm);
}


template<class Container, class T>
void tnbLib::Pstream::exchange
(
	const UList<Container>& sendBufs,
	List<Container>& recvBufs,
	const int tag,
	const label comm,
	const bool block
)
{
	labelList recvSizes;
	exchangeSizes(sendBufs, recvSizes, comm);

	exchange<Container, T>(sendBufs, recvSizes, recvBufs, tag, comm, block);
}


// ************************************************************************* //