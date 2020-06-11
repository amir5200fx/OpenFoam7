#include <UPstream.hxx>

#include <tnbDebug.hxx>
#include <registerSwitch.hxx>
#include <dictionary.hxx>
#include <IOstreams.hxx>

#include <Pstream.hxx>  // added by amir!

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(UPstream, 0);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::UPstream::commsTypes,
		3
		>::names[] =
	{
		"blocking",
		"scheduled",
		"nonBlocking"
	};
}


const tnbLib::NamedEnum<tnbLib::UPstream::commsTypes, 3>
tnbLib::UPstream::commsTypeNames;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::UPstream::setParRun(const label nProcs, const bool haveThreads)
{
	if (nProcs == 0)
	{
		parRun_ = false;
		haveThreads_ = haveThreads;

		freeCommunicator(UPstream::worldComm);
		label comm = allocateCommunicator(-1, labelList(1, label(0)), false);
		if (comm != UPstream::worldComm)
		{
			FatalErrorIn("UPstream::setParRun(const label)")
				<< "problem : comm:" << comm
				<< "  UPstream::worldComm:" << UPstream::worldComm
				<< tnbLib::exit(FatalError);
		}

		Pout.prefix() = "";
		Perr.prefix() = "";
	}
	else
	{
		parRun_ = true;
		haveThreads_ = haveThreads;

		// Redo worldComm communicator (this has been created at static
		// initialisation time)
		freeCommunicator(UPstream::worldComm);
		label comm = allocateCommunicator(-1, identity(nProcs), true);
		if (comm != UPstream::worldComm)
		{
			FatalErrorInFunction
				<< "problem : comm:" << comm
				<< "  UPstream::worldComm:" << UPstream::worldComm
				<< tnbLib::exit(FatalError);
		}

		Pout.prefix() = '[' + name(myProcNo(Pstream::worldComm)) + "] ";
		Perr.prefix() = '[' + name(myProcNo(Pstream::worldComm)) + "] ";
	}
}


tnbLib::List<tnbLib::UPstream::commsStruct> tnbLib::UPstream::calcLinearComm
(
	const label nProcs
)
{
	List<commsStruct> linearCommunication(nProcs);

	// Master
	labelList belowIDs(nProcs - 1);
	forAll(belowIDs, i)
	{
		belowIDs[i] = i + 1;
	}

	linearCommunication[0] = commsStruct
	(
		nProcs,
		0,
		-1,
		belowIDs,
		labelList(0)
	);

	// Slaves. Have no below processors, only communicate up to master
	for (label procID = 1; procID < nProcs; procID++)
	{
		linearCommunication[procID] = commsStruct
		(
			nProcs,
			procID,
			0,
			labelList(0),
			labelList(0)
		);
	}
	return linearCommunication;
}


void tnbLib::UPstream::collectReceives
(
	const label procID,
	const List<DynamicList<label>>& receives,
	DynamicList<label>& allReceives
)
{
	// Append my children (and my children children etc.) to allReceives.

	const DynamicList<label>& myChildren = receives[procID];

	forAll(myChildren, childI)
	{
		allReceives.append(myChildren[childI]);
		collectReceives(myChildren[childI], receives, allReceives);
	}
}


tnbLib::List<tnbLib::UPstream::commsStruct> tnbLib::UPstream::calcTreeComm
(
	label nProcs
)
{
	// Tree like schedule. For 8 procs:
	// (level 0)
	//      0 receives from 1
	//      2 receives from 3
	//      4 receives from 5
	//      6 receives from 7
	// (level 1)
	//      0 receives from 2
	//      4 receives from 6
	// (level 2)
	//      0 receives from 4
	//
	// The sends/receives for all levels are collected per processor
	//  (one send per processor; multiple receives possible) creating a table:
	//
	// So per processor:
	// proc     receives from   sends to
	// ----     -------------   --------
	//  0       1,2,4           -
	//  1       -               0
	//  2       3               0
	//  3       -               2
	//  4       5               0
	//  5       -               4
	//  6       7               4
	//  7       -               6

	label nLevels = 1;
	while ((1 << nLevels) < nProcs)
	{
		nLevels++;
	}

	List<DynamicList<label>> receives(nProcs);
	labelList sends(nProcs, -1);

	// Info<< "Using " << nLevels << " communication levels" << endl;

	label offset = 2;
	label childOffset = offset / 2;

	for (label level = 0; level < nLevels; level++)
	{
		label receiveID = 0;
		while (receiveID < nProcs)
		{
			// Determine processor that sends and we receive from
			label sendID = receiveID + childOffset;

			if (sendID < nProcs)
			{
				receives[receiveID].append(sendID);
				sends[sendID] = receiveID;
			}

			receiveID += offset;
		}

		offset <<= 1;
		childOffset <<= 1;
	}

	// For all processors find the processors it receives data from
	// (and the processors they receive data from etc.)
	List<DynamicList<label>> allReceives(nProcs);
	for (label procID = 0; procID < nProcs; procID++)
	{
		collectReceives(procID, receives, allReceives[procID]);
	}


	List<commsStruct> treeCommunication(nProcs);

	for (label procID = 0; procID < nProcs; procID++)
	{
		treeCommunication[procID] = commsStruct
		(
			nProcs,
			procID,
			sends[procID],
			receives[procID].shrink(),
			allReceives[procID].shrink()
		);
	}
	return treeCommunication;
}


tnbLib::label tnbLib::UPstream::allocateCommunicator
(
	const label parentIndex,
	const labelList& subRanks,
	const bool doPstream
)
{
	label index;
	if (!freeComms_.empty())
	{
		index = freeComms_.pop();
	}
	else
	{
		// Extend storage
		index = parentCommunicator_.size();

		myProcNo_.append(-1);
		procIDs_.append(List<int>(0));
		parentCommunicator_.append(-1);
		linearCommunication_.append(List<commsStruct>(0));
		treeCommunication_.append(List<commsStruct>(0));
	}

	if (debug)
	{
		Pout << "Communicators : Allocating communicator " << index << endl
			<< "    parent : " << parentIndex << endl
			<< "    procs  : " << subRanks << endl
			<< endl;
	}

	// Initialise; overwritten by allocatePstreamCommunicator
	myProcNo_[index] = 0;

	// Convert from label to int
	procIDs_[index].setSize(subRanks.size());
	forAll(procIDs_[index], i)
	{
		procIDs_[index][i] = subRanks[i];

		// Enforce incremental order (so index is rank in next communicator)
		if (i >= 1 && subRanks[i] <= subRanks[i - 1])
		{
			FatalErrorInFunction
				<< "subranks not sorted : " << subRanks
				<< " when allocating subcommunicator from parent "
				<< parentIndex
				<< tnbLib::abort(FatalError);
		}
	}
	parentCommunicator_[index] = parentIndex;

	linearCommunication_[index] = calcLinearComm(procIDs_[index].size());
	treeCommunication_[index] = calcTreeComm(procIDs_[index].size());


	if (doPstream && parRun())
	{
		allocatePstreamCommunicator(parentIndex, index);
	}

	return index;
}


void tnbLib::UPstream::freeCommunicator
(
	const label communicator,
	const bool doPstream
)
{
	if (debug)
	{
		Pout << "Communicators : Freeing communicator " << communicator << endl
			<< "    parent   : " << parentCommunicator_[communicator] << endl
			<< "    myProcNo : " << myProcNo_[communicator] << endl
			<< endl;
	}

	if (doPstream && parRun())
	{
		freePstreamCommunicator(communicator);
	}
	myProcNo_[communicator] = -1;
	// procIDs_[communicator].clear();
	parentCommunicator_[communicator] = -1;
	linearCommunication_[communicator].clear();
	treeCommunication_[communicator].clear();

	freeComms_.push(communicator);
}


void tnbLib::UPstream::freeCommunicators(const bool doPstream)
{
	forAll(myProcNo_, communicator)
	{
		if (myProcNo_[communicator] != -1)
		{
			freeCommunicator(communicator, doPstream);
		}
	}
}


int tnbLib::UPstream::baseProcNo(const label myComm, const int myProcID)
{
	int procID = myProcID;
	label comm = myComm;

	while (parent(comm) != -1)
	{
		const List<int>& parentRanks = UPstream::procID(comm);
		procID = parentRanks[procID];
		comm = UPstream::parent(comm);
	}

	return procID;
}


tnbLib::label tnbLib::UPstream::procNo(const label myComm, const int baseProcID)
{
	const List<int>& parentRanks = procID(myComm);
	label parentComm = parent(myComm);

	if (parentComm == -1)
	{
		return findIndex(parentRanks, baseProcID);
	}
	else
	{
		label parentRank = procNo(parentComm, baseProcID);
		return findIndex(parentRanks, parentRank);
	}
}


tnbLib::label tnbLib::UPstream::procNo
(
	const label myComm,
	const label currentComm,
	const int currentProcID
)
{
	label physProcID = UPstream::baseProcNo(currentComm, currentProcID);
	return procNo(myComm, physProcID);
}


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

bool tnbLib::UPstream::parRun_(false);

bool tnbLib::UPstream::haveThreads_(false);

tnbLib::LIFOStack<tnbLib::label> tnbLib::UPstream::freeComms_;

tnbLib::DynamicList<int> tnbLib::UPstream::myProcNo_(10);

tnbLib::DynamicList<tnbLib::List<int>> tnbLib::UPstream::procIDs_(10);

tnbLib::DynamicList<tnbLib::label> tnbLib::UPstream::parentCommunicator_(10);

int tnbLib::UPstream::msgType_(1);


tnbLib::DynamicList<tnbLib::List<tnbLib::UPstream::commsStruct>>
tnbLib::UPstream::linearCommunication_(10);

tnbLib::DynamicList<tnbLib::List<tnbLib::UPstream::commsStruct>>
tnbLib::UPstream::treeCommunication_(10);


// Allocate a serial communicator. This gets overwritten in parallel mode
// (by UPstream::setParRun())
tnbLib::UPstream::communicator serialComm
(
	-1,
	tnbLib::labelList(1, tnbLib::label(0)),
	false
);


bool tnbLib::UPstream::floatTransfer
(
	tnbLib::debug::optimisationSwitch("floatTransfer", 0)
);
registerOptSwitch
(
	"floatTransfer",
	bool,
	tnbLib::UPstream::floatTransfer
);

int tnbLib::UPstream::nProcsSimpleSum
(
	tnbLib::debug::optimisationSwitch("nProcsSimpleSum", 16)
);
registerOptSwitch
(
	"nProcsSimpleSum",
	int,
	tnbLib::UPstream::nProcsSimpleSum
);

tnbLib::UPstream::commsTypes tnbLib::UPstream::defaultCommsType
(
	commsTypeNames.read(tnbLib::debug::optimisationSwitches().lookup("commsType"))
);

namespace tnbLib
{
	// Register re-reader
	class addcommsTypeToOpt
		:
		public ::tnbLib::simpleRegIOobject
	{
	public:

		addcommsTypeToOpt(const char* name)
			:
			::tnbLib::simpleRegIOobject(tnbLib::debug::addOptimisationObject, name)
		{}

		virtual ~addcommsTypeToOpt()
		{}

		virtual void readData(tnbLib::Istream& is)
		{
			UPstream::defaultCommsType = UPstream::commsTypeNames.read
			(
				is
			);
		}

		virtual void writeData(tnbLib::Ostream& os) const
		{
			os << UPstream::commsTypeNames[UPstream::defaultCommsType];
		}
	};

	addcommsTypeToOpt addcommsTypeToOpt_("commsType");
}

tnbLib::label tnbLib::UPstream::worldComm(0);

tnbLib::label tnbLib::UPstream::warnComm(-1);

int tnbLib::UPstream::nPollProcInterfaces
(
	tnbLib::debug::optimisationSwitch("nPollProcInterfaces", 0)
);
registerOptSwitch
(
	"nPollProcInterfaces",
	int,
	tnbLib::UPstream::nPollProcInterfaces
);


// ************************************************************************* //