#pragma once
#include <symmTensorField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const DimensionedField<vector, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("sqr" "(" + df1.name() + ')', df1.mesh(), sqr(df1.dimensions())));
		sqr(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const tmp<DimensionedField<vector, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, vector, GeoMesh>::
			New(tdf1, "sqr" "(" + df1.name() + ')', sqr(df1.dimensions())));
		sqr(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> innerSqr(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("innerSqr" "(" + df1.name() + ')', df1.mesh(), sqr(df1.dimensions())));
		innerSqr(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> innerSqr(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "innerSqr" "(" + df1.name() + ')',
				sqr(df1.dimensions())));
		innerSqr(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("tr" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::New(tdf1, "tr" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New("sph" "(" + df1.name() + ')', df1.mesh(),
				transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, symmTensor, GeoMesh>::New(tdf1, "sph" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("symm" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		symm(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "symm" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		symm(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::
			New("twoSymm" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		twoSymm(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "twoSymm" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		twoSymm(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("dev" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		dev(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "dev" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		dev(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("dev2" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		dev2(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "dev2" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		dev2(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("det" "(" + df1.name() + ')', df1.mesh(), pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, symmTensor, GeoMesh>::New(tdf1, "det" "(" + df1.name() + ')',
				pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("cof" "(" + df1.name() + ')', df1.mesh(), pow2(df1.dimensions())));
		cof(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "cof" "(" + df1.name() + ')',
				pow2(df1.dimensions())));
		cof(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("inv" "(" + df1.name() + ')', df1.mesh(), inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')',
				inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			DimensionedField<vector, GeoMesh>::New("*" + df1.name(), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //