#include <cyclicAMIPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::cyclicAMIPolyPatch::interpolate
(
	const Field<Type>& fld,
	const UList<Type>& defaultValues
) const
{
	const cyclicAMIPolyPatch& nei = neighbPatch();

	tmp<Field<Type>> result(new Field<Type>(size(), Zero));

	if (owner())
	{
		forAll(AMIs(), i)
		{
			result.ref() +=
				AMIs()[i].interpolateToSource
				(
					AMITransforms()[i].invTransform(fld),
					defaultValues
				);
		}
	}
	else
	{
		forAll(nei.AMIs(), i)
		{
			result.ref() +=
				nei.AMIs()[i].interpolateToTarget
				(
					nei.AMITransforms()[i].transform(fld),
					defaultValues
				);
		}
	}

	return result;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::cyclicAMIPolyPatch::interpolate
(
	const tmp<Field<Type>>& tFld,
	const UList<Type>& defaultValues
) const
{
	return interpolate(tFld(), defaultValues);
}


// ************************************************************************* //