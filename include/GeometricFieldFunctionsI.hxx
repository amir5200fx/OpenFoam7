#pragma once
#include <GeometricFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void component
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf,
		const direction d
	)
	{
		component(gcf.primitiveFieldRef(), gf.primitiveField(), d);
		component(gcf.boundaryFieldRef(), gf.boundaryField(), d);
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void T
	(
		GeometricField<Type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	)
	{
		T(gf.primitiveFieldRef(), gf1.primitiveField());
		T(gf.boundaryFieldRef(), gf1.boundaryField());
	}


	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		void pow
		(
			GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh>& gf,
			const GeometricField<Type, PatchField, GeoMesh>& gf1
		)
	{
		pow(gf.primitiveFieldRef(), gf1.primitiveField(), r);
		pow(gf.boundaryFieldRef(), gf1.boundaryField(), r);
	}

	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		tmp<GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh>>
		pow
		(
			const GeometricField<Type, PatchField, GeoMesh>& gf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		tmp<GeometricField<powProductType, PatchField, GeoMesh>> tPow
		(
			GeometricField<powProductType, PatchField, GeoMesh>::New
			(
				"pow(" + gf.name() + ',' + name(r) + ')',
				gf.mesh(),
				pow(gf.dimensions(), r)
			)
		);

		pow<Type, r, PatchField, GeoMesh>(tPow.ref(), gf);

		return tPow;
	}


	template
		<
		class Type,
		template<class> class PatchField,
		class GeoMesh,
		direction r
		>
		tmp<GeometricField<typename powProduct<Type, r>::type, PatchField, GeoMesh>>
		pow
		(
			const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf,
			typename powProduct<Type, r>::type
		)
	{
		typedef typename powProduct<Type, r>::type powProductType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<powProductType, PatchField, GeoMesh>> tPow
		(
			GeometricField<powProductType, PatchField, GeoMesh>::New
			(
				"pow(" + gf.name() + ',' + name(r) + ')',
				gf.mesh(),
				pow(gf.dimensions(), r)
			)
		);

		pow<Type, r, PatchField, GeoMesh>(tPow.ref(), gf);

		tgf.clear();

		return tPow;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void sqr
	(
		GeometricField
		<typename outerProduct<Type, Type>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1
	)
	{
		sqr(gf.primitiveFieldRef(), gf1.primitiveField());
		sqr(gf.boundaryFieldRef(), gf1.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		tmp<GeometricField<outerProductType, PatchField, GeoMesh>> tSqr
		(
			GeometricField<outerProductType, PatchField, GeoMesh>::New
			(
				"sqr(" + gf.name() + ')',
				gf.mesh(),
				sqr(gf.dimensions())
			)
		);

		sqr(tSqr.ref(), gf);

		return tSqr;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename outerProduct<Type, Type>::type,
		PatchField,
		GeoMesh
		>
		>
		sqr(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf)
	{
		typedef typename outerProduct<Type, Type>::type outerProductType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<outerProductType, PatchField, GeoMesh>> tSqr
		(
			GeometricField<outerProductType, PatchField, GeoMesh>::New
			(
				"sqr(" + gf.name() + ')',
				gf.mesh(),
				sqr(gf.dimensions())
			)
		);

		sqr(tSqr.ref(), gf);

		tgf.clear();

		return tSqr;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void magSqr
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		magSqr(gsf.primitiveFieldRef(), gf.primitiveField());
		magSqr(gsf.boundaryFieldRef(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> magSqr
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tMagSqr
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"magSqr(" + gf.name() + ')',
				gf.mesh(),
				sqr(gf.dimensions())
			)
		);

		magSqr(tMagSqr.ref(), gf);

		return tMagSqr;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> magSqr
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf
	)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tMagSqr
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"magSqr(" + gf.name() + ')',
				gf.mesh(),
				sqr(gf.dimensions())
			)
		);

		magSqr(tMagSqr.ref(), gf);

		tgf.clear();

		return tMagSqr;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void mag
	(
		GeometricField<scalar, PatchField, GeoMesh>& gsf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		mag(gsf.primitiveFieldRef(), gf.primitiveField());
		mag(gsf.boundaryFieldRef(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> mag
	(
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		tmp<GeometricField<scalar, PatchField, GeoMesh>> tMag
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"mag(" + gf.name() + ')',
				gf.mesh(),
				gf.dimensions()
			)
		);

		mag(tMag.ref(), gf);

		return tMag;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> mag
	(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf
	)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<scalar, PatchField, GeoMesh>> tMag
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"mag(" + gf.name() + ')',
				gf.mesh(),
				gf.dimensions()
			)
		);

		mag(tMag.ref(), gf);

		tgf.clear();

		return tMag;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptAv
	(
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>& gcf,
		const GeometricField<Type, PatchField, GeoMesh>& gf
	)
	{
		cmptAv(gcf.primitiveFieldRef(), gf.primitiveField());
		cmptAv(gcf.boundaryFieldRef(), gf.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		typedef typename GeometricField<Type, PatchField, GeoMesh>::cmptType
			cmptType;

		tmp<GeometricField<cmptType, PatchField, GeoMesh>> CmptAv
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"cmptAv(" + gf.name() + ')',
				gf.mesh(),
				gf.dimensions()
			)
		);

		cmptAv(CmptAv.ref(), gf);

		return CmptAv;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp
		<
		GeometricField
		<
		typename GeometricField<Type, PatchField, GeoMesh>::cmptType,
		PatchField,
		GeoMesh
		>
		>
		cmptAv(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf)
	{
		typedef typename GeometricField<Type, PatchField, GeoMesh>::cmptType
			cmptType;

		const GeometricField<Type, PatchField, GeoMesh>& gf = tgf();

		tmp<GeometricField<cmptType, PatchField, GeoMesh>> CmptAv
		(
			GeometricField<scalar, PatchField, GeoMesh>::New
			(
				"cmptAv(" + gf.name() + ')',
				gf.mesh(),
				gf.dimensions()
			)
		);

		cmptAv(CmptAv.ref(), gf);

		tgf.clear();

		return CmptAv;
	}


//#define UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY(returnType, func, gFunc)        \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf                        \
//)                                                                              \
//{                                                                              \
//    return dimensioned<Type>                                                   \
//    (                                                                          \
//        #func "(" + gf.name() + ')',                                           \
//        gf.dimensions(),                                                       \
//        tnbLib::func(gFunc(gf.primitiveField()), gFunc(gf.boundaryField()))      \
//    );                                                                         \
//}                                                                              \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//)                                                                              \
//{                                                                              \
//    dimensioned<returnType> res = func(tgf1());                                \
//    tgf1.clear();                                                              \
//    return res;                                                                \
//}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("max" "(" + gf.name() + ')', gf.dimensions(),
			tnbLib::max(gMax(gf.primitiveField()), gMax(gf.boundaryField())));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = max(tgf1());
		tgf1.clear();
		return res;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("min" "(" + gf.name() + ')', gf.dimensions(),
			tnbLib::min(gMin(gf.primitiveField()), gMin(gf.boundaryField())));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = min(tgf1());
		tgf1.clear();
		return res;
	}

