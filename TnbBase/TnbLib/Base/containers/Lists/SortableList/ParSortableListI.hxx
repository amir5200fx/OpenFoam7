#pragma once
#include <SortableList.hxx>
#include <OPstream.hxx>
#include <IPstream.hxx>
#include <ListListOps.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::ParSortableList<Type>::write
(
	const List<Type>& elems,
	Ostream& os
) const
{
	os << '(';

	forAll(elems, elemI)
	{
		os << ' ' << elems[elemI];
	}
	os << ')';
}


template<class Type>
void tnbLib::ParSortableList<Type>::copyInto
(
	const List<Type>& values,
	const labelList& indices,
	const label fromProcNo,
	label& destI,
	List<taggedValue>& dest
) const
{
	forAll(values, elemI)
	{
		taggedValue& tagVal = dest[destI];

		tagVal.value() = values[elemI];
		tagVal.index() = indices[elemI];
		tagVal.procID() = fromProcNo;

		destI++;
	}
}


template<class Type>
void tnbLib::ParSortableList<Type>::getPivots
(
	const List<Type>& elems,
	List<Type>& pivots
) const
{
	pivots.setSize(Pstream::nProcs());

	label pivotPos = 0;

	forAll(pivots, pivotI)
	{
		pivots[pivotI] = elems[pivotPos];

		pivotPos += elems.size() / Pstream::nProcs();
	}
}


template<class Type>
void tnbLib::ParSortableList<Type>::checkAndSend
(
	List<Type>& values,
	labelList& indices,
	const label bufSize,
	const label destProci
) const
{
	if (destProci != Pstream::myProcNo())
	{
		values.setSize(bufSize);
		indices.setSize(bufSize);

		if (debug)
		{
			Pout << "Sending to " << destProci << " elements:" << values
				<< endl;
		}

		{
			OPstream toSlave(Pstream::commsTypes::blocking, destProci);
			toSlave << values << indices;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::ParSortableList<Type>::ParSortableList(const UList<Type>& values)
	:
	List<Type>(values),
	indices_(0),
	procs_(0)
{
	sort();
}


template<class Type>
tnbLib::ParSortableList<Type>::ParSortableList(const label size)
	:
	List<Type>(size),
	indices_(0),
	procs_(0)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::ParSortableList<Type>::sort()
{
	//
	// 0. Get total size of dataset.
	//

	label n = this->size();

	reduce(n, sumOp<label>());


	// 1. Sort list locally
	SortableList<Type> sorted(*this);

	// Collect elements at pivot points
	labelListList sortedGatherList(Pstream::nProcs());

	labelList& pivots = sortedGatherList[Pstream::myProcNo()];

	getPivots(sorted, pivots);

	if (debug)
	{
		Pout << "pivots:";
		write(pivots, Pout);
		Pout << endl;
	}


	//
	// 2. Combine pivotlist per processor onto master, sort, get pivots.
	//

	Pstream::gatherList(sortedGatherList);

	if (Pstream::master())
	{
		labelList allPivots =
			ListListOps::combine<labelList>
			(
				sortedGatherList,
				accessOp<labelList>()
				);

		SortableList<Type> sortedPivots(allPivots);

		if (debug)
		{
			Pout << "allPivots:";
			write(allPivots, Pout);
			Pout << endl;
		}

		getPivots(sortedPivots, pivots);
	}
	Pstream::scatter(pivots);

	if (debug)
	{
		Pout << "new pivots:";
		write(pivots, Pout);
		Pout << endl;
	}


	//
	// 3. Distribute pivots & distribute.
	//

	label pivotI = 1;
	label destProci = 0;

	// Buffer for my own data. Keep original index together with value.
	labelList ownValues(sorted.size());
	labelList ownIndices(sorted.size());
	label ownI = 0;

	// Buffer for sending data
	labelList sendValues(sorted.size());
	labelList sendIndices(sorted.size());
	label sendI = 0;

	forAll(sorted, sortedI)
	{
		if ((pivotI < Pstream::nProcs()) && (sorted[sortedI] > pivots[pivotI]))
		{
			checkAndSend(sendValues, sendIndices, sendI, destProci);

			// Reset buffer.
			sendValues.setSize(sorted.size());
			sendIndices.setSize(sorted.size());
			sendI = 0;

			pivotI++;
			destProci++;
		}

		if (destProci != Pstream::myProcNo())
		{
			sendValues[sendI] = sorted[sortedI];
			sendIndices[sendI] = sorted.indices()[sortedI];
			sendI++;
		}
		else
		{
			ownValues[ownI] = sorted[sortedI];
			ownIndices[ownI] = sorted.indices()[sortedI];
			ownI++;
		}
	}


	// Handle trailing send buffer
	if (sendI != 0)
	{
		checkAndSend(sendValues, sendIndices, sendI, destProci);
	}

	// Print ownValues
	ownValues.setSize(ownI);
	ownIndices.setSize(ownI);

	if (debug & 2)
	{
		Pout << "Not sending (to myself) elements "
			<< ownValues << endl;
	}

	//
	// 4. Combine pieces from all processors & sort. Use indices() from
	// SortableList to remember source processor number.
	//

	// Allocate receive buffer. Acc. to paper upper bound is 2*n/p
	// (n=total size, p=nProcs). Resize later on.
	List<taggedValue> combinedValues(2 * n / Pstream::nProcs());

	label combinedI = 0;

	for (label proci = 0; proci < Pstream::nProcs(); proci++)
	{
		if (proci == Pstream::myProcNo())
		{
			if (debug & 2)
			{
				Pout << "Copying from own:" << ownValues << endl;
			}

			// Copy ownValues,ownIndices into combined buffer
			copyInto(ownValues, ownIndices, proci, combinedI, combinedValues);
		}
		else
		{
			labelList recValues;
			labelList recIndices;

			{
				if (debug)
				{
					Pout << "Receiving from " << proci << endl;
				}

				IPstream fromSlave(Pstream::commsTypes::blocking, proci);

				fromSlave >> recValues >> recIndices;

				if (debug & 2)
				{
					Pout << "Received from " << proci
						<< " elements:" << recValues << endl;
				}
			}

			if (debug)
			{
				Pout << "Copying starting at:" << combinedI << endl;
			}
			copyInto(recValues, recIndices, proci, combinedI, combinedValues);
		}
	}
	combinedValues.setSize(combinedI);

	// Sort according to values
	tnbLib::sort(combinedValues);

	// Copy into *this
	this->setSize(combinedI);
	indices_.setSize(combinedI);
	procs_.setSize(combinedI);

	forAll(combinedValues, elemI)
	{
		this->operator[](elemI) = combinedValues[elemI].value();
		indices_[elemI] = combinedValues[elemI].index();
		procs_[elemI] = combinedValues[elemI].procID();
	}
}


// ************************************************************************* //