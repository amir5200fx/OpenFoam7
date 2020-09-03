#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1<Type>::Function1(const word& entryName)
	:
	name_(entryName)
{}


template<class Type>
tnbLib::Function1<Type>::Function1(const Function1<Type>& de)
	:
	tmp<Function1<Type>>::refCount(),
	name_(de.name_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1<Type>::~Function1()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word& tnbLib::Function1<Type>::name() const
{
	return name_;
}


template<class Type>
void tnbLib::Function1<Type>::convertTimeBase(const Time&)
{}


template<class Type>
Type tnbLib::Function1<Type>::value(const scalar x) const
{
	FatalErrorInFunction
		<< "Evaluation is not defined for " << type() << " functions"
		<< exit(FatalError);

	return Zero;
}


template<class Type>
Type tnbLib::Function1<Type>::integrate(const scalar x1, const scalar x2) const
{
	FatalErrorInFunction
		<< "Integration is not defined for " << type() << " functions"
		<< exit(FatalError);

	return Zero;
}


template<class Function1Type>
tnbLib::tmp<tnbLib::Field<typename Function1Type::returnType>>
tnbLib::FieldFunction1<Function1Type>::value
(
	const scalarField& x
) const
{
	tmp<Field<Type>> tfld(new Field<Type>(x.size()));
	Field<Type>& fld = tfld.ref();

	forAll(x, i)
	{
		fld[i] = Function1Type::value(x[i]);
	}
	return tfld;
}


template<class Function1Type>
tnbLib::FieldFunction1<Function1Type>::FieldFunction1
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1Type(entryName, dict)
{}


template<class Function1Type>
tnbLib::tmp<tnbLib::Function1<typename Function1Type::returnType>>
tnbLib::FieldFunction1<Function1Type>::clone() const
{
	return tmp<Function1<Type>>
		(
			new FieldFunction1<Function1Type>(*this)
			);
}


template<class Function1Type>
tnbLib::tmp<tnbLib::Field<typename Function1Type::returnType>>
tnbLib::FieldFunction1<Function1Type>::integrate
(
	const scalarField& x1,
	const scalarField& x2
) const
{
	tmp<Field<Type>> tfld(new Field<Type>(x1.size()));
	Field<Type>& fld = tfld.ref();

	forAll(x1, i)
	{
		fld[i] = Function1Type::integrate(x1[i], x2[i]);
	}

	return tfld;
}


template<class Type>
void tnbLib::Function1<Type>::writeData(Ostream& os) const
{
	os.writeKeyword(name_) << type();
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class Type>
void  tnbLib::writeEntry(Ostream& os, const Function1<Type>& f1)
{
	f1.writeData(os);
}


// * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const Function1<Type>& f1
	)
{
	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<(Ostream&, const Function1<Type>&)"
	);

	f1.writeData(os);

	return os;
}


// ************************************************************************* //