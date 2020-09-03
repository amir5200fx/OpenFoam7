#pragma once
//#define TEMPLATE template<class Type>
//#include <FieldFunctionsM.hxx>
#include <UPstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	template<class Type>
	void component
	(
		Field<typename Field<Type>::cmptType>& res,
		const UList<Type>& f,
		const direction d
	);


	template<class Type>
	void T(Field<Type>& res, const UList<Type>& f);


	template<class Type, direction r>
	void pow
	(
		Field<typename powProduct<Type, r>::type>& res,
		const UList<Type>& vf
	);


	template<class Type, direction r>
	tmp<Field<typename powProduct<Type, r>::type>>
		pow
		(
			const UList<Type>& f,
			typename powProduct<Type, r>::type
			= pTraits<typename powProduct<Type, r>::type>::zero
		);

	template<class Type, direction r>
	tmp<Field<typename powProduct<Type, r>::type>>
		pow
		(
			const tmp<Field<Type>>& tf,
			typename powProduct<Type, r>::type
			= pTraits<typename powProduct<Type, r>::type>::zero
		);


	template<class Type>
	void sqr
	(
		Field<typename outerProduct<Type, Type>::type>& res,
		const UList<Type>& vf
	);

	template<class Type>
	tmp<Field<typename outerProduct<Type, Type>::type>>
		sqr(const UList<Type>& f);

	template<class Type>
	tmp<Field<typename outerProduct<Type, Type>::type>>
		sqr(const tmp<Field<Type>>& tf);


	template<class Type>
	void magSqr(Field<scalar>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<scalar>> magSqr(const UList<Type>& f);

	template<class Type>
	tmp<Field<scalar>> magSqr(const tmp<Field<Type>>& tf);


	template<class Type>
	void mag(Field<scalar>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<scalar>> mag(const UList<Type>& f);

	template<class Type>
	tmp<Field<scalar>> mag(const tmp<Field<Type>>& tf);


	template<class Type>
	void cmptMax(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMax(const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>>
		cmptMax(const tmp<Field<Type>>& tf);


	template<class Type>
	void cmptMin(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptMin(const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>>
		cmptMin(const tmp<Field<Type>>& tf);


	template<class Type>
	void cmptAv(Field<typename Field<Type>::cmptType>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptAv(const UList<Type>& f);

	template<class Type>
	tmp<Field<typename Field<Type>::cmptType>> cmptAv(const tmp<Field<Type>>& tf);


	template<class Type>
	void cmptMag(Field<Type>& res, const UList<Type>& f);

	template<class Type>
	tmp<Field<Type>> cmptMag(const UList<Type>& f);

	template<class Type>
	tmp<Field<Type>> cmptMag(const tmp<Field<Type>>& tf);

//#define TMP_UNARY_FUNCTION(ReturnType, Func)                                   \
//                                                                               \
//template<class Type>                                                           \
//ReturnType Func(const tmp<Field<Type>>& tf1);

	template<class Type>
	Type max(const UList<Type>& f);

	template<class Type> Type max(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type min(const UList<Type>& f);

	template<class Type> Type min(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type sum(const UList<Type>& f);

	template<class Type> Type sum(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type maxMagSqr(const UList<Type>& f);

	template<class Type> Type maxMagSqr(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type minMagSqr(const UList<Type>& f);

	template<class Type> Type minMagSqr(const tmp<Field<Type>>& tf1);


		template<class Type>
	scalar sumProd(const UList<Type>& f1, const UList<Type>& f2);

	template<class Type>
	Type sumCmptProd(const UList<Type>& f1, const UList<Type>& f2);

	template<class Type>
	scalar sumSqr(const UList<Type>& f);

	template<class Type> scalar sumSqr(const tmp<Field<Type>>& tf1);

		template<class Type>
	scalar sumMag(const UList<Type>& f);

	template<class Type> scalar sumMag(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type sumCmptMag(const UList<Type>& f);

	template<class Type> Type sumCmptMag(const tmp<Field<Type>>& tf1);

		template<class Type>
	Type average(const UList<Type>& f);

	template<class Type> Type average(const tmp<Field<Type>>& tf1);


//#define G_UNARY_FUNCTION(ReturnType, gFunc, Func, rFunc)                       \
//                                                                               \
//template<class Type>                                                           \
//ReturnType gFunc(const UList<Type>& f, const label comm = UPstream::worldComm);\
//TMP_UNARY_FUNCTION(ReturnType, gFunc)

		
	template <class Type>
	Type gMax(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gMax(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	Type gMin(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gMin(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	Type gSum(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gSum(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	Type gMaxMagSqr(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gMaxMagSqr(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	Type gMinMagSqr(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gMinMagSqr(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	scalar gSumSqr(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	scalar gSumSqr(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	scalar gSumMag(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	scalar gSumMag(const tmp<Field<Type>>& tf1);
		
	template <class Type>
	Type gSumCmptMag(const UList<Type>& f, const label comm = UPstream::worldComm);
	template <class Type>
	Type gSumCmptMag(const tmp<Field<Type>>& tf1);

//#undef G_UNARY_FUNCTION

		template<class Type>
	scalar gSumProd
	(
		const UList<Type>& f1,
		const UList<Type>& f2,
		const label comm = UPstream::worldComm
	);

	template<class Type>
	Type gSumCmptProd
	(
		const UList<Type>& f1,
		const UList<Type>& f2,
		const label comm = UPstream::worldComm
	);

	template<class Type>
	Type gAverage
	(
		const UList<Type>& f,
		const label comm = UPstream::worldComm
	);

	template<class Type> Type gAverage(const tmp<Field<Type>>& tf1);

//#undef TMP_UNARY_FUNCTION


		
	template <class Type>
	void max(Field<Type>& f, const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const tmp<Field<Type>>& tf2);
	template <class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2);
		
	template <class Type>
	void min(Field<Type>& f, const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const tmp<Field<Type>>& tf2);
	template <class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2);
		
	template <class Type>
	void cmptMultiply(Field<Type>& f, const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const tmp<Field<Type>>& tf2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2);
		
	template <class Type>
	void cmptDivide(Field<Type>& f, const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const tmp<Field<Type>>& tf2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const tmp<Field<Type>>& tf2);

		
	template <class Type>
	void max(Field<Type>& f, const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> max(const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> max(const Type& s1, const tmp<Field<Type>>& tf2);
	template <class Type>
	void max(Field<Type>& f, const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> max(const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> max(const tmp<Field<Type>>& tf1, const Type& s2);
		
	template <class Type>
	void min(Field<Type>& f, const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> min(const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> min(const Type& s1, const tmp<Field<Type>>& tf2);
	template <class Type>
	void min(Field<Type>& f, const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> min(const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> min(const tmp<Field<Type>>& tf1, const Type& s2);
		
	template <class Type>
	void cmptMultiply(Field<Type>& f, const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const Type& s1, const tmp<Field<Type>>& tf2);
	template <class Type>
	void cmptMultiply(Field<Type>& f, const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> cmptMultiply(const tmp<Field<Type>>& tf1, const Type& s2);
		
	template <class Type>
	void cmptDivide(Field<Type>& f, const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const Type& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const Type& s1, const tmp<Field<Type>>& tf2);
	template <class Type>
	void cmptDivide(Field<Type>& f, const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const UList<Type>& f1, const Type& s2);
	template <class Type>
	tmp<Field<Type>> cmptDivide(const tmp<Field<Type>>& tf1, const Type& s2);


		// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

		
	template <class Type>
	void negate(Field<Type>& res, const UList<Type>& f);
	template <class Type>
	tmp<Field<Type>> operator -(const UList<Type>& f);
	template <class Type>
	tmp<Field<Type>> operator -(const tmp<Field<Type>>& tf);

		
	template <class Type>
	void multiply(Field<Type>& f, const UList<Type>& f1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const tmp<Field<scalar>>& tf2);
	template <class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const tmp<Field<scalar>>& tf2);
		
	template <class Type>
	void multiply(Field<Type>& f, const UList<scalar>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const UList<scalar>& f1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const UList<scalar>& f1, const tmp<Field<Type>>& tf2);
	template <class Type>
	tmp<Field<Type>> operator *(const tmp<Field<scalar>>& tf1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const tmp<Field<scalar>>& tf1, const tmp<Field<Type>>& tf2);
		
	template <class Type>
	void divide(Field<Type>& f, const UList<Type>& f1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const tmp<Field<scalar>>& tf2);
	template <class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const UList<scalar>& f2);
	template <class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const tmp<Field<scalar>>& tf2);

		
	template <class Type>
	void multiply(Field<Type>& f, const scalar& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const scalar& s1, const UList<Type>& f2);
	template <class Type>
	tmp<Field<Type>> operator *(const scalar& s1, const tmp<Field<Type>>& tf2);
		
	template <class Type>
	void multiply(Field<Type>& f, const UList<Type>& f1, const scalar& s2);
	template <class Type>
	tmp<Field<Type>> operator *(const UList<Type>& f1, const scalar& s2);
	template <class Type>
	tmp<Field<Type>> operator *(const tmp<Field<Type>>& tf1, const scalar& s2);

		
	template <class Type>
	void divide(Field<Type>& f, const UList<Type>& f1, const scalar& s2);
	template <class Type>
	tmp<Field<Type>> operator /(const UList<Type>& f1, const scalar& s2);
	template <class Type>
	tmp<Field<Type>> operator /(const tmp<Field<Type>>& tf1, const scalar& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, Op, OpFunc)                                  \
//                                                                               \
//template<class Type1, class Type2>                                             \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Type1, Type2>::type>& res,                          \
//    const UList<Type1>& f1,                                                    \
//    const UList<Type2>& f2                                                     \
//);                                                                             \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const UList<Type1>& f1, const UList<Type2>& f2);                   \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);             \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);             \
//                                                                               \
//template<class Type1, class Type2>                                             \
//tmp<Field<typename product<Type1, Type2>::type>>                               \
//operator Op(const tmp<Field<Type1>>& tf1, const tmp<Field<Type2>>& tf2);       \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Type, Form>::type>& res,                            \
//    const UList<Type>& f1,                                                     \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//tmp<Field<typename product<Type, Form>::type>>                                 \
//operator Op(const UList<Type>& f1, const VectorSpace<Form,Cmpt,nCmpt>& vs);    \
//                                                                               \
//template<class Type, class Form, class Cmpt, direction nCmpt>                  \
//tmp<Field<typename product<Type, Form>::type>>                                 \
//operator Op(const tmp<Field<Type>>&tf1,const VectorSpace<Form,Cmpt,nCmpt>&vs); \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//void OpFunc                                                                    \
//(                                                                              \
//    Field<typename product<Form, Type>::type>& res,                            \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const UList<Type>& f1                                                      \
//);                                                                             \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//tmp<Field<typename product<Form, Type>::type>>                                 \
//operator Op(const VectorSpace<Form,Cmpt,nCmpt>& vs, const UList<Type>& f1);    \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type>                  \
//tmp<Field<typename product<Form, Type>::type>>                                 \
//operator Op(const VectorSpace<Form,Cmpt,nCmpt>&vs,const tmp<Field<Type>>&tf1);

		
	template <class Type1, class Type2>
	void add(Field<typename typeOfSum<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator +(const tmp<Field<Type1>>& tf1,
	                                                              const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void add(Field<typename typeOfSum<Type, Form>::type>& res, const UList<Type>& f1,
	         const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator +(const UList<Type>& f1,
	                                                            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator +(const tmp<Field<Type>>& tf1,
	                                                            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void add(Field<typename typeOfSum<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	         const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator +(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                            const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator +(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                            const tmp<Field<Type>>& tf1);
		
	template <class Type1, class Type2>
	void subtract(Field<typename typeOfSum<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename typeOfSum<Type1, Type2>::type>> operator -(const tmp<Field<Type1>>& tf1,
	                                                              const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void subtract(Field<typename typeOfSum<Type, Form>::type>& res, const UList<Type>& f1,
	              const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator -(const UList<Type>& f1,
	                                                            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename typeOfSum<Type, Form>::type>> operator -(const tmp<Field<Type>>& tf1,
	                                                            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void subtract(Field<typename typeOfSum<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	              const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator -(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                            const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename typeOfSum<Form, Type>::type>> operator -(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                            const tmp<Field<Type>>& tf1);

		
	template <class Type1, class Type2>
	void outer(Field<typename outerProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename outerProduct<Type1, Type2>::type>> operator *(const tmp<Field<Type1>>& tf1,
	                                                                 const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void outer(Field<typename outerProduct<Type, Form>::type>& res, const UList<Type>& f1,
	           const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename outerProduct<Type, Form>::type>> operator *(const UList<Type>& f1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename outerProduct<Type, Form>::type>> operator *(const tmp<Field<Type>>& tf1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void outer(Field<typename outerProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	           const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename outerProduct<Form, Type>::type>> operator *(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename outerProduct<Form, Type>::type>> operator *(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const tmp<Field<Type>>& tf1);
		
	template <class Type1, class Type2>
	void cross(Field<typename crossProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename crossProduct<Type1, Type2>::type>> operator ^(const tmp<Field<Type1>>& tf1,
	                                                                 const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void cross(Field<typename crossProduct<Type, Form>::type>& res, const UList<Type>& f1,
	           const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename crossProduct<Type, Form>::type>> operator ^(const UList<Type>& f1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename crossProduct<Type, Form>::type>> operator ^(const tmp<Field<Type>>& tf1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void cross(Field<typename crossProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	           const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename crossProduct<Form, Type>::type>> operator ^(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename crossProduct<Form, Type>::type>> operator ^(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const tmp<Field<Type>>& tf1);
		
	template <class Type1, class Type2>
	void dot(Field<typename innerProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const UList<Type1>& f1, const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const tmp<Field<Type1>>& tf1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename innerProduct<Type1, Type2>::type>> operator &(const tmp<Field<Type1>>& tf1,
	                                                                 const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void dot(Field<typename innerProduct<Type, Form>::type>& res, const UList<Type>& f1,
	         const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename innerProduct<Type, Form>::type>> operator &(const UList<Type>& f1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename innerProduct<Type, Form>::type>> operator &(const tmp<Field<Type>>& tf1,
	                                                               const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void dot(Field<typename innerProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	         const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename innerProduct<Form, Type>::type>> operator &(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename innerProduct<Form, Type>::type>> operator &(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                               const tmp<Field<Type>>& tf1);
		
	template <class Type1, class Type2>
	void dotdot(Field<typename scalarProduct<Type1, Type2>::type>& res, const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const UList<Type1>& f1, const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const UList<Type1>& f1,
	                                                                   const tmp<Field<Type2>>& tf2);
	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const tmp<Field<Type1>>& tf1,
	                                                                   const UList<Type2>& f2);
	template <class Type1, class Type2>
	tmp<Field<typename scalarProduct<Type1, Type2>::type>> operator &&(const tmp<Field<Type1>>& tf1,
	                                                                   const tmp<Field<Type2>>& tf2);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	void dotdot(Field<typename scalarProduct<Type, Form>::type>& res, const UList<Type>& f1,
	            const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename scalarProduct<Type, Form>::type>> operator &&(const UList<Type>& f1,
	                                                                 const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Type, class Form, class Cmpt, direction nCmpt>
	tmp<Field<typename scalarProduct<Type, Form>::type>> operator &&(const tmp<Field<Type>>& tf1,
	                                                                 const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	void dotdot(Field<typename scalarProduct<Form, Type>::type>& res, const VectorSpace<Form, Cmpt, nCmpt>& vs,
	            const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename scalarProduct<Form, Type>::type>> operator &&(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                                 const UList<Type>& f1);
	template <class Form, class Cmpt, direction nCmpt, class Type>
	tmp<Field<typename scalarProduct<Form, Type>::type>> operator &&(const VectorSpace<Form, Cmpt, nCmpt>& vs,
	                                                                 const tmp<Field<Type>>& tf1);

//#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <FieldFunctionsI.hxx>
//#include <undefFieldFunctionsM.hxx>
#include <scalarField.hxx>

// ************************************************************************* //