//#undef UNARY_REDUCTION_FUNCTION_WITH_BOUNDARY


//#define UNARY_REDUCTION_FUNCTION(returnType, func, gFunc)                      \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf                        \
//)                                                                              \
//{                                                                              \
//    return dimensioned<Type>                                                   \
//    (                                                                          \
//        #func "(" + gf.name() + ')',                                           \
//        gf.dimensions(),                                                       \
//        gFunc(gf.primitiveField())                                             \
//    );                                                                         \
//}                                                                              \
//                                                                               \
//template<class Type, template<class> class PatchField, class GeoMesh>          \
//dimensioned<returnType> func                                                   \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//)                                                                              \
//{                                                                              \
//    dimensioned<returnType> res = func(tgf1());                                \
//    tgf1.clear();                                                              \
//    return res;                                                                \
//}


	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("sum" "(" + gf.name() + ')', gf.dimensions(), gSum(gf.primitiveField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> sum(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = sum(tgf1());
		tgf1.clear();
		return res;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("sumMag" "(" + gf.name() + ')', gf.dimensions(), gSumMag(gf.primitiveField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<scalar> sumMag(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<scalar> res = sumMag(tgf1());
		tgf1.clear();
		return res;
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const GeometricField<Type, PatchField, GeoMesh>& gf)
	{
		return dimensioned<Type>("average" "(" + gf.name() + ')', gf.dimensions(), gAverage(gf.primitiveField()));
	}

	template <class Type, template<class> class PatchField, class GeoMesh>
	dimensioned<Type> average(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		dimensioned<Type> res = average(tgf1());
		tgf1.clear();
		return res;
	}

//#undef UNARY_REDUCTION_FUNCTION


	template<class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::max(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::max(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"max" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.mesh(), max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "max" "(" + gf1.name() + ',' + gf2.name() + ')',
				max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "max" "(" + gf1.name() + ',' + gf2.name() + ')',
				max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "max" "(" + gf1.name() + ',' + gf2.name() + ')', max(gf1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::min(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::min(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"min" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.mesh(), min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "min" "(" + gf1.name() + ',' + gf2.name() + ')',
				min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "min" "(" + gf1.name() + ',' + gf2.name() + ')',
				min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "min" "(" + gf1.name() + ',' + gf2.name() + ')', min(gf1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::cmptMultiply(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.mesh(),
			cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')', cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptMultiply" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptMultiply(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptDivide(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::cmptDivide(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', gf1.mesh(), cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')', cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, "cmptDivide" "(" + gf1.name() + ',' + gf2.name() + ')',
				cmptDivide(gf1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::max(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::max(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"max" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.mesh(), max(dt1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return max(dimensioned<Type>(t1), gf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const dimensioned<Type>& dt1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "max" "(" + dt1.name() + gf2.name() + ',' + ')',
				max(dt1.dimensions(), gf2.dimensions())));
		tnbLib::max(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const Type& t1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return max(dimensioned<Type>(t1), tgf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void max(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tnbLib::max(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::max(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"max" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.mesh(), max(gf1.dimensions(), dt2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const Type& t2) {
		return max(gf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "max" "(" + gf1.name() + ',' + dt2.name() + ')',
				max(gf1.dimensions(), dt2.dimensions())));
		tnbLib::max(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> max(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const Type& t2) {
		return max(tgf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::min(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::min(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"min" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.mesh(), min(dt1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return min(dimensioned<Type>(t1), gf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const dimensioned<Type>& dt1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, "min" "(" + dt1.name() + gf2.name() + ',' + ')',
				min(dt1.dimensions(), gf2.dimensions())));
		tnbLib::min(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const Type& t1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return min(dimensioned<Type>(t1), tgf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void min(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tnbLib::min(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::min(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"min" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.mesh(), min(gf1.dimensions(), dt2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const Type& t2) {
		return min(gf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "min" "(" + gf1.name() + ',' + dt2.name() + ')',
				min(gf1.dimensions(), dt2.dimensions())));
		tnbLib::min(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> min(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const Type& t2) {
		return min(tgf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptMultiply(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::cmptMultiply(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptMultiply" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.mesh(),
			cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return cmptMultiply(dimensioned<Type>(t1), gf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const dimensioned<Type>& dt1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptMultiply" "(" + dt1.name() + gf2.name() + ',' + ')', cmptMultiply(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const Type& t1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return cmptMultiply(dimensioned<Type>(t1), tgf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptMultiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tnbLib::cmptMultiply(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::cmptMultiply(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.mesh(),
			cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const Type& t2)
	{
		return cmptMultiply(gf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptMultiply" "(" + gf1.name() + ',' + dt2.name() + ')', cmptMultiply(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptMultiply(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptMultiply(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const Type& t2)
	{
		return cmptMultiply(tgf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cmptDivide(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::cmptDivide(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptDivide" "(" + dt1.name() + ',' + gf2.name() + ')', gf2.mesh(), cmptDivide(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return cmptDivide(dimensioned<Type>(t1), gf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const dimensioned<Type>& dt1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf2, "cmptDivide" "(" + dt1.name() + gf2.name() + ',' + ')', cmptDivide(dt1.dimensions(), gf2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const Type& t1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return cmptDivide(dimensioned<Type>(t1), tgf2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void cmptDivide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tnbLib::cmptDivide(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::cmptDivide(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<Type>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(GeometricField<Type, PatchField, GeoMesh>::New(
			"cmptDivide" "(" + gf1.name() + ',' + dt2.name() + ')', gf1.mesh(), cmptDivide(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const Type& t2)
	{
		return cmptDivide(gf1, dimensioned<Type>(t2));
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<Type>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(
			tgf1, "cmptDivide" "(" + gf1.name() + ',' + dt2.name() + ')', cmptDivide(gf1.dimensions(), dt2.dimensions())));
		tnbLib::cmptDivide(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> cmptDivide(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const Type& t2)
	{
		return cmptDivide(tgf1, dimensioned<Type>(t2));
	}


	// * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void negate(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::negate(res.primitiveFieldRef(), gf1.primitiveField());
		tnbLib::negate(res.boundaryFieldRef(), gf1.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New("-" + gf1.name(), gf1.mesh(), transform(gf1.dimensions())));
		tnbLib::negate(tRes.ref(), gf1);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator -(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, "-" + gf1.name(), transform(gf1.dimensions())));
		tnbLib::negate(tRes.ref(), gf1);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::multiply(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + gf1.name() + '*' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::multiply(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + gf1.name() + '*' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<scalar, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, scalar, scalar, Type, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '*' + gf2.name() + ')', gf1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, scalar, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const GeometricField<scalar, PatchField, GeoMesh>& gf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + gf2.name() + ')',
				gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<scalar, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<scalar, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpTmpGeometricField<Type, Type, Type, scalar, PatchField, GeoMesh>::New(
				tgf1, tgf2, '(' + gf1.name() + '|' + gf2.name() + ')', gf1.dimensions() / gf2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const dimensioned<scalar>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tnbLib::multiply(res.primitiveFieldRef(), dt1.value(), gf2.primitiveField());
		tnbLib::multiply(res.boundaryFieldRef(), dt1.value(), gf2.boundaryField());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + dt1.name() + '*' + gf2.name() + ')', gf2.mesh(),
				dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), dt1, gf2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
		const GeometricField<Type, PatchField, GeoMesh>& gf2)
	{
		return dimensioned<scalar>(t1) * gf2;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const dimensioned<scalar>& dt1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf2, '(' + dt1.name() + '*' + gf2.name() + ')',
				dt1.dimensions() * gf2.dimensions()));
		tnbLib::multiply(tRes.ref(), dt1, gf2);
		tgf2.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const scalar& t1,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf2)
	{
		return dimensioned<scalar>(t1) * tgf2;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void multiply(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tnbLib::multiply(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::multiply(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + gf1.name() + '*' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const scalar& t2) {
		return gf1 * dimensioned<scalar>(t2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<scalar>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '*' + dt2.name() + ')',
				gf1.dimensions() * dt2.dimensions()));
		tnbLib::multiply(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator *(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const scalar& t2) {
		return tgf1 * dimensioned<scalar>(t2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	void divide(GeometricField<Type, PatchField, GeoMesh>& res, const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tnbLib::divide(res.primitiveFieldRef(), gf1.primitiveField(), dt2.value());
		tnbLib::divide(res.boundaryFieldRef(), gf1.boundaryField(), dt2.value());
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const dimensioned<scalar>& dt2)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			GeometricField<Type, PatchField, GeoMesh>::New('(' + gf1.name() + '|' + dt2.name() + ')', gf1.mesh(),
				gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const GeometricField<Type, PatchField, GeoMesh>& gf1,
		const scalar& t2) {
		return gf1 / dimensioned<scalar>(t2);
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const dimensioned<scalar>& dt2)
	{
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<Type, PatchField, GeoMesh>> tRes(
			reuseTmpGeometricField<Type, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + '|' + dt2.name() + ')',
				gf1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref(), gf1, dt2);
		tgf1.clear();
		return tRes;
	}

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> operator /(const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,
		const scalar& t2) {
		return tgf1 / dimensioned<scalar>(t2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define PRODUCT_OPERATOR(product, op, opFunc)                                  \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Type1, Type2>::type, PatchField, GeoMesh>& gf,           \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//)                                                                              \
//{                                                                              \
//    tnbLib::opFunc                                                               \
//    (                                                                          \
//        gf.primitiveFieldRef(),                                                \
//        gf1.primitiveField(),                                                  \
//        gf2.primitiveField()                                                   \
//    );                                                                         \
//    tnbLib::opFunc                                                               \
//    (                                                                          \
//        gf.boundaryFieldRef(),                                                 \
//        gf1.boundaryField(),                                                   \
//        gf2.boundaryField()                                                    \
//    );                                                                         \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh>  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes                 \
//    (                                                                          \
//        GeometricField<productType, PatchField, GeoMesh>::New                  \
//        (                                                                      \
//            '(' + gf1.name() + #op + gf2.name() + ')',                         \
//            gf1.mesh(),                                                        \
//            gf1.dimensions() op gf2.dimensions()                               \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, gf2);                                        \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh>  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1,                     \
//    const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2                \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//                                                                               \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();            \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes =               \
//        reuseTmpGeometricField<productType, Type2, PatchField, GeoMesh>::New   \
//        (                                                                      \
//            tgf2,                                                              \
//            '(' + gf1.name() + #op + gf2.name() + ')',                         \
//            gf1.dimensions() op gf2.dimensions()                               \
//        );                                                                     \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, gf2);                                        \
//                                                                               \
//    tgf2.clear();                                                              \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh>  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,               \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2                      \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//                                                                               \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();            \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes =               \
//        reuseTmpGeometricField<productType, Type1, PatchField, GeoMesh>::New   \
//        (                                                                      \
//            tgf1,                                                              \
//            '(' + gf1.name() + #op + gf2.name() + ')',                         \
//            gf1.dimensions() op gf2.dimensions()                               \
//        );                                                                     \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, gf2);                                        \
//                                                                               \
//    tgf1.clear();                                                              \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Type1, class Type2, template<class> class PatchField, class GeoMesh>    \
//tmp                                                                            \
//<                                                                              \
//    GeometricField<typename product<Type1, Type2>::type, PatchField, GeoMesh>  \
//>                                                                              \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,               \
//    const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2                \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type1, Type2>::type productType;                  \
//                                                                               \
//    const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();            \
//    const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();            \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes =               \
//        reuseTmpTmpGeometricField                                              \
//        <productType, Type1, Type1, Type2, PatchField, GeoMesh>::New           \
//        (                                                                      \
//            tgf1,                                                              \
//            tgf2,                                                              \
//            '(' + gf1.name() + #op + gf2.name() + ')',                         \
//            gf1.dimensions() op gf2.dimensions()                               \
//        );                                                                     \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, gf2);                                        \
//                                                                               \
//    tgf1.clear();                                                              \
//    tgf2.clear();                                                              \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Type, Form>::type, PatchField, GeoMesh>& gf,             \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const dimensioned<Form>& dvs                                               \
//)                                                                              \
//{                                                                              \
//    tnbLib::opFunc(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());   \
//    tnbLib::opFunc(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());     \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp<GeometricField<typename product<Type, Form>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const dimensioned<Form>& dvs                                               \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes                 \
//    (                                                                          \
//        GeometricField<productType, PatchField, GeoMesh>::New                  \
//        (                                                                      \
//            '(' + gf1.name() + #op + dvs.name() + ')',                         \
//            gf1.mesh(),                                                        \
//            gf1.dimensions() op dvs.dimensions()                               \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, dvs);                                        \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1,                      \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    return gf1 op dimensioned<Form>(static_cast<const Form&>(vs));             \
//}                                                                              \
//                                                                               \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp<GeometricField<typename product<Type, Form>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,                \
//    const dimensioned<Form>& dvs                                               \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Type, Form>::type productType;                    \
//                                                                               \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();             \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes =               \
//        reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::New    \
//        (                                                                      \
//            tgf1,                                                              \
//            '(' + gf1.name() + #op + dvs.name() + ')',                         \
//            gf1.dimensions() op dvs.dimensions()                               \
//        );                                                                     \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), gf1, dvs);                                        \
//                                                                               \
//    tgf1.clear();                                                              \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1,                \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs                                     \
//)                                                                              \
//{                                                                              \
//    return tgf1 op dimensioned<Form>(static_cast<const Form&>(vs));            \
//}                                                                              \
//                                                                               \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//void opFunc                                                                    \
//(                                                                              \
//    GeometricField                                                             \
//    <typename product<Form, Type>::type, PatchField, GeoMesh>& gf,             \
//    const dimensioned<Form>& dvs,                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//)                                                                              \
//{                                                                              \
//    tnbLib::opFunc(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());   \
//    tnbLib::opFunc(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());     \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes                 \
//    (                                                                          \
//        GeometricField<productType, PatchField, GeoMesh>::New                  \
//        (                                                                      \
//            '(' + dvs.name() + #op + gf1.name() + ')',                         \
//            gf1.mesh(),                                                        \
//            dvs.dimensions() op gf1.dimensions()                               \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), dvs, gf1);                                        \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1                       \
//)                                                                              \
//{                                                                              \
//    return dimensioned<Form>(static_cast<const Form&>(vs)) op gf1;             \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<class Form, class Type, template<class> class PatchField, class GeoMesh>      \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const dimensioned<Form>& dvs,                                              \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//)                                                                              \
//{                                                                              \
//    typedef typename product<Form, Type>::type productType;                    \
//                                                                               \
//    const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();             \
//                                                                               \
//    tmp<GeometricField<productType, PatchField, GeoMesh>> tRes =               \
//        reuseTmpGeometricField<productType, Type, PatchField, GeoMesh>::New    \
//        (                                                                      \
//            tgf1,                                                              \
//            '(' + dvs.name() + #op + gf1.name() + ')',                         \
//            dvs.dimensions() op gf1.dimensions()                               \
//        );                                                                     \
//                                                                               \
//    tnbLib::opFunc(tRes.ref(), dvs, gf1);                                        \
//                                                                               \
//    tgf1.clear();                                                              \
//                                                                               \
//    return tRes;                                                               \
//}                                                                              \
//                                                                               \
//template                                                                       \
//<                                                                              \
//    class Form,                                                                \
//    class Cmpt,                                                                \
//    direction nCmpt,                                                           \
//    class Type, template<class> class PatchField,                              \
//    class GeoMesh                                                              \
//>                                                                              \
//tmp<GeometricField<typename product<Form, Type>::type, PatchField, GeoMesh>>   \
//operator op                                                                    \
//(                                                                              \
//    const VectorSpace<Form,Cmpt,nCmpt>& vs,                                    \
//    const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1                 \
//)                                                                              \
//{                                                                              \
//    return dimensioned<Form>(static_cast<const Form&>(vs)) op tgf1;            \
//}


	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::add(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::add(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "+" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() + gf2.dimensions()));
		tnbLib::add(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "+" + gf2.name() + ')',
				gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "+" + gf2.name() + ')',
				gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "+" + gf2.name() + ')',
				gf1.dimensions() + gf2.dimensions());
		tnbLib::add(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::add(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::add(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "+" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() + dvs.dimensions()));
		tnbLib::add(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "+" + dvs.name() + ')',
				gf1.dimensions() + dvs.dimensions());
		tnbLib::add(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 + dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void add(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf, const dimensioned<Form>& dvs,
		const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::add(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::add(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "+" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() + gf1.dimensions()));
		tnbLib::add(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "+" + gf1.name() + ')',
				dvs.dimensions() + gf1.dimensions());
		tnbLib::add(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator +(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) + tgf1;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1,
		const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::subtract(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::subtract(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "-" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() - gf2.dimensions()));
		tnbLib::subtract(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "-" + gf2.name() + ')',
				gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "-" + gf2.name() + ')',
				gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type1, Type2>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename typeOfSum<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "-" + gf2.name() + ')',
				gf1.dimensions() - gf2.dimensions());
		tnbLib::subtract(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::subtract(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::subtract(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "-" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() - dvs.dimensions()));
		tnbLib::subtract(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Type, Form>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename typeOfSum<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "-" + dvs.name() + ')',
				gf1.dimensions() - dvs.dimensions());
		tnbLib::subtract(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 - dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void subtract(GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>& gf,
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::subtract(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::subtract(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "-" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() - gf1.dimensions()));
		tnbLib::subtract(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename typeOfSum<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "-" + gf1.name() + ')',
				dvs.dimensions() - gf1.dimensions());
		tnbLib::subtract(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename typeOfSum<Form, Type>::type, PatchField, GeoMesh>> operator -(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) - tgf1;
	}


	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1,
		const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::outer(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::outer(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "*" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() * gf2.dimensions()));
		tnbLib::outer(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "*" + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "*" + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename outerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "*" + gf2.name() + ')',
				gf1.dimensions() * gf2.dimensions());
		tnbLib::outer(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::outer(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::outer(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "*" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() * dvs.dimensions()));
		tnbLib::outer(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Type, Form>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename outerProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "*" + dvs.name() + ')',
				gf1.dimensions() * dvs.dimensions());
		tnbLib::outer(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 * dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void outer(GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::outer(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::outer(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "*" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() * gf1.dimensions()));
		tnbLib::outer(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename outerProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "*" + gf1.name() + ')',
				dvs.dimensions() * gf1.dimensions());
		tnbLib::outer(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename outerProduct<Form, Type>::type, PatchField, GeoMesh>> operator *(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) * tgf1;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1,
		const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::cross(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::cross(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "^" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() ^ gf2.dimensions()));
		tnbLib::cross(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "^" + gf2.name() + ')',
				gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "^" + gf2.name() + ')',
				gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename crossProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "^" + gf2.name() + ')',
				gf1.dimensions() ^ gf2.dimensions());
		tnbLib::cross(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::cross(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::cross(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "^" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() ^ dvs.dimensions()));
		tnbLib::cross(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Type, Form>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename crossProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "^" + dvs.name() + ')',
				gf1.dimensions() ^ dvs.dimensions());
		tnbLib::cross(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 ^ dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void cross(GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::cross(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::cross(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "^" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() ^ gf1.dimensions()));
		tnbLib::cross(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename crossProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "^" + gf1.name() + ')',
				dvs.dimensions() ^ gf1.dimensions());
		tnbLib::cross(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename crossProduct<Form, Type>::type, PatchField, GeoMesh>> operator ^(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) ^ tgf1;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dot(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::dot(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "&" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() & gf2.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "&" + gf2.name() + ')',
				gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&" + gf2.name() + ')',
				gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename innerProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "&" + gf2.name() + ')',
				gf1.dimensions() & gf2.dimensions());
		tnbLib::dot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::dot(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::dot(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "&" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() & dvs.dimensions()));
		tnbLib::dot(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Type, Form>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename innerProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&" + dvs.name() + ')',
				gf1.dimensions() & dvs.dimensions());
		tnbLib::dot(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 & dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dot(GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dot(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::dot(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "&" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() & gf1.dimensions()));
		tnbLib::dot(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename innerProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "&" + gf1.name() + ')',
				dvs.dimensions() & gf1.dimensions());
		tnbLib::dot(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename innerProduct<Form, Type>::type, PatchField, GeoMesh>> operator &(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) & tgf1;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type1, PatchField, GeoMesh>& gf1,
		const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		tnbLib::dotdot(gf.primitiveFieldRef(), gf1.primitiveField(), gf2.primitiveField());
		tnbLib::dotdot(gf.boundaryFieldRef(), gf1.boundaryField(), gf2.boundaryField());
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "&&" + gf2.name() + ')', gf1.mesh(),
				gf1.dimensions() && gf2.dimensions()));
		tnbLib::dotdot(tRes.ref(), gf1, gf2);
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type1, PatchField, GeoMesh>& gf1, const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type2, PatchField, GeoMesh>::New(tgf2, '(' + gf1.name() + "&&" + gf2.name() + ')',
				gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes.ref(), gf1, gf2);
		tgf2.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1, const GeometricField<Type2, PatchField, GeoMesh>& gf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type1, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&&" + gf2.name() + ')',
				gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		return tRes;
	}

	template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type1, Type2>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type1, PatchField, GeoMesh>>& tgf1,
		const tmp<GeometricField<Type2, PatchField, GeoMesh>>& tgf2)
	{
		typedef typename scalarProduct<Type1, Type2>::type productType;
		const GeometricField<Type1, PatchField, GeoMesh>& gf1 = tgf1();
		const GeometricField<Type2, PatchField, GeoMesh>& gf2 = tgf2();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpTmpGeometricField<
			productType, Type1, Type1, Type2, PatchField, GeoMesh>::New(tgf1, tgf2, '(' + gf1.name() + "&&" + gf2.name() + ')',
				gf1.dimensions() && gf2.dimensions());
		tnbLib::dotdot(tRes.ref(), gf1, gf2);
		tgf1.clear();
		tgf2.clear();
		return tRes;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>& gf,
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		tnbLib::dotdot(gf.primitiveFieldRef(), gf1.primitiveField(), dvs.value());
		tnbLib::dotdot(gf.boundaryFieldRef(), gf1.boundaryField(), dvs.value());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + gf1.name() + "&&" + dvs.name() + ')', gf1.mesh(),
				gf1.dimensions() && dvs.dimensions()));
		tnbLib::dotdot(tRes.ref(), gf1, dvs);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const GeometricField<Type, PatchField, GeoMesh>& gf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return gf1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Type, Form>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const dimensioned<Form>& dvs)
	{
		typedef typename scalarProduct<Type, Form>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + gf1.name() + "&&" + dvs.name() + ')',
				gf1.dimensions() && dvs.dimensions());
		tnbLib::dotdot(tRes.ref(), gf1, dvs);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1, const VectorSpace<Form, Cmpt, nCmpt>& vs)
	{
		return tgf1 && dimensioned<Form>(static_cast<const Form&>(vs));
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	void dotdot(GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>& gf,
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		tnbLib::dotdot(gf.primitiveFieldRef(), dvs.value(), gf1.primitiveField());
		tnbLib::dotdot(gf.boundaryFieldRef(), dvs.value(), gf1.boundaryField());
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes(
			GeometricField<productType, PatchField, GeoMesh>::New('(' + dvs.name() + "&&" + gf1.name() + ')', gf1.mesh(),
				dvs.dimensions() && gf1.dimensions()));
		tnbLib::dotdot(tRes.ref(), dvs, gf1);
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const GeometricField<Type, PatchField, GeoMesh>& gf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && gf1;
	}

	template <class Form, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const dimensioned<Form>& dvs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		typedef typename scalarProduct<Form, Type>::type productType;
		const GeometricField<Type, PatchField, GeoMesh>& gf1 = tgf1();
		tmp<GeometricField<productType, PatchField, GeoMesh>> tRes = reuseTmpGeometricField<
			productType, Type, PatchField, GeoMesh>::New(tgf1, '(' + dvs.name() + "&&" + gf1.name() + ')',
				dvs.dimensions() && gf1.dimensions());
		tnbLib::dotdot(tRes.ref(), dvs, gf1);
		tgf1.clear();
		return tRes;
	}

	template <class Form, class Cmpt, direction nCmpt, class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<typename scalarProduct<Form, Type>::type, PatchField, GeoMesh>> operator &&(
		const VectorSpace<Form, Cmpt, nCmpt>& vs, const tmp<GeometricField<Type, PatchField, GeoMesh>>& tgf1)
	{
		return dimensioned<Form>(static_cast<const Form&>(vs)) && tgf1;
	}

//#undef PRODUCT_OPERATOR


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //