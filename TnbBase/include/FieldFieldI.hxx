#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

#ifdef FULLDEBUG

	template<template<class> class Field, class Type1, class Type2>
	void checkFields
	(
		const FieldField<Field, Type1>& f1,
		const FieldField<Field, Type2>& f2,
		const char* op
	)
	{
		if (f1.size() != f2.size())
		{
			FatalErrorInFunction
				<< " FieldField<" << pTraits<Type1>::typeName
				<< "> f1(" << f1.size() << ')'
				<< " and FieldField<" << pTraits<Type2>::typeName
				<< "> f2(" << f2.size() << ')'
				<< endl << " for operation " << op
				<< abort(FatalError);
		}
	}

	template<template<class> class Field, class Type1, class Type2, class Type3>
	void checkFields
	(
		const FieldField<Field, Type1>& f1,
		const FieldField<Field, Type2>& f2,
		const FieldField<Field, Type3>& f3,
		const char* op
	)
	{
		if (f1.size() != f2.size() || f1.size() != f3.size())
		{
			FatalErrorInFunction
				<< " FieldField<" << pTraits<Type1>::typeName
				<< "> f1(" << f1.size() << ')'
				<< ", FieldField<" << pTraits<Type2>::typeName
				<< "> f2(" << f2.size() << ')'
				<< " and FieldField<" << pTraits<Type3>::typeName
				<< "> f3(" << f3.size() << ')'
				<< endl << "    for operation " << op
				<< abort(FatalError);
		}
	}

#else

	template<template<class> class Field, class Type1, class Type2>
	void checkFields
	(
		const FieldField<Field, Type1>&,
		const FieldField<Field, Type2>&,
		const char* op
	)
	{}

	template<template<class> class Field, class Type1, class Type2, class Type3>
	void checkFields
	(
		const FieldField<Field, Type1>&,
		const FieldField<Field, Type2>&,
		const FieldField<Field, Type3>&,
		const char* op
	)
	{}

