#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::GAMGInterface::interfaceInternalField
(
	const UList<Type>& iF
) const
{
	tmp<Field<Type>> tresult(new Field<Type>(size()));
	interfaceInternalField(iF, tresult.ref());
	return tresult;
}


template<class Type>
void tnbLib::GAMGInterface::interfaceInternalField
(
	const UList<Type>& iF,
	List<Type>& result
) const
{
	result.setSize(size());

	forAll(result, elemI)
	{
		result[elemI] = iF[faceCells_[elemI]];
	}
}


// ************************************************************************* //