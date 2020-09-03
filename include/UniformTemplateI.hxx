#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Uniform<Type>::Uniform
(
	const word& entryName,
	const dictionary& dict
)
	:
	Constant<Type>(entryName, dict)
{}


// ************************************************************************* //