#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::OneConstant<Type>::OneConstant(const word& entryName)
	:
	Function1<Type>(entryName)
{}


template<class Type>
tnbLib::Function1Types::OneConstant<Type>::OneConstant
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1<Type>(entryName)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::OneConstant<Type>::~OneConstant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Function1Types::OneConstant<Type>::value
(
	const scalarField& x
) const
{
	return tmp<Field<Type>>(new Field<Type>(x.size(), pTraits<Type>::one));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Function1Types::OneConstant<Type>::integrate
(
	const scalarField& x1,
	const scalarField& x2
) const
{
	return (x2 - x1)*pTraits<Type>::one;
}


template<class Type>
void tnbLib::Function1Types::OneConstant<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);

	os << token::END_STATEMENT << nl;
}


// ************************************************************************* //