#pragma once
#include <error.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

inline tnbLib::SLListBase::link::link()
	:
	next_(0)
{}


inline tnbLib::SLListBase::link::link(link* p)
	:
	next_(p)
{}


inline tnbLib::SLListBase::SLListBase()
	:
	last_(0),
	nElmts_(0)
{}


inline tnbLib::SLListBase::SLListBase(link* a)
	:
	last_(a->next_ = a),
	nElmts_(1)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

inline tnbLib::SLListBase::~SLListBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::SLListBase::size() const
{
	return nElmts_;
}


inline bool tnbLib::SLListBase::empty() const
{
	return !nElmts_;
}


inline tnbLib::SLListBase::link*
tnbLib::SLListBase::first()
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_->next_;
}


inline const tnbLib::SLListBase::link*
tnbLib::SLListBase::first() const
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_->next_;
}


inline tnbLib::SLListBase::link*
tnbLib::SLListBase::last()
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline const tnbLib::SLListBase::link*
tnbLib::SLListBase::last() const
{
	if (!nElmts_)
	{
		FatalErrorInFunction
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline void tnbLib::SLListBase::clear()
{
	last_ = 0;
	nElmts_ = 0;
}


inline void tnbLib::SLListBase::transfer(SLListBase& lst)
{
	last_ = lst.last_;
	nElmts_ = lst.nElmts_;

	lst.clear();
}


inline tnbLib::SLListBase::link* tnbLib::SLListBase::remove
(
	SLListBase::iterator& it
)
{
	return remove(it.curElmt_);
}


// * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * * //

inline tnbLib::SLListBase::iterator::iterator(SLListBase& s, link* elmt)
	:
	curList_(s),
	curElmt_(elmt),
	curLink_(*curElmt_)
{}


inline tnbLib::SLListBase::iterator::iterator(SLListBase& s)
	:
	curList_(s),
	curElmt_(nullptr),
	curLink_()
{}


inline void tnbLib::SLListBase::iterator::operator=(const iterator& iter)
{
	curElmt_ = iter.curElmt_;
	curLink_ = iter.curLink_;
}


inline bool tnbLib::SLListBase::iterator::operator==(const iterator& iter) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool tnbLib::SLListBase::iterator::operator!=(const iterator& iter) const
{
	return curElmt_ != iter.curElmt_;
}


inline tnbLib::SLListBase::link& tnbLib::SLListBase::iterator::operator*()
{
	return *curElmt_;
}


inline tnbLib::SLListBase::iterator& tnbLib::SLListBase::iterator::operator++()
{
	if (curElmt_ == curList_.last_ || curList_.last_ == 0)
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


inline tnbLib::SLListBase::iterator
tnbLib::SLListBase::iterator::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}


inline tnbLib::SLListBase::iterator
tnbLib::SLListBase::begin()
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


inline const tnbLib::SLListBase::iterator&
tnbLib::SLListBase::end()
{
	return endIter_;
}


// * * * * * * * * * * * * * * STL const_iterator  * * * * * * * * * * * * * //

inline tnbLib::SLListBase::const_iterator::const_iterator
(
	const SLListBase& s,
	const link* elmt
)
	:
	curList_(s),
	curElmt_(elmt)
{}


inline tnbLib::SLListBase::const_iterator::const_iterator(const iterator& iter)
	:
	curList_(iter.curList_),
	curElmt_(iter.curElmt_)
{}


inline void tnbLib::SLListBase::const_iterator::operator=
(
	const const_iterator& iter
	)
{
	curElmt_ = iter.curElmt_;
}


inline bool tnbLib::SLListBase::const_iterator::operator==
(
	const const_iterator& iter
	) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool tnbLib::SLListBase::const_iterator::operator!=
(
	const const_iterator& iter
	) const
{
	return curElmt_ != iter.curElmt_;
}


inline const tnbLib::SLListBase::link&
tnbLib::SLListBase::const_iterator::operator*()
{
	return *curElmt_;
}


inline tnbLib::SLListBase::const_iterator&
tnbLib::SLListBase::const_iterator::operator++()
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


inline tnbLib::SLListBase::const_iterator
tnbLib::SLListBase::const_iterator::operator++(int)
{
	const_iterator tmp = *this;
	++*this;
	return tmp;
}


inline tnbLib::SLListBase::const_iterator
tnbLib::SLListBase::cbegin() const
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


inline const tnbLib::SLListBase::const_iterator&
tnbLib::SLListBase::cend() const
{
	return endConstIter_;
}


inline tnbLib::SLListBase::const_iterator
tnbLib::SLListBase::begin() const
{
	return this->cbegin();
}


inline const tnbLib::SLListBase::const_iterator&
tnbLib::SLListBase::end() const
{
	return endConstIter_;
}


// ************************************************************************* //