#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ContainerType>
tnbLib::Circulator<ContainerType>::Circulator()
	:
	CirculatorBase(),
	begin_(0),
	end_(0),
	iter_(0),
	fulcrum_(0)
{}


template<class ContainerType>
tnbLib::Circulator<ContainerType>::Circulator(ContainerType& container)
	:
	CirculatorBase(),
	begin_(container.begin()),
	end_(container.end()),
	iter_(begin_),
	fulcrum_(begin_)
{}


template<class ContainerType>
tnbLib::Circulator<ContainerType>::Circulator
(
	const iterator& begin,
	const iterator& end
)
	:
	CirculatorBase(),
	begin_(begin),
	end_(end),
	iter_(begin),
	fulcrum_(begin)
{}


template<class ContainerType>
tnbLib::Circulator<ContainerType>::Circulator
(
	const Circulator<ContainerType>& rhs
)
	:
	CirculatorBase(),
	begin_(rhs.begin_),
	end_(rhs.end_),
	iter_(rhs.iter_),
	fulcrum_(rhs.fulcrum_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ContainerType>
tnbLib::Circulator<ContainerType>::~Circulator()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::size_type
tnbLib::Circulator<ContainerType>::size() const
{
	return end_ - begin_;
}


template<class ContainerType>
bool tnbLib::Circulator<ContainerType>::circulate
(
	const CirculatorBase::direction dir
)
{
	if (dir == CirculatorBase::direction::clockwise)
	{
		operator++();
	}
	else if (dir == CirculatorBase::direction::anticlockwise)
	{
		operator--();
	}

	return !(iter_ == fulcrum_);
}


template<class ContainerType>
void tnbLib::Circulator<ContainerType>::setFulcrumToIterator()
{
	fulcrum_ = iter_;
}


template<class ContainerType>
void tnbLib::Circulator<ContainerType>::setIteratorToFulcrum()
{
	iter_ = fulcrum_;
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::difference_type
tnbLib::Circulator<ContainerType>::nRotations() const
{
	return (iter_ - fulcrum_);
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::reference
tnbLib::Circulator<ContainerType>::next() const
{
	if (iter_ == end_ - 1)
	{
		return *begin_;
	}

	return *(iter_ + 1);
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::reference
tnbLib::Circulator<ContainerType>::prev() const
{
	if (iter_ == begin_)
	{
		return *(end_ - 1);
	}

	return *(iter_ - 1);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class ContainerType>
void tnbLib::Circulator<ContainerType>::operator=
(
	const Circulator<ContainerType>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	begin_ = rhs.begin_;
	end_ = rhs.end_;
	iter_ = rhs.iter_;
	fulcrum_ = rhs.fulcrum_;
}


template<class ContainerType>
tnbLib::Circulator<ContainerType>&
tnbLib::Circulator<ContainerType>::operator++()
{
	++iter_;
	if (iter_ == end_)
	{
		iter_ = begin_;
	}

	return *this;
}


template<class ContainerType>
tnbLib::Circulator<ContainerType>
tnbLib::Circulator<ContainerType>::operator++(int)
{
	Circulator<ContainerType> tmp = *this;
	++(*this);
	return tmp;
}


template<class ContainerType>
tnbLib::Circulator<ContainerType>&
tnbLib::Circulator<ContainerType>::operator--()
{
	if (iter_ == begin_)
	{
		iter_ = end_;
	}
	--iter_;

	return *this;
}


template<class ContainerType>
tnbLib::Circulator<ContainerType>
tnbLib::Circulator<ContainerType>::operator--(int)
{
	Circulator<ContainerType> tmp = *this;
	--(*this);
	return tmp;
}


template<class ContainerType>
bool tnbLib::Circulator<ContainerType>::operator==
(
	const Circulator<ContainerType>& c
	) const
{
	return
		(
			begin_ == c.begin_
			&& end_ == c.end_
			&& iter_ == c.iter_
			&& fulcrum_ == c.fulcrum_
			);
}


template<class ContainerType>
bool tnbLib::Circulator<ContainerType>::operator!=
(
	const Circulator<ContainerType>& c
	) const
{
	return !(*this == c);
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::reference
tnbLib::Circulator<ContainerType>::operator*() const
{
	return *iter_;
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::reference
tnbLib::Circulator<ContainerType>::operator()() const
{
	return operator*();
}


template<class ContainerType>
typename tnbLib::Circulator<ContainerType>::difference_type
tnbLib::Circulator<ContainerType>::operator-
(
	const Circulator<ContainerType>& c
	) const
{
	return iter_ - c.iter_;
}


// ************************************************************************* //