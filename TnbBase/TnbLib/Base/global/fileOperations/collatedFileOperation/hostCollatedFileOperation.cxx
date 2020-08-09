#include <hostCollatedFileOperation.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <PackedBoolList.hxx>

#include <Pstream.hxx>  // added by amir
#include <UIPstream.hxx>  // added by amir
#include <IStringStream.hxx>  // added by amir

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	namespace fileOperations
	{
		defineTypeNameAndDebug(hostCollatedFileOperation, 0);
		addToRunTimeSelectionTable
		(
			fileOperation,
			hostCollatedFileOperation,
			word
		);

		// Register initialisation routine. Signals need for threaded mpi and
		// handles command line arguments
		addNamedToRunTimeSelectionTable
		(
			fileOperationInitialise,
			hostCollatedFileOperationInitialise,
			word,
			hostCollated
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::labelList tnbLib::fileOperations::hostCollatedFileOperation::subRanks
(
	const label n
)
{
	DynamicList<label> subRanks(64);

	string ioRanksString(getEnv("FOAM_IORANKS"));
	if (!ioRanksString.empty())
	{
		IStringStream is(ioRanksString);
		labelList ioRanks(is);

		if (findIndex(ioRanks, 0) == -1)
		{
			FatalErrorInFunction
				<< "Rank 0 (master) should be in the IO ranks. Currently "
				<< ioRanks << exit(FatalError);
		}

		// The lowest numbered rank is the IO rank
		PackedBoolList isIOrank(n);
		isIOrank.set(ioRanks);

		for (label proci = Pstream::myProcNo(); proci >= 0; --proci)
		{
			if (isIOrank[proci])
			{
				// Found my master. Collect all processors with same master
				subRanks.append(proci);
				for
					(
						label rank = proci + 1;
						rank < n && !isIOrank[rank];
						++rank
						)
				{
					subRanks.append(rank);
				}
				break;
			}
		}
	}
	else
	{
		// Normal operation: one lowest rank per hostname is the writer
		const string myHostName(hostName());

		stringList hosts(Pstream::nProcs());
		hosts[Pstream::myProcNo()] = myHostName;
		Pstream::gatherList(hosts);
		Pstream::scatterList(hosts);

		// Collect procs with same hostname
		forAll(hosts, proci)
		{
			if (hosts[proci] == myHostName)
			{
				subRanks.append(proci);
			}
		}
	}

	return move(subRanks);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileOperations::hostCollatedFileOperation::hostCollatedFileOperation
(
	const bool verbose
)
	:
	collatedFileOperation
	(
		UPstream::allocateCommunicator
		(
			UPstream::worldComm,
			subRanks(Pstream::nProcs())
		),
		(Pstream::parRun() ? labelList(0) : ioRanks()), // processor dirs
		typeName,
		verbose
	)
{
	if (verbose)
	{
		// Print a bit of information
		stringList ioRanks(Pstream::nProcs());
		if (Pstream::master(comm_))
		{
			ioRanks[Pstream::myProcNo()] = hostName() + "." + name(pid());
		}
		Pstream::gatherList(ioRanks);

		Info << "         IO nodes:" << endl;
		forAll(ioRanks, proci)
		{
			if (!ioRanks[proci].empty())
			{
				Info << "             " << ioRanks[proci] << endl;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileOperations::hostCollatedFileOperation::~hostCollatedFileOperation()
{
	if (comm_ != -1)
	{
		UPstream::freeCommunicator(comm_);
	}
}


// ************************************************************************* //