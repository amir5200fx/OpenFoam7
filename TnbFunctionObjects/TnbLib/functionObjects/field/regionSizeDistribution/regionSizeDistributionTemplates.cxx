#include <regionSizeDistribution.hxx>

//#include <regionSplit.hxx>
//#include <volFields.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//tnbLib::Map<Type> tnbLib::functionObjects::regionSizeDistribution::regionSum
//(
//	const regionSplit& regions,
//	const Field<Type>& fld
//) const
//{
//	// Per region the sum of fld
//	Map<Type> regionToSum(regions.nRegions() / Pstream::nProcs());
//
//	forAll(fld, celli)
//	{
//		label regionI = regions[celli];
//
//		typename Map<Type>::iterator fnd = regionToSum.find(regionI);
//		if (fnd == regionToSum.end())
//		{
//			regionToSum.insert(regionI, fld[celli]);
//		}
//		else
//		{
//			fnd() += fld[celli];
//		}
//	}
//	Pstream::mapCombineGather(regionToSum, plusEqOp<Type>());
//	Pstream::mapCombineScatter(regionToSum);
//
//	return regionToSum;
//}
//
//
//template<class Type>
//tnbLib::List<Type> tnbLib::functionObjects::regionSizeDistribution::extractData
//(
//	const UList<label>& keys,
//	const Map<Type>& regionData
//) const
//{
//	List<Type> sortedData(keys.size());
//
//	forAll(keys, i)
//	{
//		sortedData[i] = regionData[keys[i]];
//	}
//	return sortedData;
//}
//
//
//// ************************************************************************* //