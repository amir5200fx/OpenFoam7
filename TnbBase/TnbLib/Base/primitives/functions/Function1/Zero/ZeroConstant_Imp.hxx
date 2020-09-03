#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::ZeroConstant<Type>::ZeroConstant
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1<Type>(entryName)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::ZeroConstant<Type>::~ZeroConstant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::ZeroConstant<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);

	os << token::END_STATEMENT << nl;
}


// ************************************************************************* //