#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::setSizeFieldMapper::setSize(Field<Type>& f) const
{
	f.setSize(size_);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::setSizeFieldMapper::setSize() const
{
	return tmp<Field<Type>>(new Field<Type>(size_));
}


// ************************************************************************* //