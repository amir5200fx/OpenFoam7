#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<sphericalTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("tr" "(" + df1.name() + ')', df1.mesh(), transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor, GeoMesh>::New(tdf1, "tr" "(" + df1.name() + ')',
				transform(df1.dimensions())));
		tr(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<sphericalTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New("sph" "(" + df1.name() + ')', df1.mesh(),
				transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, sphericalTensor, GeoMesh>::New(
				tdf1, "sph" "(" + df1.name() + ')', transform(df1.dimensions())));
		sph(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<sphericalTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("det" "(" + df1.name() + ')', df1.mesh(), pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, sphericalTensor, GeoMesh>::New(tdf1, "det" "(" + df1.name() + ')',
				pow3(df1.dimensions())));
		det(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> inv(const DimensionedField<sphericalTensor, GeoMesh>& df1)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New("inv" "(" + df1.name() + ')', df1.mesh(), inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, sphericalTensor, GeoMesh>::New(
				tdf1, "inv" "(" + df1.name() + ')', inv(df1.dimensions())));
		inv(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const DimensionedField<sphericalTensor, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New('(' + df1.name() + '|' + df2.name() + ')', df1.mesh(),
				df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, sphericalTensor, GeoMesh>::New(
				tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const DimensionedField<sphericalTensor, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')',
				df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<sphericalTensor, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<sphericalTensor, scalar, scalar, sphericalTensor, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const DimensionedField<sphericalTensor, GeoMesh>& df2)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New('(' + dt1.name() + '|' + df2.name() + ')', df2.mesh(),
				dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), dt1.value(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const scalar& t1,
		const DimensionedField<sphericalTensor, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf2)
	{
		const DimensionedField<sphericalTensor, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, sphericalTensor, GeoMesh>::New(
				tdf2, '(' + dt1.name() + '|' + df2.name() + ')', dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), dt1.value(), tdf2().field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const scalar& t1,
		const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const dimensioned<sphericalTensor>& dt2)
	{
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			DimensionedField<sphericalTensor, GeoMesh>::New('(' + df1.name() + '|' + dt2.name() + ')', df1.mesh(),
				df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), dt2.value());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const sphericalTensor& t2)
	{
		return df1 / dimensioned<sphericalTensor>(t2);
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const dimensioned<sphericalTensor>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<sphericalTensor, GeoMesh>> tRes(
			reuseTmpDimensionedField<sphericalTensor, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + dt2.name() + ')',
				df1.dimensions() / dt2.dimensions()));
		tnbLib::divide(tRes.ref().field(), tdf1().field(), dt2.value());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const sphericalTensor& t2)
	{
		return tdf1 / dimensioned<sphericalTensor>(t2);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //