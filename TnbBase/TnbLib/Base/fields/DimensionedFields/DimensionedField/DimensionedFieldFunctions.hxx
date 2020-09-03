#pragma once
#include <DimensionedScalarField.hxx>

//#define TEMPLATE template<class Type, class GeoMesh>
//#include <DimensionedFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * //

	template<class Type, class GeoMesh, direction r>
	tmp<DimensionedField<typename powProduct<Type, r>::type, GeoMesh>>
		pow
		(
			const DimensionedField<Type, GeoMesh>& df,
			typename powProduct<Type, r>::type
		);

	template<class Type, class GeoMesh, direction r>
	tmp<DimensionedField<typename powProduct<Type, r>::type, GeoMesh>>
		pow
		(
			const tmp<DimensionedField<Type, GeoMesh>>& tdf,
			typename powProduct<Type, r>::type
		);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Type>::type, GeoMesh>>
		sqr(const DimensionedField<Type, GeoMesh>& df);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Type>::type, GeoMesh>>
		sqr(const tmp<DimensionedField<Type, GeoMesh>>& tdf);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> magSqr
	(
		const DimensionedField<Type, GeoMesh>& df
	);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> magSqr
	(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf
	);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> mag
	(
		const DimensionedField<Type, GeoMesh>& df
	);

	template<class Type, class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> mag
	(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf
	);

	template<class Type, class GeoMesh>
	tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>
		cmptAv(const DimensionedField<Type, GeoMesh>& df);

	template<class Type, class GeoMesh>
	tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>
		cmptAv(const tmp<DimensionedField<Type, GeoMesh>>& tdf);


