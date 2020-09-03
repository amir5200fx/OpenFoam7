#pragma once
#include <contiguous.hxx> // added by amir
#include <IPstream.hxx> // added by amir
#include <OPstream.hxx> // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::globalIndex::gather
(
	const labelUList& off,
	const label comm,
	const labelList& procIDs,
	const UList<Type>& fld,
	List<Type>& allFld,
	const int tag,
	const Pstream::commsTypes commsType
)
{
	if (Pstream::myProcNo(comm) == procIDs[0])
	{
		allFld.setSize(off.last());

		// Assign my local data
		SubList<Type>(allFld, fld.size(), 0) = fld;

		if
			(
				commsType == Pstream::commsTypes::scheduled
				|| commsType == Pstream::commsTypes::blocking
				)
		{
			for (label i = 1; i < procIDs.size(); i++)
			{
				SubList<Type> procSlot(allFld, off[i + 1] - off[i], off[i]);

				if (contiguous<Type>())
				{
					IPstream::read
					(
						commsType,
						procIDs[i],
						reinterpret_cast<char*>(procSlot.begin()),
						procSlot.byteSize(),
						tag,
						comm
					);
				}
				else
				{
					IPstream fromSlave
					(
						commsType,
						procIDs[i],
						0,
						tag,
						comm
					);
					fromSlave >> procSlot;
				}
			}
		}
		else
		{
			// nonBlocking

			if (!contiguous<Type>())
			{
				FatalErrorInFunction
					<< "nonBlocking not supported for non-contiguous data"
					<< exit(FatalError);
			}

			label startOfRequests = Pstream::nRequests();

			// Set up reads
			for (label i = 1; i < procIDs.size(); i++)
			{
				SubList<Type> procSlot(allFld, off[i + 1] - off[i], off[i]);

				IPstream::read
				(
					commsType,
					procIDs[i],
					reinterpret_cast<char*>(procSlot.begin()),
					procSlot.byteSize(),
					tag,
					comm
				);
			}

			// Wait for all to finish
			Pstream::waitRequests(startOfRequests);
		}
	}
	else
	{
		if
			(
				commsType == Pstream::commsTypes::scheduled
				|| commsType == Pstream::commsTypes::blocking
				)
		{
			if (contiguous<Type>())
			{
				OPstream::write
				(
					commsType,
					procIDs[0],
					reinterpret_cast<const char*>(fld.begin()),
					fld.byteSize(),
					tag,
					comm
				);
			}
			else
			{
				OPstream toMaster
				(
					commsType,
					procIDs[0],
					0,
					tag,
					comm
				);
				toMaster << fld;
			}
		}
		else
		{
			// nonBlocking

			if (!contiguous<Type>())
			{
				FatalErrorInFunction
					<< "nonBlocking not supported for non-contiguous data"
					<< exit(FatalError);
			}

			label startOfRequests = Pstream::nRequests();

			// Set up write
			OPstream::write
			(
				commsType,
				procIDs[0],
				reinterpret_cast<const char*>(fld.begin()),
				fld.byteSize(),
				tag,
				comm
			);

			// Wait for all to finish
			Pstream::waitRequests(startOfRequests);
		}
	}
}


template<class Type>
void tnbLib::globalIndex::gather
(
	const labelUList& off,
	const label comm,
	const labelList& procIDs,
	List<Type>& fld,
	const int tag,
	const Pstream::commsTypes commsType
)
{
	List<Type> allFld;

	gather(off, comm, procIDs, fld, allFld, tag, commsType);

	if (Pstream::myProcNo(comm) == procIDs[0])
	{
		fld.transfer(allFld);
	}
}


template<class Type>
void tnbLib::globalIndex::scatter
(
	const labelUList& off,
	const label comm,
	const labelList& procIDs,
	const UList<Type>& allFld,
	UList<Type>& fld,
	const int tag,
	const Pstream::commsTypes commsType
)
{
	if (Pstream::myProcNo(comm) == procIDs[0])
	{
		fld.deepCopy(SubList<Type>(allFld, off[1] - off[0]));

		if
			(
				commsType == Pstream::commsTypes::scheduled
				|| commsType == Pstream::commsTypes::blocking
				)
		{
			for (label i = 1; i < procIDs.size(); i++)
			{
				const SubList<Type> procSlot
				(
					allFld,
					off[i + 1] - off[i],
					off[i]
				);

				if (contiguous<Type>())
				{
					OPstream::write
					(
						commsType,
						procIDs[i],
						reinterpret_cast<const char*>(procSlot.begin()),
						procSlot.byteSize(),
						tag,
						comm
					);
				}
				else
				{
					OPstream toSlave
					(
						commsType,
						procIDs[i],
						0,
						tag,
						comm
					);
					toSlave << procSlot;
				}
			}
		}
		else
		{
			// nonBlocking

			if (!contiguous<Type>())
			{
				FatalErrorInFunction
					<< "nonBlocking not supported for non-contiguous data"
					<< exit(FatalError);
			}

			label startOfRequests = Pstream::nRequests();

			// Set up writes
			for (label i = 1; i < procIDs.size(); i++)
			{
				const SubList<Type> procSlot
				(
					allFld,
					off[i + 1] - off[i],
					off[i]
				);

				OPstream::write
				(
					commsType,
					procIDs[i],
					reinterpret_cast<const char*>(procSlot.begin()),
					procSlot.byteSize(),
					tag,
					comm
				);
			}

			// Wait for all to finish
			Pstream::waitRequests(startOfRequests);
		}
	}
	else
	{
		if
			(
				commsType == Pstream::commsTypes::scheduled
				|| commsType == Pstream::commsTypes::blocking
				)
		{
			if (contiguous<Type>())
			{
				IPstream::read
				(
					commsType,
					procIDs[0],
					reinterpret_cast<char*>(fld.begin()),
					fld.byteSize(),
					tag,
					comm
				);
			}
			else
			{
				IPstream fromMaster
				(
					commsType,
					procIDs[0],
					0,
					tag,
					comm
				);
				fromMaster >> fld;
			}
		}
		else
		{
			// nonBlocking

			if (!contiguous<Type>())
			{
				FatalErrorInFunction
					<< "nonBlocking not supported for non-contiguous data"
					<< exit(FatalError);
			}

			label startOfRequests = Pstream::nRequests();

			// Set up read
			IPstream::read
			(
				commsType,
				procIDs[0],
				reinterpret_cast<char*>(fld.begin()),
				fld.byteSize(),
				tag,
				comm
			);

			// Wait for all to finish
			Pstream::waitRequests(startOfRequests);
		}
	}
}


// ************************************************************************* //