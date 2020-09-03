#pragma once
#include <tensorField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("tr" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, tensor, GeoMesh>::New(tdf1, "tr" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New("sph" "(" + df1.name() + ')', df1.mesh(),
				transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, tensor, GeoMesh>::New(tdf1, "sph" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::New("symm" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		symm(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::New(tdf1, "symm" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		symm(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::
			New("twoSymm" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		twoSymm(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, tensor, GeoMesh>::New(tdf1, "twoSymm" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		twoSymm(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> skew(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("skew" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		skew(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> skew(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "skew" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		skew(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("dev" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		dev(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "dev" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		dev(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev2(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("dev2" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		dev2(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> dev2(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "dev2" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		dev2(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("det" "(" + df1.name() + ')', df1.mesh(), pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, tensor, GeoMesh>::New(tdf1, "det" "(" + df1.name() + ')', pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> cof(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("cof" "(" + df1.name() + ')', df1.mesh(), pow2(df1.dimensions())));
		cof(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> cof(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "cof" "(" + df1.name() + ')', pow2(df1.dimensions())));
		cof(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> inv(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("inv" "(" + df1.name() + ')', df1.mesh(), inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> inv(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			DimensionedField<vector, GeoMesh>::New("eigenValues" "(" + df1.name() + ')', df1.mesh(),
				transform(df1.dimensions())));
		eigenValues(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, tensor, GeoMesh>::New(tdf1, "eigenValues" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		eigenValues(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> eigenVectors(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("eigenVectors" "(" + df1.name() + ')', df1.mesh(), sign(df1.dimensions())));
		eigenVectors(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> eigenVectors(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, tensor, GeoMesh>::New(tdf1, "eigenVectors" "(" + df1.name() + ')',
				sign(df1.dimensions())));
		eigenVectors(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			DimensionedField<vector, GeoMesh>::New("eigenValues" "(" + df1.name() + ')', df1.mesh(),
				transform(df1.dimensions())));
		eigenValues(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> eigenValues(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, symmTensor, GeoMesh>::New(tdf1, "eigenValues" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		eigenValues(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> eigenVectors(const DimensionedField<symmTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			DimensionedField<symmTensor, GeoMesh>::
			New("eigenVectors" "(" + df1.name() + ')', df1.mesh(), sign(df1.dimensions())));
		eigenVectors(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> eigenVectors(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<symmTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<symmTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<symmTensor, symmTensor, GeoMesh>::New(tdf1, "eigenVectors" "(" + df1.name() + ')',
				sign(df1.dimensions())));
		eigenVectors(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const DimensionedField<tensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			DimensionedField<vector, GeoMesh>::New("*" + df1.name(), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const tmp<DimensionedField<tensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<tensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<vector, GeoMesh>> tRes(
			reuseTmpDimensionedField<vector, tensor, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> operator *(const DimensionedField<vector, GeoMesh>& df1)
	{
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			DimensionedField<tensor, GeoMesh>::New("*" + df1.name(), df1.mesh(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<tensor, GeoMesh>> operator *(const tmp<DimensionedField<vector, GeoMesh>>& tdf1)
	{
		const DimensionedField<vector, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<tensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<tensor, vector, GeoMesh>::New(tdf1, "*" + df1.name(), transform(df1.dimensions())));
		tnbLib::hdual(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //