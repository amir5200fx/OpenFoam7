#pragma once
// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::TimeFunction1<Type>::TimeFunction1
(
	const Time& t,
	const word& name,
	const dictionary& dict
)
	:
	time_(t),
	name_(name),
	entry_(Function1<Type>::New(name, dict))
{
	entry_->convertTimeBase(t);
}


template<class Type>
tnbLib::TimeFunction1<Type>::TimeFunction1(const Time& t, const word& name)
	:
	time_(t),
	name_(name),
	entry_(nullptr)
{}


template<class Type>
tnbLib::TimeFunction1<Type>::TimeFunction1
(
	const TimeFunction1<Type>& tde
)
	:
	time_(tde.time_),
	name_(tde.name_),
	entry_()
{
	if (tde.entry_.valid())
	{
		entry_.reset(tde.entry_->clone().ptr());
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::TimeFunction1<Type>::~TimeFunction1()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::TimeFunction1<Type>::reset(const dictionary& dict)
{
	entry_.reset
	(
		Function1<Type>::New
		(
			name_,
			dict
		).ptr()
	);

	entry_->convertTimeBase(time_);
}


template<class Type>
const tnbLib::word& tnbLib::TimeFunction1<Type>::name() const
{
	return entry_->name();
}


template<class Type>
Type tnbLib::TimeFunction1<Type>::value(const scalar x) const
{
	return entry_->value(x);
}


template<class Type>
Type tnbLib::TimeFunction1<Type>::integrate
(
	const scalar x1,
	const scalar x2
) const
{
	return entry_->integrate(x1, x2);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const TimeFunction1<Type>& de
	)
{
	return de.entry_->operator<<(os, de);
}


template<class Type>
void tnbLib::TimeFunction1<Type>::writeData(Ostream& os) const
{
	entry_->writeData(os);
}


// ************************************************************************* //