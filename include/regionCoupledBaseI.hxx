#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::regionCoupledBase::interpolate
(
	const Field<Type>& fld
) const
{
	if (owner())
	{
		return AMI().interpolateToSource(fld);
	}
	else
	{
		return neighbPatch().AMI().interpolateToTarget(fld);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::regionCoupledBase::interpolate
(
	const tmp<Field<Type>>& tFld
) const
{
	if (owner())
	{
		return AMI().interpolateToSource(tFld);
	}
	else
	{
		return neighbPatch().AMI().interpolateToTarget(tFld);
	}
}


template<class Type, class BinaryOp>
void tnbLib::regionCoupledBase::interpolate
(
	const UList<Type>& fld,
	const BinaryOp& bop,
	List<Type>& result
) const
{
	if (owner())
	{
		AMI().interpolateToSource(fld, bop, result);
	}
	else
	{
		neighbPatch().AMI().interpolateToTarget(fld, bop, result);
	}
}


// ************************************************************************* //