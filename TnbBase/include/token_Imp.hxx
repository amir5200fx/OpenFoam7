#pragma once
#include <HashTable.hxx>
template<class compoundType>
tnbLib::token::compound::addIstreamConstructorToTable<compoundType>::addIstreamConstructorToTable(const word& lookup /* = compoundType::typeName */)
{
	constructIstreamConstructorTables();
	if (!tnbLib::token::compound::IstreamConstructorTablePtr_->insert(lookup, New))
	{
		std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "compound" << std::endl;
		error::safePrintStack(std::cerr);
	}
}

template<class compoundType>
tnbLib::token::compound::addRemovableIstreamConstructorToTable<compoundType>::addRemovableIstreamConstructorToTable(const word& lookup /* = compoundType::typeName */)
	: lookup_(lookup)
{
	constructIstreamConstructorTables();
	tnbLib::token::compound::IstreamConstructorTablePtr_->set(lookup, New);
}

template<class compoundType>
tnbLib::token::compound::addRemovableIstreamConstructorToTable<compoundType>::~addRemovableIstreamConstructorToTable()
{
	if (tnbLib::token::compound::IstreamConstructorTablePtr_) { tnbLib::token::compound::IstreamConstructorTablePtr_->erase(lookup_); }
}