#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::PackedBoolList::PackedBoolList()
	:
	PackedList<1>()
{}


inline tnbLib::PackedBoolList::PackedBoolList(const label size)
	:
	PackedList<1>(size)
{}


inline tnbLib::PackedBoolList::PackedBoolList
(
	const label size,
	const bool val
)
	:
	PackedList<1>(size, (val ? 1u : 0u))
{}


inline tnbLib::PackedBoolList::PackedBoolList(const PackedBoolList& lst)
	:
	PackedList<1>(lst)
{}


inline tnbLib::PackedBoolList::PackedBoolList(const PackedList<1>& lst)
	:
	PackedList<1>(lst)
{}


inline tnbLib::PackedBoolList::PackedBoolList(const tnbLib::UList<bool>& lst)
	:
	PackedList<1>()
{
	operator=(lst);
}


inline tnbLib::PackedBoolList::PackedBoolList(const labelUList& indices)
	:
	PackedList<1>(indices.size(), 0u)
{
	set(indices);
}


inline tnbLib::PackedBoolList::PackedBoolList(const UIndirectList<label>& indices)
	:
	PackedList<1>(indices.size(), 0u)
{
	set(indices);
}


inline tnbLib::autoPtr<tnbLib::PackedBoolList>
tnbLib::PackedBoolList::clone() const
{
	return autoPtr<PackedBoolList>(new PackedBoolList(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline void tnbLib::PackedBoolList::transfer(PackedBoolList& lst)
{
	PackedList<1>::transfer(static_cast<PackedList<1>&>(lst));
}


inline void tnbLib::PackedBoolList::transfer(PackedList<1>& lst)
{
	PackedList<1>::transfer(lst);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::PackedBoolList::operator=(const bool val)
{
	PackedList<1>::operator=(val);
}


inline void tnbLib::PackedBoolList::operator=(const PackedBoolList& lst)
{
	PackedList<1>::operator=(lst);
}


inline void tnbLib::PackedBoolList::operator=(const PackedList<1>& lst)
{
	PackedList<1>::operator=(lst);
}


inline void tnbLib::PackedBoolList::operator=(const labelUList& indices)
{
	clear();
	set(indices);
}


inline void tnbLib::PackedBoolList::operator=(const UIndirectList<label>& indices)
{
	clear();
	set(indices);
}


inline tnbLib::PackedBoolList
tnbLib::PackedBoolList::operator~() const
{
	PackedBoolList result(*this);
	result.flip();

	return result;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator&=(const PackedList<1>& lst)
{
	subset(lst);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator&=(const labelUList& indices)
{
	subset(indices);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator&=(const UIndirectList<label>& indices)
{
	subset(indices);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator|=(const PackedList<1>& lst)
{
	set(lst);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator|=(const labelUList& indices)
{
	set(indices);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator|=(const UIndirectList<label>& indices)
{
	set(indices);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator+=(const PackedList<1>& lst)
{
	return operator|=(lst);
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator+=(const labelUList& indices)
{
	return operator|=(indices);
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator+=(const UIndirectList<label>& indices)
{
	return operator|=(indices);
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator-=(const PackedList<1>& lst)
{
	unset(lst);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator-=(const labelUList& indices)
{
	unset(indices);
	return *this;
}


inline tnbLib::PackedBoolList&
tnbLib::PackedBoolList::operator-=(const UIndirectList<label>& indices)
{
	unset(indices);
	return *this;
}


// ************************************************************************* //