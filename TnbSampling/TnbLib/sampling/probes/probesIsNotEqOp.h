#pragma once
#ifndef _probesIsNotEqOp_Header
#define _probesIsNotEqOp_Header

#include <scalar.hxx>

namespace tnbLib
{

	template<class T>
	class isNotEqOp
	{
	public:

		void operator()(T& x, const T& y) const
		{
			const T unsetVal(-vGreat * pTraits<T>::one);

			if (x != unsetVal)
			{
				// Keep x.

				// Note: should check for y != unsetVal but multiple sample cells
				// already handled in read().
			}
			else
			{
				// x is not set. y might be.
				x = y;
			}
		}
	};

}

#endif // !_probesIsNotEqOp_Header
