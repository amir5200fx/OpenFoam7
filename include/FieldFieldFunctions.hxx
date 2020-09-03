#pragma once
#include <scalarFieldField.hxx>

//#define TEMPLATE template<template<class> class Field, class Type>
//#include <FieldFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

	template<template<class> class Field, class Type>
	void component
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& sf,
		const FieldField<Field, Type>& f,
		const direction d
	);

	template<template<class> class Field, class Type>
	void T(FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);


	template<template<class> class Field, class Type, direction r>
	void pow
	(
		FieldField<Field, typename powProduct<Type, r>::type>& f,
		const FieldField<Field, Type>& vf
	);

	template<template<class> class Field, class Type, direction r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type>>
		pow
		(
			const FieldField<Field, Type>& f, typename powProduct<Type, r>::type
			= pTraits<typename powProduct<Type, r>::type>::zero
		);

	template<template<class> class Field, class Type, direction r>
	tmp<FieldField<Field, typename powProduct<Type, r>::type>>
		pow
		(
			const tmp<FieldField<Field, Type>>& tf, typename powProduct<Type, r>::type
			= pTraits<typename powProduct<Type, r>::type>::zero
		);


	template<template<class> class Field, class Type>
	void sqr
	(
		FieldField<Field, typename outerProduct<Type, Type>::type>& f,
		const FieldField<Field, Type>& vf
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type>>
		sqr(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename outerProduct<Type, Type>::type>>
		sqr(const tmp<FieldField<Field, Type>>& tf);

	template<template<class> class Field, class Type>
	void magSqr(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> magSqr(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> magSqr(const tmp<FieldField<Field, Type>>& tf);

	template<template<class> class Field, class Type>
	void mag(FieldField<Field, scalar>& sf, const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> mag(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, scalar>> mag(const tmp<FieldField<Field, Type>>& tf);


	template<template<class> class Field, class Type>
	void cmptMax
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMax
	(
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMax
	(
		const tmp<FieldField<Field, Type>>& tf
	);


	template<template<class> class Field, class Type>
	void cmptMin
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMin
	(
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptMin
	(
		const tmp<FieldField<Field, Type>>& tf
	);


	template<template<class> class Field, class Type>
	void cmptAv
	(
		FieldField<Field, typename FieldField<Field, Type>::cmptType>& cf,
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptAv
	(
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, typename FieldField<Field, Type>::cmptType>> cmptAv
	(
		const tmp<FieldField<Field, Type>>& tf
	);


	template<template<class> class Field, class Type>
	void cmptMag
	(
		FieldField<Field, Type>& cf,
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMag
	(
		const FieldField<Field, Type>& f
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMag
	(
		const tmp<FieldField<Field, Type>>& tf
	);


//#define TMP_UNARY_FUNCTION(returnType, func)                                   \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//returnType func(const tmp<FieldField<Field, Type>>& tf1);

	template<template<class> class Field, class Type>
	Type max(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> Type max(const tmp<FieldField<Field, Type>>& tf1);

		template<template<class> class Field, class Type>
	Type min(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> Type min(const tmp<FieldField<Field, Type>>& tf1);

		template<template<class> class Field, class Type>
	Type sum(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> Type sum(const tmp<FieldField<Field, Type>>& tf1);

		template<template<class> class Field, class Type>
	scalar sumMag(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> scalar sumMag(const tmp<FieldField<Field, Type>>& tf1);

		template<template<class> class Field, class Type>
	Type average(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> Type average(const tmp<FieldField<Field, Type>>& tf1);


//#define G_UNARY_FUNCTION(returnType, gFunc, func, rFunc)                       \
//                                                                               \
//template<template<class> class Field, class Type>                              \
//returnType gFunc(const FieldField<Field, Type>& f);                            \
//TMP_UNARY_FUNCTION(returnType, gFunc)

		
	template <template<class> class Field, class Type>
	Type gMax(const FieldField<Field, Type>& f);
	template<template<class> class Field, class Type> 
	Type gMax(const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field, class Type>
	Type gMin(const FieldField<Field, Type>& f);
	template<template<class> class Field, class Type> 
	Type gMin(const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field, class Type>
	Type gSum(const FieldField<Field, Type>& f);
	template<template<class> class Field, class Type> 
	Type gSum(const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field, class Type>
	scalar gSumMag(const FieldField<Field, Type>& f);
	template<template<class> class Field, class Type> 
	scalar gSumMag(const tmp<FieldField<Field, Type>>& tf1);

//#undef G_UNARY_FUNCTION


		template<template<class> class Field, class Type>
	Type gAverage(const FieldField<Field, Type>& f);

	template<template<class> class Field, class Type> Type gAverage(const tmp<FieldField<Field, Type>>& tf1);

//#undef TMP_UNARY_FUNCTION


		
	template <template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2);
		
	template <template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2);
		
	template <template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2);
		
	template <template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const tmp<FieldField<Field, Type>>& tf2);

		
	template <template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const Type& s1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	void max(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> max(const tmp<FieldField<Field, Type>>& tf1, const Type& s);
		
	template <template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const Type& s1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	void min(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> min(const tmp<FieldField<Field, Type>>& tf1, const Type& s);
		
	template <template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const Type& s1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	void cmptMultiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptMultiply(const tmp<FieldField<Field, Type>>& tf1, const Type& s);
		
	template <template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const Type& s1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	void cmptDivide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const FieldField<Field, Type>& f1, const Type& s);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> cmptDivide(const tmp<FieldField<Field, Type>>& tf1, const Type& s);


		/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

		
	template <template<class> class Field, class Type>
	void negate(FieldField<Field, Type>& res, const FieldField<Field, Type>& f);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator -(const FieldField<Field, Type>& f);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator -(const tmp<FieldField<Field, Type>>& tf);

		
	template <template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1,
	                                        const tmp<FieldField<Field, scalar>>& tf2);
		
	template <template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, scalar>& f1, const tmp<FieldField<Field, Type>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, scalar>>& tf1,
	                                        const tmp<FieldField<Field, Type>>& tf2);
		
	template <template<class> class Field, class Type>
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const tmp<FieldField<Field, scalar>>& tf2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const FieldField<Field, scalar>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1,
	                                        const tmp<FieldField<Field, scalar>>& tf2);

		
	template <template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const scalar& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const scalar& s1, const FieldField<Field, Type>& f2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const scalar& s1, const tmp<FieldField<Field, Type>>& tf2);
		
	template <template<class> class Field, class Type>
	void multiply(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const FieldField<Field, Type>& f1, const scalar& s2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator *(const tmp<FieldField<Field, Type>>& tf1, const scalar& s2);

		
	template <template<class> class Field, class Type>
	void divide(FieldField<Field, Type>& f, const FieldField<Field, Type>& f1, const scalar& s2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const FieldField<Field, Type>& f1, const scalar& s2);
	template <template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> operator /(const tmp<FieldField<Field, Type>>& tf1, const scalar& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field1, typename product<Type1, Type2>::type>& f,               \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const FieldField<Field2, Type2>& f2                                        \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const FieldField<Field2, Type2>& f2                                        \
//);                                                                             \
//                                                                               \
//template<template<class> class Field, class Type1, class Type2>                \
//tmp<FieldField<Field, typename product<Type1, Type2>::type>>                   \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field, Type1>& f1,                                        \
//    const tmp<FieldField<Field, Type2>>& tf2                                   \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field1, Type1>& f1,                                       \
//    const tmp<FieldField<Field2, Type2>>& tf2                                  \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field1, Type1>>& tf1,                                 \
//    const FieldField<Field2, Type2>& f2                                        \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field1,                                              \
//    template<class> class Field2,                                              \
//    class Type1,                                                               \
//    class Type2                                                                \
//>                                                                              \
//tmp<FieldField<Field1, typename product<Type1, Type2>::type>>                  \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field1, Type1>>& tf1,                                 \
//    const tmp<FieldField<Field2, Type2>>& tf2                                  \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field, typename product<Type, Form>::type>& f,                  \
//    const FieldField<Field, Type>& f1,                                         \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Type, Form>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const FieldField<Field, Type>& f1,                                         \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Type, Form>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const tmp<FieldField<Field, Type>>& tf1,                                   \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//void opFunc                                                                    \
//(                                                                              \
//    FieldField<Field, typename product<Form, Type>::type>& f,                  \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const FieldField<Field, Type>& f1                                          \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Form, Type>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const FieldField<Field, Type>& f1                                          \
//);                                                                             \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    template<class> class Field,                                               \
//    class Type,                                                                \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt                                                            \
//>                                                                              \
//tmp<FieldField<Field, typename product<Form, Type>::type>>                     \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const tmp<FieldField<Field, Type>>& tf1                                    \
//);

		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void add(FieldField<Field1, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	         const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator +(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void add(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	         const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator +(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void add(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	         const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void subtract(FieldField<Field1, typename typeOfSum<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	              const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename typeOfSum<Type1, Type2>::type>> operator -(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(FieldField<Field, typename typeOfSum<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	              const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Type, Form>::type>> operator -(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(FieldField<Field, typename typeOfSum<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	              const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename typeOfSum<Form, Type>::type>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);

		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void outer(FieldField<Field1, typename outerProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	           const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename outerProduct<Type1, Type2>::type>> operator *(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void outer(FieldField<Field, typename outerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	           const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Type, Form>::type>> operator *(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void outer(FieldField<Field, typename outerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	           const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename outerProduct<Form, Type>::type>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void cross(FieldField<Field1, typename crossProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	           const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename crossProduct<Type1, Type2>::type>> operator ^(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void cross(FieldField<Field, typename crossProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	           const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Type, Form>::type>> operator ^(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void cross(FieldField<Field, typename crossProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	           const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename crossProduct<Form, Type>::type>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void dot(FieldField<Field1, typename innerProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	         const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename innerProduct<Type1, Type2>::type>> operator &(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dot(FieldField<Field, typename innerProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	         const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Type, Form>::type>> operator &(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dot(FieldField<Field, typename innerProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	         const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename innerProduct<Form, Type>::type>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);
		
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	void dotdot(FieldField<Field1, typename scalarProduct<Type1, Type2>::type>& f, const FieldField<Field1, Type1>& f1,
	            const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field1, Type1>& f1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field, class Type1, class Type2>
	tmp<FieldField<Field, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field, Type1>& f1, const tmp<FieldField<Field, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const FieldField<Field1, Type1>& f1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field1, Type1>>& tf1, const FieldField<Field2, Type2>& f2);
	template <template<class> class Field1, template<class> class Field2, class Type1, class Type2>
	tmp<FieldField<Field1, typename scalarProduct<Type1, Type2>::type>> operator &&(
		const tmp<FieldField<Field1, Type1>>& tf1, const tmp<FieldField<Field2, Type2>>& tf2);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(FieldField<Field, typename scalarProduct<Type, Form>::type>& f, const FieldField<Field, Type>& f1,
	            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const FieldField<Field, Type>& f1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Type, Form>::type>> operator &&(
		const tmp<FieldField<Field, Type>>& tf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(FieldField<Field, typename scalarProduct<Form, Type>::type>& f, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	            const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const FieldField<Field, Type>& f1);
	template <template<class> class Field, class Type, class Form, class Cmpt, direction nCmpt>
	tmp<FieldField<Field, typename scalarProduct<Form, Type>::type>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<FieldField<Field, Type>>& tf1);

//#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <FieldFieldFunctionsI.hxx>

//#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //