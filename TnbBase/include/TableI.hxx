#pragma once

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Table<Type>::Table
(
	const word& entryName,
	const dictionary& dict
)
	:
	TableBase<Type>(entryName, dict)
{
	Istream& is(dict.lookup(entryName));
	word entryType(is);
	is >> this->table_;
	TableBase<Type>::check();
}


template<class Type>
tnbLib::Function1Types::Table<Type>::Table(const Table<Type>& tbl)
	:
	TableBase<Type>(tbl)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Table<Type>::~Table()
{}


// ************************************************************************* //