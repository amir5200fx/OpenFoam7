#pragma once
// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class Type, class BinaryOp>
void tnbLib::allReduce
(
	Type& Value,
	int MPICount,
	MPI_Datatype MPIType,
	MPI_Op MPIOp,
	const BinaryOp& bop,
	const int tag,
	const label communicator
)
{
	if (!UPstream::parRun())
	{
		return;
	}

	if (UPstream::nProcs(communicator) <= UPstream::nProcsSimpleSum)
	{
		if (UPstream::master(communicator))
		{
			for
				(
					int slave = UPstream::firstSlave();
					slave <= UPstream::lastSlave(communicator);
					slave++
					)
			{
				Type value;

				if
					(
						MPI_Recv
						(
							&value,
							MPICount,
							MPIType,
							slave,  // UPstream::procID(slave),
							tag,
							PstreamGlobals::MPICommunicators_[communicator],
							MPI_STATUS_IGNORE
						)
						)
				{
					FatalErrorInFunction
						<< "MPI_Recv failed"
						<< tnbLib::abort(FatalError);
				}

				Value = bop(Value, value);
			}
		}
		else
		{
			if
				(
					MPI_Send
					(
						&Value,
						MPICount,
						MPIType,
						UPstream::masterNo(),//UPstream::procID(masterNo()),
						tag,
						PstreamGlobals::MPICommunicators_[communicator]
					)
					)
			{
				FatalErrorInFunction
					<< "MPI_Send failed"
					<< tnbLib::abort(FatalError);
			}
		}


		if (UPstream::master(communicator))
		{
			for
				(
					int slave = UPstream::firstSlave();
					slave <= UPstream::lastSlave(communicator);
					slave++
					)
			{
				if
					(
						MPI_Send
						(
							&Value,
							MPICount,
							MPIType,
							slave,      // UPstream::procID(slave),
							tag,
							PstreamGlobals::MPICommunicators_[communicator]
						)
						)
				{
					FatalErrorInFunction
						<< "MPI_Send failed"
						<< tnbLib::abort(FatalError);
				}
			}
		}
		else
		{
			if
				(
					MPI_Recv
					(
						&Value,
						MPICount,
						MPIType,
						UPstream::masterNo(),//UPstream::procID(masterNo()),
						tag,
						PstreamGlobals::MPICommunicators_[communicator],
						MPI_STATUS_IGNORE
					)
					)
			{
				FatalErrorInFunction
					<< "MPI_Recv failed"
					<< tnbLib::abort(FatalError);
			}
		}
	}
	else
	{
		Type sum;
		MPI_Allreduce
		(
			&Value,
			&sum,
			MPICount,
			MPIType,
			MPIOp,
			PstreamGlobals::MPICommunicators_[communicator]
		);
		Value = sum;
	}
}


// ************************************************************************* //