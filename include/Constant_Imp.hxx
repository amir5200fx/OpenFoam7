#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Constant<Type>::Constant
(
	const word& entryName,
	const Type& val
)
	:
	Function1<Type>(entryName),
	value_(val)
{}


template<class Type>
tnbLib::Function1Types::Constant<Type>::Constant
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1<Type>(entryName),
	value_(Zero)
{
	Istream& is(dict.lookup(entryName));
	word entryType(is);
	is >> value_;
}


template<class Type>
tnbLib::Function1Types::Constant<Type>::Constant
(
	const word& entryName,
	Istream& is
)
	:
	Function1<Type>(entryName),
	value_(pTraits<Type>(is))
{}


template<class Type>
tnbLib::Function1Types::Constant<Type>::Constant(const Constant<Type>& cnst)
	:
	Function1<Type>(cnst),
	value_(cnst.value_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Constant<Type>::~Constant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Function1Types::Constant<Type>::value
(
	const scalarField& x
) const
{
	return tmp<Field<Type>>(new Field<Type>(x.size(), value_));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Function1Types::Constant<Type>::integrate
(
	const scalarField& x1,
	const scalarField& x2
) const
{
	return (x2 - x1)*value_;
}


template<class Type>
void tnbLib::Function1Types::Constant<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);

	os << token::SPACE << value_ << token::END_STATEMENT << nl;
}


// ************************************************************************* //