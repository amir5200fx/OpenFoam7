#pragma once
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::globalIndex::globalIndex()
{}


tnbLib::globalIndex::globalIndex(labelList&& offsets)
	:
	offsets_(move(offsets))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::labelList& tnbLib::globalIndex::offsets()
{
	return offsets_;
}


inline tnbLib::label tnbLib::globalIndex::offset(const label proci) const
{
	return offsets_[proci];
}


inline tnbLib::label tnbLib::globalIndex::localSize(const label proci) const
{
	return offsets_[proci + 1] - offsets_[proci];
}


inline tnbLib::label tnbLib::globalIndex::localSize() const
{
	return localSize(Pstream::myProcNo());
}


inline tnbLib::label tnbLib::globalIndex::size() const
{
	return offsets_.last();
}


inline tnbLib::label tnbLib::globalIndex::toGlobal
(
	const label proci,
	const label i
) const
{
	return i + offsets_[proci];
}


inline tnbLib::label tnbLib::globalIndex::toGlobal(const label i) const
{
	return toGlobal(Pstream::myProcNo(), i);
}


//- Is on local processor
inline bool tnbLib::globalIndex::isLocal(const label proci, const label i) const
{
	return i >= offsets_[proci] && i < offsets_[proci + 1];
}


inline bool tnbLib::globalIndex::isLocal(const label i) const
{
	return isLocal(Pstream::myProcNo(), i);
}


inline tnbLib::label tnbLib::globalIndex::toLocal(const label proci, const label i)
const
{
	label localI = i - offsets_[proci];

	if (localI < 0 || i >= offsets_[proci + 1])
	{
		FatalErrorInFunction
			<< "Global " << i << " does not belong on processor "
			<< proci << endl << "Offsets:" << offsets_
			<< abort(FatalError);
	}
	return localI;
}


inline tnbLib::label tnbLib::globalIndex::toLocal(const label i) const
{
	return toLocal(Pstream::myProcNo(), i);
}


inline tnbLib::label tnbLib::globalIndex::whichProcID(const label i) const
{
	if (i < 0 || i >= size())
	{
		FatalErrorInFunction
			<< "Global " << i << " does not belong on any processor."
			<< " Offsets:" << offsets_
			<< abort(FatalError);
	}

	return findLower(offsets_, i + 1);
}


// ************************************************************************* //