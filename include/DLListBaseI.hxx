#pragma once
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

inline tnbLib::DLListBase::link::link()
	:
	prev_(0),
	next_(0)
{}


inline tnbLib::DLListBase::DLListBase()
	:
	first_(0),
	last_(0),
	nElmts_(0)
{}


inline tnbLib::DLListBase::DLListBase(link* a)
	:
	first_(a),
	last_(a),
	nElmts_(1)
{
	a->prev_ = a;
	a->next_ = a;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

inline tnbLib::DLListBase::~DLListBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::DLListBase::link::registered() const
{
	return prev_ != 0 && next_ != 0;
}


inline void tnbLib::DLListBase::link::deregister()
{
	prev_ = 0;
	next_ = 0;
}


inline tnbLib::label tnbLib::DLListBase::size() const
{
	return nElmts_;
}


inline bool tnbLib::DLListBase::empty() const
{
	return !nElmts_;
}


inline tnbLib::DLListBase::link*
tnbLib::DLListBase::first()
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return first_;
}


inline const tnbLib::DLListBase::link*
tnbLib::DLListBase::first() const
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return first_;
}


inline tnbLib::DLListBase::link*
tnbLib::DLListBase::last()
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline const tnbLib::DLListBase::link*
tnbLib::DLListBase::last() const
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline void tnbLib::DLListBase::clear()
{
	first_ = 0;
	last_ = 0;
	nElmts_ = 0;
}


inline void tnbLib::DLListBase::transfer(DLListBase& lst)
{
	first_ = lst.first_;
	last_ = lst.last_;
	nElmts_ = lst.nElmts_;

	lst.clear();
}


inline tnbLib::DLListBase::link*
tnbLib::DLListBase::remove
(
	DLListBase::iterator& it
)
{
	return remove(it.curElmt_);
}


inline tnbLib::DLListBase::link*
tnbLib::DLListBase::replace
(
	DLListBase::iterator& oldIter,
	DLListBase::link* newLink
)
{
	return replace(oldIter.curElmt_, newLink);
}


// * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * * //

inline tnbLib::DLListBase::iterator::iterator(DLListBase& s, link* elmt)
	:
	curList_(s),
	curElmt_(elmt),
	curLink_(*curElmt_)
{}


inline tnbLib::DLListBase::iterator::iterator(DLListBase& s)
	:
	curList_(s),
	curElmt_(nullptr),
	curLink_()
{}


inline void tnbLib::DLListBase::iterator::operator=(const iterator& iter)
{
	curElmt_ = iter.curElmt_;
	curLink_ = iter.curLink_;
}


inline bool tnbLib::DLListBase::iterator::operator==(const iterator& iter) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool tnbLib::DLListBase::iterator::operator!=(const iterator& iter) const
{
	return curElmt_ != iter.curElmt_;
}


inline tnbLib::DLListBase::link&
tnbLib::DLListBase::iterator::operator*()
{
	return *curElmt_;
}


inline tnbLib::DLListBase::iterator&
tnbLib::DLListBase::iterator::operator++()
{
	// Check if the curElmt_ is the last element (if it points to itself)
	// or if the list is empty because the last element may have been removed
	if (curLink_.next_ == curElmt_ || curList_.last_ == 0)
	{
		curElmt_ = 0;
	}
	else
	{
		curElmt_ = curLink_.next_;
		curLink_ = *curElmt_;
	}

	return *this;
}


inline tnbLib::DLListBase::iterator
tnbLib::DLListBase::iterator::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}


inline tnbLib::DLListBase::iterator
tnbLib::DLListBase::begin()
{
	if (size())
	{
		return iterator(*this, first());
	}
	else
	{
		return endIter_;
	}
}


inline const tnbLib::DLListBase::iterator& tnbLib::DLListBase::end()
{
	return endIter_;
}


// * * * * * * * * * * * * * * STL const_iterator  * * * * * * * * * * * * * //

inline tnbLib::DLListBase::const_iterator::const_iterator
(
	const DLListBase& s,
	const link* elmt
)
	:
	curList_(s),
	curElmt_(elmt)
{}


