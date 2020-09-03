#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class AccessType, class T, class AccessOp>
	AccessType ListListOps::combine(const List<T>& lst, AccessOp aop)
	{
		label sum = 0;

		forAll(lst, lstI)
		{
			sum += aop(lst[lstI]).size();
		}

		AccessType result(sum);

		label globalElemI = 0;

		forAll(lst, lstI)
		{
			const T& sub = lst[lstI];

			forAll(aop(sub), elemI)
			{
				result[globalElemI++] = aop(sub)[elemI];
			}
		}
		return result;
	}


	template<class T, class AccessOp>
	labelList ListListOps::subSizes(const List<T>& lst, AccessOp aop)
	{
		labelList sizes(lst.size());

		forAll(lst, lstI)
		{
			sizes[lstI] = aop(lst[lstI]).size();
		}
		return sizes;
	}


	template<class AccessType, class T, class AccessOp, class OffsetOp>
	AccessType ListListOps::combineOffset
	(
		const List<T>& lst,
		const labelList& sizes,
		AccessOp aop,
		OffsetOp oop
	)
	{
		label sum = 0;

		forAll(lst, lstI)
		{
			sum += aop(lst[lstI]).size();
		}

		AccessType result(sum);

		label globalElemI = 0;

		label offset = 0;

		forAll(lst, lstI)
		{
			const T& sub = lst[lstI];

			forAll(aop(sub), elemI)
			{
				result[globalElemI++] = oop(aop(sub)[elemI], offset);
			}

			offset += sizes[lstI];
		}
		return result;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// ************************************************************************* //