#pragma once
#include <error.hxx>
#include <products.hxx>
#include <VectorSpaceOps.hxx>
#include <ops.hxx>

#include <type_traits>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts>::VectorSpace()
	{}


	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts>::VectorSpace(const tnbLib::zero)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOpS(*this, Zero, eqOp<Cmpt>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	template<class Form2, class Cmpt2>
	inline VectorSpace<Form, Cmpt, Ncmpts>::VectorSpace
	(
		const VectorSpace<Form2, Cmpt2, Ncmpts>& vs
	)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOp(*this, vs, eqOp<Cmpt>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	template<class SubVector, direction BStart>
	inline
		VectorSpace<Form, Cmpt, Ncmpts>::ConstBlock<SubVector, BStart>::ConstBlock
		(
			const vsType& vs
		)
		:
		vs_(vs)
	{
		static_assert
			(
				vsType::nComponents >= BStart + nComponents,
				"Requested block size > VectorSpace size"
				);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Ncmpts>
	inline direction VectorSpace<Form, Cmpt, Ncmpts>::size()
	{
		return Ncmpts;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline const Cmpt& VectorSpace<Form, Cmpt, Ncmpts>::component
	(
		const direction d
	) const
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		return v_[d];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt& VectorSpace<Form, Cmpt, Ncmpts>::component
	(
		const direction d
	)
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		return v_[d];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::component
	(
		Cmpt& c,
		const direction d
	) const
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		c = v_[d];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::replace
	(
		const direction d,
		const Cmpt& c
	)
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		v_[d] = c;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form VectorSpace<Form, Cmpt, Ncmpts>::uniform(const Cmpt& s)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::eqOpS(v, s, eqOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	template<class SubVector, direction BStart>
	inline const typename VectorSpace<Form, Cmpt, Ncmpts>::template
		ConstBlock<SubVector, BStart>
		VectorSpace<Form, Cmpt, Ncmpts>::block() const
	{
		return *this;
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Ncmpts>
	inline const Cmpt& VectorSpace<Form, Cmpt, Ncmpts>::operator[]
	(
		const direction d
		) const
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		return v_[d];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt& VectorSpace<Form, Cmpt, Ncmpts>::operator[]
	(
		const direction d
		)
	{
#ifdef FULLDEBUG
		if (d >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		return v_[d];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	template<class SubVector, direction BStart>
	inline const Cmpt&
		VectorSpace<Form, Cmpt, Ncmpts>::
		ConstBlock<SubVector, BStart>::operator[]
		(
			const direction i
			) const
	{
#ifdef FULLDEBUG
		if (i >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}
#endif

		return vs_[BStart + i];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	template<class SubVector, direction BStart>
	inline const Cmpt&
		VectorSpace<Form, Cmpt, Ncmpts>::
		ConstBlock<SubVector, BStart>::operator()
		(
			const direction i,
			const direction j
			) const
	{
#ifdef FULLDEBUG
		if (i >= Ncmpts)
		{
			FatalErrorInFunction
				<< "index out of range"
				<< abort(FatalError);
		}

		if (j != 0)
		{
			FatalErrorInFunction
				<< "j != 0"
				<< abort(FatalError);
		}
#endif

		return vs_[BStart + i];
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::operator+=
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs
			)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOp(*this, vs, plusEqOp<Cmpt>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::operator-=
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs
			)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOp(*this, vs, minusEqOp<Cmpt>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::operator=(const tnbLib::zero)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOpS(*this, 0, eqOp<Cmpt>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::operator*=
		(
			const scalar s
			)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOpS(*this, s, multiplyEqOp2<Cmpt, scalar>());
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline void VectorSpace<Form, Cmpt, Ncmpts>::operator/=
		(
			const scalar s
			)
	{
		VectorSpaceOps<Ncmpts, 0>::eqOpS(*this, s, divideEqOp2<Cmpt, scalar>());
	}


	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt& setComponent
	(
		VectorSpace<Form, Cmpt, Ncmpts>& vs,
		const direction d
	)
	{
		return vs.component(d);
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline const Cmpt& component
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs,
		const direction d
	)
	{
		return vs.component(d);
	}


	// Powers of a Form
	// Equivalent to outer-products between the Form and itself
	// Form^0 = 1.0
	template<class Form, class Cmpt, direction Ncmpts>
	inline typename powProduct<Form, 0>::type pow
	(
		const VectorSpace<Form, Cmpt, Ncmpts>&,
		typename powProduct<Form, 0>::type
		= pTraits<typename powProduct<Form, 0>::type>::zero
	)
	{
		return 1.0;
	}

	// Form^1 = Form
	template<class Form, class Cmpt, direction Ncmpts>
	inline typename powProduct<Form, 1>::type pow
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& v,
		typename powProduct<Form, 1>::type
		= pTraits<typename powProduct<Form, 1>::type>::zero
	)
	{
		return static_cast<const Form&>(v);
	}


	// Form^2 = sqr(Form)
	template<class Form, class Cmpt, direction Ncmpts>
	inline typename powProduct<Form, 2>::type pow
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& v,
		typename powProduct<Form, 2>::type
		= pTraits<typename powProduct<Form, 2>::type>::zero
	)
	{
		return sqr(static_cast<const Form&>(v));
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline scalar magSqr
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		scalar ms = magSqr(vs.v_[0]);
		VectorSpaceOps<Ncmpts, 1>::SeqOp(ms, vs, plusEqMagSqrOp2<scalar, Cmpt>());
		return ms;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline scalar mag
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		return ::sqrt(magSqr(static_cast<const Form&>(vs)));
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form normalised
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		const scalar magVs = mag(vs);
		return magVs > 0 ? vs / magVs : Zero;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts> cmptMultiply
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, cmptMultiplyOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts> cmptPow
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, cmptPowOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts> cmptDivide
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, cmptDivideOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline VectorSpace<Form, Cmpt, Ncmpts> stabilise
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs,
		const Cmpt& small
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::opVS(v, vs, small, stabiliseOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt cmptMax
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Cmpt cMax = vs.v_[0];
		VectorSpaceOps<Ncmpts, 1>::SeqOp(cMax, vs, maxEqOp<Cmpt>());
		return cMax;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt cmptMin
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Cmpt cMin = vs.v_[0];
		VectorSpaceOps<Ncmpts, 1>::SeqOp(cMin, vs, minEqOp<Cmpt>());
		return cMin;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt cmptSum
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Cmpt sum = vs.v_[0];
		VectorSpaceOps<Ncmpts, 1>::SeqOp(sum, vs, plusEqOp<Cmpt>());
		return sum;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt cmptAv
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		return cmptSum(vs) / Ncmpts;
	}

	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt cmptProduct
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Cmpt product = vs.v_[0];
		VectorSpaceOps<Ncmpts, 1>::SeqOp(product, vs, multiplyEqOp<Cmpt>());
		return product;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form cmptSqr
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::eqOp(v, vs, eqSqrOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form cmptMag
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::eqOp(v, vs, eqMagOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form max
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, maxOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form min
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, minOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form minMod
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, minModOp<Cmpt>());
		return v;
	}


	template<class Type>
	inline Type dot(const scalar s, const Type& t)
	{
		return s * t;
	}


	template<class Type>
	inline Type dot(const Type& t, const scalar s)
	{
		return t * s;
	}


	template
		<
		class Form1, class Cmpt1, direction Ncmpts1,
		class Form2, class Cmpt2, direction Ncmpts2
		>
		inline typename innerProduct<Form1, Form2>::type dot
		(
			const VectorSpace<Form1, Cmpt1, Ncmpts1>& t1,
			const VectorSpace<Form2, Cmpt2, Ncmpts2>& t2
		)
	{
		return static_cast<const Form1&>(t1) & static_cast<const Form2&>(t2);
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline direction findMax(const VectorSpace<Form, Cmpt, Ncmpts>& vs)
	{
		direction index = 0;
		for (direction i = 1; i < Ncmpts; ++i)
		{
			index = vs[index] > vs[i] ? index : i;
		}
		return index;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline direction findMin(const VectorSpace<Form, Cmpt, Ncmpts>& vs)
	{
		direction index = 0;
		for (direction i = 1; i < Ncmpts; ++i)
		{
			index = vs[index] < vs[i] ? index : i;
		}
		return index;
	}


	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator-
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::eqOp(v, vs, eqMinusOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator+
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, plusOp<Cmpt>());
		return v;
	}

	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator-
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::op(v, vs1, vs2, minusOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator*
		(
			scalar s,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::opSV(v, s, vs, multiplyOp3<Cmpt, scalar, Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator*
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs,
			scalar s
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::opVS(v, vs, s, multiplyOp3<Cmpt, Cmpt, scalar>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator/
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs,
			scalar s
			)
	{
		Form v;
		VectorSpaceOps<Ncmpts, 0>::opVS(v, vs, s, divideOp3<Cmpt, Cmpt, scalar>());
		return v;
	}

	/*
	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator/
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs2
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts,0>::op(v, vs1, vs2, divideOp<Cmpt>());
		return v;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline Form operator/
	(
		scalar s,
		const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
	{
		Form v;
		VectorSpaceOps<Ncmpts,0>::opSV(v, s, vs, divideOp2<scalar, Cmpt>());
		return v;
	}
	*/


	template<class Form, class Cmpt, direction Ncmpts>
	inline Cmpt operator&&
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		Cmpt ddProd = vs1.v_[0] * vs2.v_[0];
		for (direction i = 1; i < Ncmpts; ++i)
		{
			ddProd += vs1.v_[i] * vs2.v_[i];
		}
		return ddProd;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator==
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		bool eq = true;
		for (direction i = 0; i < Ncmpts; ++i)
		{
			if (!(eq &= (equal(vs1.v_[i], vs2.v_[i])))) break;
		}
		return eq;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator!=
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		return !(vs1 == vs2);
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator>
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		bool gt = true;
		for (direction i = 0; i < Ncmpts; ++i)
		{
			if (!(gt &= vs1.v_[i] > vs2.v_[i])) break;
		}
		return gt;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator<
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		bool lt = true;
		for (direction i = 0; i < Ncmpts; ++i)
		{
			if (!(lt &= vs1.v_[i] < vs2.v_[i])) break;
		}
		return lt;
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator>=
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		return !(vs1 < vs2);
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline bool operator<=
		(
			const VectorSpace<Form, Cmpt, Ncmpts>& vs1,
			const VectorSpace<Form, Cmpt, Ncmpts>& vs2
			)
	{
		return !(vs1 > vs2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //