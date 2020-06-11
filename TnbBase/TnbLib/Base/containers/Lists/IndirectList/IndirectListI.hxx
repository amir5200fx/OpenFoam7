#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


inline tnbLib::IndirectListAddressing::IndirectListAddressing
(
	const labelUList& addr
)
	:
	addressing_(addr)
{}


inline tnbLib::IndirectListAddressing::IndirectListAddressing
(
	List<label>&& addr
)
	:
	addressing_(move(addr))
{}


template<class T>
inline tnbLib::IndirectList<T>::IndirectList
(
	const UList<T>& completeList,
	const labelUList& addr
)
	:
	IndirectListAddressing(addr),
	UIndirectList<T>
	(
		completeList,
		IndirectListAddressing::addressing()
		)
{}


template<class T>
inline tnbLib::IndirectList<T>::IndirectList
(
	const UList<T>& completeList,
	List<label>&& addr
)
	:
	IndirectListAddressing(move(addr)),
	UIndirectList<T>
	(
		completeList,
		IndirectListAddressing::addressing()
		)
{}


template<class T>
inline tnbLib::IndirectList<T>::IndirectList
(
	const IndirectList<T>& lst
)
	:
	IndirectListAddressing(lst.addressing()),
	UIndirectList<T>
	(
		lst.completeList(),
		IndirectListAddressing::addressing()
		)
{}


template<class T>
inline tnbLib::IndirectList<T>::IndirectList
(
	const UIndirectList<T>& lst
)
	:
	IndirectListAddressing(lst.addressing()),
	UIndirectList<T>
	(
		lst.completeList(),
		IndirectListAddressing::addressing()
		)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::List<tnbLib::label>&
tnbLib::IndirectListAddressing::addressing() const
{
	return addressing_;
}


inline void tnbLib::IndirectListAddressing::resetAddressing
(
	const labelUList& addr
)
{
	addressing_ = addr;
}


// ************************************************************************* //