//#define UNARY_REDUCTION_FUNCTION(returnType, func, dfunc)                      \
//                                                                               \
//template<class Type, class GeoMesh>                                            \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const DimensionedField<Type, GeoMesh>& df                                  \
//);                                                                             \
//template<class Type, class GeoMesh>                                            \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const tmp<DimensionedField<Type, GeoMesh>>& tdf1                           \
//);

	template <class Type, class GeoMesh>
	dimensioned<Type> max(const DimensionedField<Type, GeoMesh>& df);
	template <class Type, class GeoMesh>
	dimensioned<Type> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type, class GeoMesh>
	dimensioned<Type> min(const DimensionedField<Type, GeoMesh>& df);
	template <class Type, class GeoMesh>
	dimensioned<Type> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type, class GeoMesh>
	dimensioned<Type> sum(const DimensionedField<Type, GeoMesh>& df);
	template <class Type, class GeoMesh>
	dimensioned<Type> sum(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type, class GeoMesh>
	dimensioned<scalar> sumMag(const DimensionedField<Type, GeoMesh>& df);
	template <class Type, class GeoMesh>
	dimensioned<scalar> sumMag(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type, class GeoMesh>
	dimensioned<Type> average(const DimensionedField<Type, GeoMesh>& df);
	template <class Type, class GeoMesh>
	dimensioned<Type> average(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);

//#undef UNARY_REDUCTION_FUNCTION


		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1,
	                                         const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1,
	                                         const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1,
	                                                  const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1,
	                                                  const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                  const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                  const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const dimensioned<Type>& dt1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const Type& t1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const dimensioned<Type>& dt1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const DimensionedField<Type, GeoMesh>& df1, const Type& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> max(const tmp<DimensionedField<Type, GeoMesh>>& tdf2, const Type& t2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const dimensioned<Type>& dt1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const Type& t1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const dimensioned<Type>& dt1,
	                                         const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const DimensionedField<Type, GeoMesh>& df1, const Type& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                         const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> min(const tmp<DimensionedField<Type, GeoMesh>>& tdf2, const Type& t2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                  const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const Type& t1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
	                                                  const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1,
	                                                  const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const DimensionedField<Type, GeoMesh>& df1, const Type& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                  const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptMultiply(const tmp<DimensionedField<Type, GeoMesh>>& tdf2, const Type& t2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const Type& t1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const Type& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1,
	                                                const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const DimensionedField<Type, GeoMesh>& df1, const Type& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const dimensioned<Type>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> cmptDivide(const tmp<DimensionedField<Type, GeoMesh>>& tdf2, const Type& t2);


		// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator -(const DimensionedField<Type, GeoMesh>& df1);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator -(const tmp<DimensionedField<Type, GeoMesh>>& tdf1);

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1,
	                                                const DimensionedField<scalar, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1,
	                                                const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const DimensionedField<scalar, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1,
	                                                const DimensionedField<scalar, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1,
	                                                const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const DimensionedField<scalar, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const tmp<DimensionedField<scalar, GeoMesh>>& tdf2);

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const scalar& t1, const DimensionedField<Type, GeoMesh>& df2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
	                                                const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const scalar& t1, const tmp<DimensionedField<Type, GeoMesh>>& tdf2);
		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1,
	                                                const dimensioned<scalar>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const DimensionedField<Type, GeoMesh>& df1, const scalar& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const dimensioned<scalar>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator *(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const scalar& t2);

		
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1,
	                                                const dimensioned<scalar>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const DimensionedField<Type, GeoMesh>& df1, const scalar& t2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1,
	                                                const dimensioned<scalar>& dt2);
	template <class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>> operator /(const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const scalar& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template<class Type1, class Type2, class GeoMesh>                              \
//tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh>>           \
//operator op                                                                    \
//(                                                                              \
//    const DimensionedField<Type1, GeoMesh>& df1,                               \
//    const DimensionedField<Type2, GeoMesh>& df2                                \
//);                                                                             \
//                                                                               \
//template<class Type1, class Type2, class GeoMesh>                              \
//tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh>>           \
//operator op                                                                    \
//(                                                                              \
//    const DimensionedField<Type1, GeoMesh>& df1,                               \
//    const tmp<DimensionedField<Type2, GeoMesh>>& tdf2                          \
//);                                                                             \
//                                                                               \
//template<class Type1, class Type2, class GeoMesh>                              \
//tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh>>           \
//operator op                                                                    \
//(                                                                              \
//    const tmp<DimensionedField<Type1, GeoMesh>>& tdf1,                         \
//    const DimensionedField<Type2, GeoMesh>& df2                                \
//);                                                                             \
//                                                                               \
//template<class Type1, class Type2, class GeoMesh>                              \
//tmp<DimensionedField<typename product<Type1, Type2>::type, GeoMesh>>           \
//operator op                                                                    \
//(                                                                              \
//    const tmp<DimensionedField<Type1, GeoMesh>>& tdf1,                         \
//    const tmp<DimensionedField<Type2, GeoMesh>>& tdf2                          \
//);                                                                             \
//                                                                               \
//template<class Form, class Type, class GeoMesh>                                \
//tmp<DimensionedField<typename product<Type, Form>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const DimensionedField<Type, GeoMesh>& df1,                                \
//    const dimensioned<Form>& dvs                                               \
//);                                                                             \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>   \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const DimensionedField<Type, GeoMesh>& df1,                                \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template<class Form, class Type, class GeoMesh>                                \
//tmp<DimensionedField<typename product<Type, Form>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const tmp<DimensionedField<Type, GeoMesh>>& tdf1,                          \
//    const dimensioned<Form>& dvs                                               \
//);                                                                             \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>   \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const tmp<DimensionedField<Type, GeoMesh>>& tdf1,                          \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//);                                                                             \
//                                                                               \
//template<class Form, class Type, class GeoMesh>                                \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const DimensionedField<Type, GeoMesh>& df1                                 \
//);                                                                             \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>   \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const DimensionedField<Type, GeoMesh>& df1                                 \
//);                                                                             \
//                                                                               \
//template<class Form, class Type, class GeoMesh>                                \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const tmp<DimensionedField<Type, GeoMesh>>& tdf1                           \
//);                                                                             \
//                                                                               \
//template<class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>   \
//tmp<DimensionedField<typename product<Form, Type>::type, GeoMesh>>             \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const tmp<DimensionedField<Type, GeoMesh>>& tdf1                           \
//);

		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator +(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type1, Type2>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator -(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Type, Form>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename typeOfSum<Form, Type>::type, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);

		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type1, Type2>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Form>::type, GeoMesh>> operator *(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Type, Form>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename outerProduct<Form, Type>::type, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type1, Type2>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type, Form>::type, GeoMesh>> operator ^(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Type, Form>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename crossProduct<Form, Type>::type, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type1, Type2>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type, Form>::type, GeoMesh>> operator &(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Type, Form>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename innerProduct<Form, Type>::type, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
		
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const DimensionedField<Type1, GeoMesh>& df1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const DimensionedField<Type1, GeoMesh>& df1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const DimensionedField<Type2, GeoMesh>& df2);
	template <class Type1, class Type2, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type1, Type2>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type1, GeoMesh>>& tdf1, const tmp<DimensionedField<Type2, GeoMesh>>& tdf2);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type, Form>::type, GeoMesh>> operator &&(
		const DimensionedField<Type, GeoMesh>& df1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const DimensionedField<Type, GeoMesh>& df1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Type, Form>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const dimensioned<Form>& dvs);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf1, const VectorSpace<Form, Cmpt, nCmpt>& vs);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const DimensionedField<Type, GeoMesh>& df1);
	template <class Form, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);
	template <class Form, class Cmpt, direction nCmpt, class Type, class GeoMesh>
	tmp<DimensionedField<typename scalarProduct<Form, Type>::type, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<DimensionedField<Type, GeoMesh>>& tdf1);

//#undef PRODUCT_OPERATOR


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <DimensionedFieldFunctions_Imp.hxx>

//#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //