#include <globalIndex.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::globalIndex::globalIndex
(
	const label localSize,
	const int tag,
	const label comm,
	const bool parallel
)
	:
	offsets_(Pstream::nProcs(comm) + 1)
{
	labelList localSizes(Pstream::nProcs(comm), 0);
	localSizes[Pstream::myProcNo(comm)] = localSize;
	if (parallel)
	{
		Pstream::gatherList(localSizes, tag, comm);
		Pstream::scatterList(localSizes, tag, comm);
	}

	label offset = 0;
	offsets_[0] = 0;
	for (label proci = 0; proci < Pstream::nProcs(comm); proci++)
	{
		label oldOffset = offset;
		offset += localSizes[proci];

		if (offset < oldOffset)
		{
			FatalErrorInFunction
				<< "Overflow : sum of sizes " << localSizes
				<< " exceeds capability of label (" << labelMax
				<< "). Please recompile with larger datatype for label."
				<< exit(FatalError);
		}
		offsets_[proci + 1] = offset;
	}
}


tnbLib::globalIndex::globalIndex(const label localSize)
	:
	offsets_(Pstream::nProcs() + 1)
{
	labelList localSizes(Pstream::nProcs(), 0);
	localSizes[Pstream::myProcNo()] = localSize;
	Pstream::gatherList(localSizes, Pstream::msgType());
	Pstream::scatterList(localSizes, Pstream::msgType());

	label offset = 0;
	offsets_[0] = 0;
	for (label proci = 0; proci < Pstream::nProcs(); proci++)
	{
		label oldOffset = offset;
		offset += localSizes[proci];

		if (offset < oldOffset)
		{
			FatalErrorInFunction
				<< "Overflow : sum of sizes " << localSizes
				<< " exceeds capability of label (" << labelMax
				<< "). Please recompile with larger datatype for label."
				<< exit(FatalError);
		}
		offsets_[proci + 1] = offset;
	}
}


tnbLib::globalIndex::globalIndex(const labelList& offsets)
	:
	offsets_(offsets)
{}


tnbLib::globalIndex::globalIndex(Istream& is)
{
	is >> offsets_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, globalIndex& gi)
{
	return is >> gi.offsets_;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const globalIndex& gi)
{
	return os << gi.offsets_;
}


// ************************************************************************* //