#pragma once
#include <ListOps.hxx>
#include <IOobject.hxx>
#include <HashSet.hxx>
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class ListType1, class ListType2>
	typename tnbLib::outerProduct
		<
		typename ListType1::value_type,
		typename ListType2::value_type
		>::type
		tnbLib::interpolationWeights::weightedSum
		(
			const ListType1& f1,
			const ListType2& f2
		)
	{
		typedef typename outerProduct
			<
			typename ListType1::value_type,
			typename ListType2::value_type
			>::type returnType;

		if (f1.size())
		{
			returnType SumProd = f1[0] * f2[0];
			for (label i = 1; i < f1.size(); ++i)
			{
				SumProd += f1[i] * f2[i];
			}
			return SumProd;
		}
		else
		{
			return Zero;
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //