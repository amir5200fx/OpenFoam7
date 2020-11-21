#pragma once
#ifndef _UPstream_Header
#define _UPstream_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::UPstream

Description
	Inter-processor communications stream

SourceFiles
	UPstream.C
	UPstreamCommsStruct.C
	gatherScatter.C
	combineGatherScatter.C
	gatherScatterList.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <DynamicList.hxx>
//#include <HashTable.hxx>
#include <tnbString.hxx>
#include <NamedEnum.hxx>
#include <ListOps.hxx>
#include <LIFOStack.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward Declarations
	template<class T, unsigned SizeInc = 0, unsigned SizeMult = 2, unsigned SizeDiv = 1>
	class DynamicList;

	template<class T, class Key, class Hash> class HashTable;

	/*---------------------------------------------------------------------------*\
							  Class UPstream Declaration
	\*---------------------------------------------------------------------------*/

	class UPstream
	{

	public:

		//- Types of communications
		enum class commsTypes
		{
			blocking,
			scheduled,
			nonBlocking
		};

		static FoamBase_EXPORT const NamedEnum<commsTypes, 3> commsTypeNames;

		// Public classes

			//- Structure for communicating between processors
		class commsStruct
		{
			// Private Data

				//- procID of above processor
			label above_;

			//- procIDs of processors directly below me
			labelList below_;

			//- procIDs of all processors below (so not just directly below)
			labelList allBelow_;

			//- procIDs of all processors not below. (inverse set of
			//  allBelow_ and minus myProcNo)
			labelList allNotBelow_;


		public:

			// Constructors

				//- Construct null
			FoamBase_EXPORT commsStruct();

			//- Construct from components
			FoamBase_EXPORT commsStruct
			(
				const label,
				const labelList&,
				const labelList&,
				const labelList&
			);

			//- Construct from components; construct allNotBelow_
			FoamBase_EXPORT commsStruct
			(
				const label nProcs,
				const label myProcID,
				const label,
				const labelList&,
				const labelList&
			);


			// Member Functions

				// Access

			label above() const
			{
				return above_;
			}

			const labelList& below() const
			{
				return below_;
			}

			const labelList& allBelow() const
			{
				return allBelow_;
			}

			const labelList& allNotBelow() const
			{
				return allNotBelow_;
			}


			// Member Operators

			FoamBase_EXPORT bool operator==(const commsStruct&) const;

			FoamBase_EXPORT bool operator!=(const commsStruct&) const;


			// Ostream Operator

			friend Ostream& operator<<(Ostream&, const commsStruct&);
		};


		//- combineReduce operator for lists. Used for counting.
		class listEq
		{

		public:

			template<class T>
			void operator()(T& x, const T& y) const
			{
				forAll(y, i)
				{
					if (y[i].size())
					{
						x[i] = y[i];
					}
				}
			}
		};


	private:

		// Private Data

			//- By default this is not a parallel run
		static FoamBase_EXPORT bool parRun_;

		//- Have support for threads?
		static FoamBase_EXPORT bool haveThreads_;

		//- Standard transfer message type
		static FoamBase_EXPORT int msgType_;

		// Communicator specific data

		//- Free communicators
		static FoamBase_EXPORT LIFOStack<label> freeComms_;

		//- My processor number
		static FoamBase_EXPORT DynamicList<int> myProcNo_;

		//- List of process IDs
		static FoamBase_EXPORT DynamicList<List<int>> procIDs_;

		//- Parent communicator
		static FoamBase_EXPORT DynamicList<label> parentCommunicator_;

		//- Linear communication schedule
		static FoamBase_EXPORT DynamicList<List<commsStruct>> linearCommunication_;

		//- Multi level communication schedule
		static FoamBase_EXPORT DynamicList<List<commsStruct>> treeCommunication_;


		// Private Member Functions

			//- Set data for parallel running
		static FoamBase_EXPORT void setParRun(const label nProcs, const bool haveThreads);

		//- Calculate linear communication schedule
		static FoamBase_EXPORT List<commsStruct> calcLinearComm(const label nProcs);

		//- Calculate tree communication schedule
		static FoamBase_EXPORT List<commsStruct> calcTreeComm(const label nProcs);

		//- Helper function for tree communication schedule determination
		//  Collects all processorIDs below a processor
		static FoamBase_EXPORT void collectReceives
		(
			const label procID,
			const List<DynamicList<label>>& receives,
			DynamicList<label>& allReceives
		);

		//- Allocate a communicator with index
		static FoamBase_EXPORT void allocatePstreamCommunicator
		(
			const label parentIndex,
			const label index
		);

		//- Free a communicator
		static FoamBase_EXPORT void freePstreamCommunicator
		(
			const label index
		);


	protected:

		// Protected data

			//- Communications type of this stream
		commsTypes commsType_;

	public:

		// Declare name of the class and its debug switch
		//ClassName("UPstream");
		static const char* typeName_() { return "UPstream"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;


		// Static data

			//- Should compact transfer be used in which floats replace doubles
			//  reducing the bandwidth requirement at the expense of some loss
			//  in accuracy
		static FoamBase_EXPORT bool floatTransfer;

		//- Number of processors at which the sum algorithm changes from linear
		//  to tree
		static FoamBase_EXPORT int nProcsSimpleSum;

		//- Default commsType
		static FoamBase_EXPORT commsTypes defaultCommsType;

		//- Number of polling cycles in processor updates
		static FoamBase_EXPORT int nPollProcInterfaces;

		//- Default communicator (all processors)
		static FoamBase_EXPORT label worldComm;

		//- Debugging: warn for use of any communicator differing from warnComm
		static FoamBase_EXPORT label warnComm;


		// Constructors

			//- Construct given optional buffer size
		UPstream(const commsTypes commsType)
			:
			commsType_(commsType)
		{}


		// Member Functions

			//- Allocate a new communicator
		static FoamBase_EXPORT label allocateCommunicator
		(
			const label parent,
			const labelList& subRanks,
			const bool doPstream = true
		);

		//- Free a previously allocated communicator
		static FoamBase_EXPORT void freeCommunicator
		(
			const label communicator,
			const bool doPstream = true
		);

		//- Free all communicators
		static FoamBase_EXPORT void freeCommunicators(const bool doPstream);

		//- Helper class for allocating/freeing communicators
		class communicator
		{
			label comm_;

		public:

			communicator
			(
				const label parent,
				const labelList& subRanks,
				const bool doPstream
			)
				:
				comm_(allocateCommunicator(parent, subRanks, doPstream))
			{}

			//- Disallow default bitwise copy construction
			FoamBase_EXPORT communicator(const communicator&) = delete;

			~communicator()
			{
				freeCommunicator(comm_);
			}

			operator label() const
			{
				return comm_;
			}

			//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const communicator&) = delete;
		};

		//- Return physical processor number (i.e. processor number in
		//  worldComm) given communicator and procssor
		static FoamBase_EXPORT int baseProcNo(const label myComm, const int procID);

		//- Return processor number in communicator (given physical processor
		//  number) (= reverse of baseProcNo)
		static FoamBase_EXPORT label procNo(const label comm, const int baseProcID);

		//- Return processor number in communicator (given processor number
		//  and communicator)
		static FoamBase_EXPORT label procNo
		(
			const label myComm,
			const label currentComm,
			const int currentProcID
		);

		//- Add the valid option this type of communications library
		//  adds/requires on the command line
		static FoamBase_EXPORT void addValidParOptions(HashTable<string>& validParOptions);

		//- Initialisation function called from main
		//  Spawns slave processes and initialises inter-communication
		static FoamBase_EXPORT bool init(int& argc, char**& argv, const bool needsThread);

		// Non-blocking comms

			//- Get number of outstanding requests
		static FoamBase_EXPORT label nRequests();

		//- Truncate number of outstanding requests
		static FoamBase_EXPORT void resetRequests(const label sz);

		//- Wait until all requests (from start onwards) have finished.
		static FoamBase_EXPORT void waitRequests(const label start = 0);

		//- Wait until request i has finished.
		static FoamBase_EXPORT void waitRequest(const label i);

		//- Non-blocking comms: has request i finished?
		static FoamBase_EXPORT bool finishedRequest(const label i);

		static FoamBase_EXPORT int allocateTag(const char*);

		static FoamBase_EXPORT int allocateTag(const word&);

		static FoamBase_EXPORT void freeTag(const char*, const int tag);

		static FoamBase_EXPORT void freeTag(const word&, const int tag);


		//- Is this a parallel run?
		static bool& parRun()
		{
			return parRun_;
		}

		//- Have support for threads
		static bool haveThreads()
		{
			return haveThreads_;
		}

		//- Number of processes in parallel run
		static label nProcs(const label communicator = 0)
		{
			return procIDs_[communicator].size();
		}

		//- Process index of the master
		static int masterNo()
		{
			return 0;
		}

		//- Am I the master process
		static bool master(const label communicator = 0)
		{
			return myProcNo_[communicator] == masterNo();
		}

		//- Number of this process (starting from masterNo() = 0)
		static int myProcNo(const label communicator = 0)
		{
			return myProcNo_[communicator];
		}

		static label parent(const label communicator)
		{
			return parentCommunicator_(communicator);
		}

		//- Process ID of given process index
		static List<int>& procID(label communicator)
		{
			return procIDs_[communicator];
		}

		//- Process index of first slave
		static int firstSlave()
		{
			return 1;
		}

		//- Process index of last slave
		static int lastSlave(const label communicator = 0)
		{
			return nProcs(communicator) - 1;
		}

		//- Communication schedule for linear all-to-master (proc 0)
		static const List<commsStruct>& linearCommunication
		(
			const label communicator = 0
		)
		{
			return linearCommunication_[communicator];
		}

		//- Communication schedule for tree all-to-master (proc 0)
		static const List<commsStruct>& treeCommunication
		(
			const label communicator = 0
		)
		{
			return treeCommunication_[communicator];
		}

		//- Message tag of standard messages
		static int& msgType()
		{
			return msgType_;
		}


		//- Get the communications type of the stream
		commsTypes commsType() const
		{
			return commsType_;
		}

		//- Set the communications type of the stream
		commsTypes commsType(const commsTypes ct)
		{
			commsTypes oldCommsType = commsType_;
			commsType_ = ct;
			return oldCommsType;
		}


		//- Exit program
		static FoamBase_EXPORT void exit(int errnum = 1);

		//- Abort program
		static FoamBase_EXPORT void abort();

		//- Exchange label with all processors (in the communicator).
		//  sendData[proci] is the label to send to proci.
		//  After return recvData contains the data from the other processors.
		static FoamBase_EXPORT void allToAll
		(
			const labelUList& sendData,
			labelUList& recvData,
			const label communicator = 0
		);

		//- Exchange data with all processors (in the communicator)
		//  sendSizes, sendOffsets give (per processor) the slice of
		//  sendData to send, similarly recvSizes, recvOffsets give the slice
		//  of recvData to receive
		static FoamBase_EXPORT void allToAll
		(
			const char* sendData,
			const UList<int>& sendSizes,
			const UList<int>& sendOffsets,

			char* recvData,
			const UList<int>& recvSizes,
			const UList<int>& recvOffsets,

			const label communicator = 0
		);

		//- Receive data from all processors on the master
		static FoamBase_EXPORT void gather
		(
			const char* sendData,
			int sendSize,

			char* recvData,
			const UList<int>& recvSizes,
			const UList<int>& recvOffsets,
			const label communicator = 0
		);

		//- Send data to all processors from the root of the communicator
		static FoamBase_EXPORT void scatter
		(
			const char* sendData,
			const UList<int>& sendSizes,
			const UList<int>& sendOffsets,

			char* recvData,
			int recvSize,
			const label communicator = 0
		);
	};


	Ostream& operator<<(Ostream&, const UPstream::commsStruct&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UPstream_Header