inline tnbLib::DLListBase::const_iterator::const_iterator(const iterator& iter)
	:
	curList_(iter.curList_),
	curElmt_(iter.curElmt_)
{}


inline void tnbLib::DLListBase::const_iterator::operator=
(
	const const_iterator& iter
	)
{
	curElmt_ = iter.curElmt_;
}


inline bool tnbLib::DLListBase::const_iterator::operator==
(
	const const_iterator& iter
	) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool tnbLib::DLListBase::const_iterator::operator!=
(
	const const_iterator& iter
	) const
{
	return curElmt_ != iter.curElmt_;
}


inline const tnbLib::DLListBase::link&
tnbLib::DLListBase::const_iterator::operator*()
{
	return *curElmt_;
}


inline tnbLib::DLListBase::const_iterator&
tnbLib::DLListBase::const_iterator::operator++()
{
	if (curElmt_ == curList_.last_)
	{
		curElmt_ = 0;
	}
	else
	{
		curElmt_ = curElmt_->next_;
	}

	return *this;
}


inline tnbLib::DLListBase::const_iterator
tnbLib::DLListBase::const_iterator::operator++(int)
{
	const_iterator tmp = *this;
	++*this;
	return tmp;
}


inline tnbLib::DLListBase::const_iterator
tnbLib::DLListBase::cbegin() const
{
	if (size())
	{
		return const_iterator(*this, first());
	}
	else
	{
		return endConstIter_;
	}
}


inline const tnbLib::DLListBase::const_iterator&
tnbLib::DLListBase::cend() const
{
	return endConstIter_;
}


inline tnbLib::DLListBase::const_iterator
tnbLib::DLListBase::begin() const
{
	return this->cbegin();
}


inline const tnbLib::DLListBase::const_iterator&
tnbLib::DLListBase::end() const
{
	return endConstIter_;
}


// * * * * * * * * * * STL const_reverse_iterator  * * * * * * * * * * * * * //

inline tnbLib::DLListBase::const_reverse_iterator::const_reverse_iterator
(
	const DLListBase& s,
	const link* elmt
)
	:
	curList_(s),
	curElmt_(elmt)
{}


inline void tnbLib::DLListBase::const_reverse_iterator::operator=
(
	const const_reverse_iterator& iter
	)
{
	curElmt_ = iter.curElmt_;
}


inline bool tnbLib::DLListBase::const_reverse_iterator::operator==
(
	const const_reverse_iterator& iter
	) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool tnbLib::DLListBase::const_reverse_iterator::operator!=
(
	const const_reverse_iterator& iter
	) const
{
	return curElmt_ != iter.curElmt_;
}


inline const tnbLib::DLListBase::link&
tnbLib::DLListBase::const_reverse_iterator::operator*()
{
	return *curElmt_;
}


inline tnbLib::DLListBase::const_reverse_iterator&
tnbLib::DLListBase::const_reverse_iterator::operator++()
{
	if (curElmt_ == curList_.first_)
	{
		curElmt_ = 0;
	}
	else
	{
		curElmt_ = curElmt_->prev_;
	}

	return *this;
}


inline tnbLib::DLListBase::const_reverse_iterator
tnbLib::DLListBase::const_reverse_iterator::operator++(int)
{
	const_reverse_iterator tmp = *this;
	++*this;
	return tmp;
}


inline tnbLib::DLListBase::const_reverse_iterator
tnbLib::DLListBase::crbegin() const
{
	if (size())
	{
		return const_reverse_iterator(*this, last());
	}
	else
	{
		return endConstRevIter_;
	}
}


inline const tnbLib::DLListBase::const_reverse_iterator&
tnbLib::DLListBase::crend() const
{
	return endConstRevIter_;
}


inline tnbLib::DLListBase::const_reverse_iterator
tnbLib::DLListBase::rbegin() const
{
	return this->crbegin();
}


inline const tnbLib::DLListBase::const_reverse_iterator&
tnbLib::DLListBase::rend() const
{
	return endConstRevIter_;
}


// ************************************************************************* //