#endif


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField()
		:
		PtrList<Field<Type>>()
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(const label size)
		:
		PtrList<Field<Type>>(size)
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField
	(
		const word& type,
		const FieldField<Field, Type>& ff
	)
		:
		PtrList<Field<Type>>(ff.size())
	{
		forAll(*this, i)
		{
			set(i, Field<Type>::New(type, ff[i]));
		}
	}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(const FieldField<Field, Type>& f)
		:
		tmp<FieldField<Field, Type>>::refCount(),
		PtrList<Field<Type>>(f)
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(FieldField<Field, Type>&& f)
		:
		tmp<FieldField<Field, Type>>::refCount(),
		PtrList<Field<Type>>(move(f))
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(FieldField<Field, Type>& f, bool reuse)
		:
		PtrList<Field<Type>>(f, reuse)
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(const PtrList<Field<Type>>& tl)
		:
		PtrList<Field<Type>>(tl)
	{}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(const tmp<FieldField<Field, Type>>& tf)
		:
		PtrList<Field<Type>>
		(
			const_cast<FieldField<Field, Type>&>(tf()),
			tf.isTmp()
			)
	{
		tf.clear();
	}


	template<template<class> class Field, class Type>
	FieldField<Field, Type>::FieldField(Istream& is)
		:
		PtrList<Field<Type>>(is)
	{}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> FieldField<Field, Type>::clone() const
	{
		return tmp<FieldField<Field, Type>>(new FieldField<Field, Type>(*this));
	}


	template<template<class> class Field, class Type>
	template<class Type2>
	tmp<FieldField<Field, Type>> FieldField<Field, Type>::NewCalculatedType
	(
		const FieldField<Field, Type2>& ff
	)
	{
		FieldField<Field, Type>* nffPtr
		(
			new FieldField<Field, Type>(ff.size())
		);

		forAll(*nffPtr, i)
		{
			nffPtr->set(i, Field<Type>::NewCalculatedType(ff[i]).ptr());
		}

		return tmp<FieldField<Field, Type>>(nffPtr);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::negate()
	{
		forAll(*this, i)
		{
			this->operator[](i).negate();
		}
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>>
		FieldField<Field, Type>::component
		(
			const direction d
		) const
	{
		tmp<FieldField<Field, cmptType>> Component
		(
			FieldField<Field, typename FieldField<Field, Type>::cmptType>::
			NewCalculatedType(*this)
		);

		::tnbLib::component(Component.ref(), *this, d);

		return Component;
	}


	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::replace
	(
		const direction d,
		const FieldField<Field, cmptType>& sf
	)
	{
		forAll(*this, i)
		{
			this->operator[](i).replace(d, sf[i]);
		}
	}


	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::replace
	(
		const direction d,
		const cmptType& s
	)
	{
		forAll(*this, i)
		{
			this->operator[](i).replace(d, s);
		}
	}


	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> FieldField<Field, Type>::T() const
	{
		tmp<FieldField<Field, Type>> transpose
		(
			FieldField<Field, Type>::NewCalculatedType(*this)
		);

		::tnbLib::T(transpose.ref(), *this);
		return transpose;
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::operator=(const FieldField<Field, Type>& f)
	{
		if (this == &f)
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		forAll(*this, i)
		{
			this->operator[](i) = f[i];
		}
	}


	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::operator=(FieldField<Field, Type>&& f)
	{
		if (this == &f)
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		PtrList<Field<Type>>::operator=(move(f));
	}


	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::operator=(const tmp<FieldField>& tf)
	{
		if (this == &(tf()))
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		// This is dodgy stuff, don't try this at home.
		FieldField* fieldPtr = tf.ptr();
		PtrList<Field<Type>>::transfer(*fieldPtr);
		delete fieldPtr;
	}


	template<template<class> class Field, class Type>
	void FieldField<Field, Type>::operator=(const Type& t)
	{
		forAll(*this, i)
		{
			this->operator[](i) = t;
		}
	}


//#define COMPUTED_ASSIGNMENT(TYPE, op)                                          \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//void FieldField<Field, Type>::operator op(const FieldField<Field, TYPE>& f)    \
//{                                                                              \
//    forAll(*this, i)                                                           \
//    {                                                                          \
//        this->operator[](i) op f[i];                                           \
//    }                                                                          \
//}                                                                              \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//void FieldField<Field, Type>::operator op                                      \
//(                                                                              \
//    const tmp<FieldField<Field, TYPE>>& tf                                     \
//)                                                                              \
//{                                                                              \
//    operator op(tf());                                                         \
//    tf.clear();                                                                \
//}                                                                              \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//void FieldField<Field, Type>::operator op(const TYPE& t)                       \
//{                                                                              \
//    forAll(*this, i)                                                           \
//    {                                                                          \
//        this->operator[](i) op t;                                              \
//    }                                                                          \
//}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator +=(const FieldField<Field, Type>& f)
	{
		forAll(*this, i) { this->operator[](i) += f[i]; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator +=(const tmp<FieldField<Field, Type>>& tf)
	{
		operator +=(tf());
		tf.clear();
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator +=(const Type& t)
	{
		forAll(*this, i) { this->operator[](i) += t; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator -=(const FieldField<Field, Type>& f)
	{
		forAll(*this, i) { this->operator[](i) -= f[i]; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator -=(const tmp<FieldField<Field, Type>>& tf)
	{
		operator -=(tf());
		tf.clear();
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator -=(const Type& t)
	{
		forAll(*this, i) { this->operator[](i) -= t; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator *=(const FieldField<Field, scalar>& f)
	{
		forAll(*this, i) { this->operator[](i) *= f[i]; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator *=(const tmp<FieldField<Field, scalar>>& tf)
	{
		operator *=(tf());
		tf.clear();
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator *=(const scalar& t)
	{
		forAll(*this, i) { this->operator[](i) *= t; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator /=(const FieldField<Field, scalar>& f)
	{
		forAll(*this, i) { this->operator[](i) /= f[i]; }
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator /=(const tmp<FieldField<Field, scalar>>& tf)
	{
		operator /=(tf());
		tf.clear();
	}

	template <template<class> class Field, class Type>
	void FieldField<Field, Type>::operator /=(const scalar& t)
	{
		forAll(*this, i) { this->operator[](i) /= t; }
	}

//#undef COMPUTED_ASSIGNMENT


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	Ostream& operator<<(Ostream& os, const FieldField<Field, Type>& f)
	{
		os << static_cast<const PtrList<Field<Type>>&>(f);
		return os;
	}


	template<template<class> class Field, class Type>
	Ostream& operator<<(Ostream& os, const tmp<FieldField<Field, Type>>& tf)
	{
		os << tf();
		tf.clear();
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //