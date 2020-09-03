#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::vectorTensorTransform::transform(const Type& x) const
{
	if (hasR_)
	{
		return tnbLib::transform(R(), x);
	}
	else
	{
		return x;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::vectorTensorTransform::transform
(
	const Field<Type>& fld
) const
{
	if (hasR_)
	{
		return tnbLib::transform(R(), fld);
	}
	else
	{
		return fld;
	}
}


template<class Type>
Type tnbLib::vectorTensorTransform::invTransform(const Type& x) const
{
	if (hasR_)
	{
		return tnbLib::transform(R().T(), x);
	}
	else
	{
		return x;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::vectorTensorTransform::invTransform
(
	const Field<Type>& fld
) const
{
	if (hasR_)
	{
		return tnbLib::transform(R().T(), fld);
	}
	else
	{
		return fld;
	}
}


// ************************************************************************* //