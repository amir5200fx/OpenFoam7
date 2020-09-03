#pragma once
#include <DimensionedFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> stabilise
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const dimensioned<scalar>& ds
	)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"stabilise(" + dsf.name() + ',' + ds.name() + ')',
				dsf.mesh(),
				dsf.dimensions() + ds.dimensions()
			)
		);

		stabilise(tRes.ref().field(), dsf.field(), ds.value());

		return tRes;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> stabilise
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf,
		const dimensioned<scalar>& ds
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh>> tRes = New
		(
			tdsf,
			"stabilise(" + dsf.name() + ',' + ds.name() + ')',
			dsf.dimensions() + ds.dimensions()
		);

		stabilise(tRes.ref().field(), dsf.field(), ds.value());

		tdsf.clear();

		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + dt1.name() + '+' + df2.name() + ')', df2.mesh(), dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes.ref().field(), dt1.value(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) + df2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const dimensioned<scalar>& dt1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '+' + df2.name() + ')',
				dt1.dimensions() + df2.dimensions()));
		tnbLib::add(tRes.ref().field(), dt1.value(), tdf2().field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) + tdf2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1,
		const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + df1.name() + '+' + dt2.name() + ')', df1.mesh(), df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes.ref().field(), df1.field(), dt2.value());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2)
	{
		return df1 + dimensioned<scalar>(t2);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const dimensioned<scalar>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '+' + dt2.name() + ')',
				df1.dimensions() + dt2.dimensions()));
		tnbLib::add(tRes.ref().field(), tdf1().field(), dt2.value());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator +(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 + dimensioned<scalar>(t2);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + dt1.name() + '-' + df2.name() + ')', df2.mesh(), dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes.ref().field(), dt1.value(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) - df2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const dimensioned<scalar>& dt1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '-' + df2.name() + ')',
				dt1.dimensions() - df2.dimensions()));
		tnbLib::subtract(tRes.ref().field(), dt1.value(), tdf2().field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) - tdf2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1,
		const dimensioned<scalar>& dt2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + df1.name() + '-' + dt2.name() + ')', df1.mesh(), df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes.ref().field(), df1.field(), dt2.value());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const DimensionedField<scalar, GeoMesh>& df1, const scalar& t2)
	{
		return df1 - dimensioned<scalar>(t2);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const dimensioned<scalar>& dt2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '-' + dt2.name() + ')',
				df1.dimensions() - dt2.dimensions()));
		tnbLib::subtract(tRes.ref().field(), tdf1().field(), dt2.value());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator -(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1, const scalar& t2)
	{
		return tdf1 - dimensioned<scalar>(t2);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + df1.name() + '*' + df2.name() + ')', df1.mesh(), df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes.ref().field(), df1.field(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const DimensionedField<scalar, GeoMesh>& df1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '*' + df2.name() + ')',
				df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes.ref().field(), df1.field(), df2.field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '*' + df2.name() + ')',
				df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator *(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '*' + df2.name() + ')', df1.dimensions() * df2.dimensions()));
		tnbLib::multiply(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + df1.name() + '|' + df2.name() + ')', df1.mesh(), df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + df1.name() + '|' + df2.name() + ')',
				df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, '(' + df1.name() + '|' + df2.name() + ')',
				df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::New(
				tdf1, tdf2, '(' + df1.name() + '|' + df2.name() + ')', df1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), df1.field(), df2.field());
		tdf1.clear();
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const DimensionedField<scalar, GeoMesh>& df2)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(DimensionedField<scalar, GeoMesh>::New(
			'(' + dt1.name() + '|' + df2.name() + ')', df2.mesh(), dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), dt1.value(), df2.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const scalar& t1, const DimensionedField<scalar, GeoMesh>& df2)
	{
		return dimensioned<scalar>(t1) / df2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		const DimensionedField<scalar, GeoMesh>& df2 = tdf2();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf2, '(' + dt1.name() + '|' + df2.name() + ')',
				dt1.dimensions() / df2.dimensions()));
		tnbLib::divide(tRes.ref().field(), dt1.value(), tdf2().field());
		tdf2.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> operator /(const scalar& t1, const tmp<DimensionedField<scalar, GeoMesh>>& tdf2)
	{
		return dimensioned<scalar>(t1) / tdf2;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		if (!dsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << dsf1.dimensions()
				<< exit(FatalError);
		}

		if (!dsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
				dsf1.mesh(),
				dimless
			)
		);

		pow(tPow.ref().field(), dsf1.field(), dsf2.field());

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();

		if (!dsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << dsf1.dimensions()
				<< exit(FatalError);
		}

		if (!dsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow = New
		(
			tdsf1,
			"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
			dimless
		);

		pow(tPow.ref().field(), dsf1.field(), dsf2.field());

		tdsf1.clear();

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		if (!dsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << dsf1.dimensions()
				<< exit(FatalError);
		}

		if (!dsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow = New
		(
			tdsf2,
			"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
			dimless
		);

		pow(tPow.ref().field(), dsf1.field(), dsf2.field());

		tdsf2.clear();

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		if (!dsf1.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base field is not dimensionless: " << dsf1.dimensions()
				<< exit(FatalError);
		}

		if (!dsf2.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf2.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow =
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::
			New
			(
				tdsf1,
				tdsf2,
				"pow(" + dsf1.name() + ',' + dsf2.name() + ')',
				dimless
			);

		pow(tPow.ref().field(), dsf1.field(), dsf2.field());

		tdsf1.clear();
		tdsf2.clear();

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const dimensionedScalar& ds
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"pow(" + dsf.name() + ',' + ds.name() + ')',
				dsf.mesh(),
				pow(dsf.dimensions(), ds)
			)
		);

		pow(tPow.ref().field(), dsf.field(), ds.value());

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf,
		const dimensionedScalar& ds
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh>> tPow = New
		(
			tdsf,
			"pow(" + dsf.name() + ',' + ds.name() + ')',
			pow(dsf.dimensions(), ds)
		);

		pow(tPow.ref().field(), dsf.field(), ds.value());

		tdsf.clear();

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const scalar& s
	)
	{
		return pow(dsf, dimensionedScalar(s));
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf,
		const scalar& s
	)
	{
		return pow(tdsf, dimensionedScalar(s));
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const dimensionedScalar& ds,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base scalar is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"pow(" + ds.name() + ',' + dsf.name() + ')',
				dsf.mesh(),
				dimless
			)
		);

		pow(tPow.ref().field(), ds.value(), dsf.field());

		return tPow;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const dimensionedScalar& ds,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		if (!ds.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Base scalar is not dimensionless: " << ds.dimensions()
				<< exit(FatalError);
		}

		if (!dsf.dimensions().dimensionless())
		{
			FatalErrorInFunction
				<< "Exponent field is not dimensionless: " << dsf.dimensions()
				<< exit(FatalError);
		}

		tmp<DimensionedField<scalar, GeoMesh>> tPow = New
		(
			tdsf,
			"pow(" + ds.name() + ',' + dsf.name() + ')',
			dimless
		);

		pow(tPow.ref().field(), ds.value(), dsf.field());

		tdsf.clear();

		return tPow;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const scalar& s,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		return pow(dimensionedScalar(s), dsf);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow
	(
		const scalar& s,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf
	)
	{
		return pow(dimensionedScalar(s), tdsf);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tAtan2
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"atan2(" + dsf1.name() + ',' + dsf2.name() + ')',
				dsf1.mesh(),
				atan2(dsf1.dimensions(), dsf2.dimensions())
			)
		);

		atan2(tAtan2.ref().field(), dsf1.field(), dsf2.field());

		return tAtan2;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf1,
		const DimensionedField<scalar, GeoMesh>& dsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();

		tmp<DimensionedField<scalar, GeoMesh>> tAtan2 = New
		(
			tdsf1,
			"atan2(" + dsf1.name() + ',' + dsf2.name() + ')',
			atan2(dsf1.dimensions(), dsf2.dimensions())
		);

		atan2(tAtan2.ref().field(), dsf1.field(), dsf2.field());

		tdsf1.clear();

		return tAtan2;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const DimensionedField<scalar, GeoMesh>& dsf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		tmp<DimensionedField<scalar, GeoMesh>> tAtan2 = New
		(
			tdsf2,
			"atan2(" + dsf1.name() + ',' + dsf2.name() + ')',
			atan2(dsf1.dimensions(), dsf2.dimensions())
		);

		atan2(tAtan2.ref().field(), dsf1.field(), dsf2.field());

		tdsf2.clear();

		return tAtan2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf1,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf2
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf1 = tdsf1();
		const DimensionedField<scalar, GeoMesh>& dsf2 = tdsf2();

		tmp<DimensionedField<scalar, GeoMesh>> tAtan2 =
			reuseTmpTmpDimensionedField<scalar, scalar, scalar, scalar, GeoMesh>::
			New
			(
				tdsf1,
				tdsf2,
				"atan2(" + dsf1.name() + ',' + dsf2.name() + ')',
				atan2(dsf1.dimensions(), dsf2.dimensions())
			);

		atan2(tAtan2.ref().field(), dsf1.field(), dsf2.field());

		tdsf1.clear();
		tdsf2.clear();

		return tAtan2;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const dimensionedScalar& ds
	)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tAtan2
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"atan2(" + dsf.name() + ',' + ds.name() + ')',
				dsf.mesh(),
				atan2(dsf.dimensions(), ds)
			)
		);

		atan2(tAtan2.ref().field(), dsf.field(), ds.value());

		return tAtan2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf,
		const dimensionedScalar& ds
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh>> tAtan2 = New
		(
			tdsf,
			"atan2(" + dsf.name() + ',' + ds.name() + ')',
			atan2(dsf.dimensions(), ds)
		);

		atan2(tAtan2.ref().field(), dsf.field(), ds.value());

		tdsf.clear();

		return tAtan2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const DimensionedField<scalar, GeoMesh>& dsf,
		const scalar& s
	)
	{
		return atan2(dsf, dimensionedScalar(s));
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf,
		const scalar& s
	)
	{
		return atan2(tdsf, dimensionedScalar(s));
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const dimensionedScalar& ds,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tAtan2
		(
			DimensionedField<scalar, GeoMesh>::New
			(
				"atan2(" + ds.name() + ',' + dsf.name() + ')',
				dsf.mesh(),
				atan2(ds, dsf.dimensions())
			)
		);

		atan2(tAtan2.ref().field(), ds.value(), dsf.field());

		return tAtan2;
	}


	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const dimensionedScalar& ds,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf
	)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();

		tmp<DimensionedField<scalar, GeoMesh>> tAtan2 = New
		(
			tdsf,
			"atan2(" + ds.name() + ',' + dsf.name() + ')',
			atan2(ds, dsf.dimensions())
		);

		atan2(tAtan2.ref().field(), ds.value(), dsf.field());

		tdsf.clear();

		return tAtan2;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const scalar& s,
		const DimensionedField<scalar, GeoMesh>& dsf
	)
	{
		return atan2(dimensionedScalar(s), dsf);
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan2
	(
		const scalar& s,
		const tmp<DimensionedField<scalar, GeoMesh>>& tdsf
	)
	{
		return atan2(dimensionedScalar(s), tdsf);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pow3" "(" + df1.name() + ')', df1.mesh(), pow3(df1.dimensions())));
		pow3(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow3(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow3" "(" + df1.name() + ')', pow3(df1.dimensions())));
		pow3(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pow4" "(" + df1.name() + ')', df1.mesh(), pow4(df1.dimensions())));
		pow4(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow4(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow4" "(" + df1.name() + ')', pow4(df1.dimensions())));
		pow4(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pow5" "(" + df1.name() + ')', df1.mesh(), pow5(df1.dimensions())));
		pow5(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow5(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow5" "(" + df1.name() + ')', pow5(df1.dimensions())));
		pow5(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pow6" "(" + df1.name() + ')', df1.mesh(), pow6(df1.dimensions())));
		pow6(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow6(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow6" "(" + df1.name() + ')', pow6(df1.dimensions())));
		pow6(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow025(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pow025" "(" + df1.name() + ')', df1.mesh(), pow025(df1.dimensions())));
		pow025(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pow025(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pow025" "(" + df1.name() + ')',
				pow025(df1.dimensions())));
		pow025(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("sqrt" "(" + df1.name() + ')', df1.mesh(), sqrt(df1.dimensions())));
		sqrt(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sqrt(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sqrt" "(" + df1.name() + ')', sqrt(df1.dimensions())));
		sqrt(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cbrt(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("cbrt" "(" + df1.name() + ')', df1.mesh(), cbrt(df1.dimensions())));
		cbrt(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cbrt(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "cbrt" "(" + df1.name() + ')', cbrt(df1.dimensions())));
		cbrt(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("sign" "(" + df1.name() + ')', df1.mesh(), sign(df1.dimensions())));
		sign(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sign(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sign" "(" + df1.name() + ')', sign(df1.dimensions())));
		sign(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pos" "(" + df1.name() + ')', df1.mesh(), pos(df1.dimensions())));
		pos(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pos" "(" + df1.name() + ')', pos(df1.dimensions())));
		pos(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("pos0" "(" + df1.name() + ')', df1.mesh(), pos0(df1.dimensions())));
		pos0(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> pos0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "pos0" "(" + df1.name() + ')', pos0(df1.dimensions())));
		pos0(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("neg" "(" + df1.name() + ')', df1.mesh(), neg(df1.dimensions())));
		neg(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "neg" "(" + df1.name() + ')', neg(df1.dimensions())));
		neg(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("neg0" "(" + df1.name() + ')', df1.mesh(), neg0(df1.dimensions())));
		neg0(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> neg0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "neg0" "(" + df1.name() + ')', neg0(df1.dimensions())));
		neg0(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> posPart(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("posPart" "(" + df1.name() + ')', df1.mesh(), posPart(df1.dimensions())));
		posPart(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> posPart(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "posPart" "(" + df1.name() + ')',
				posPart(df1.dimensions())));
		posPart(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> negPart(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("negPart" "(" + df1.name() + ')', df1.mesh(), negPart(df1.dimensions())));
		negPart(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> negPart(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "negPart" "(" + df1.name() + ')',
				negPart(df1.dimensions())));
		negPart(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("exp" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		exp(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> exp(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "exp" "(" + df1.name() + ')', trans(df1.dimensions())));
		exp(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("log" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		log(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "log" "(" + df1.name() + ')', trans(df1.dimensions())));
		log(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("log10" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		log10(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> log10(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "log10" "(" + df1.name() + ')', trans(df1.dimensions())));
		log10(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("sin" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		sin(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sin" "(" + df1.name() + ')', trans(df1.dimensions())));
		sin(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("cos" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		cos(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "cos" "(" + df1.name() + ')', trans(df1.dimensions())));
		cos(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("tan" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		tan(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "tan" "(" + df1.name() + ')', trans(df1.dimensions())));
		tan(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("asin" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		asin(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asin(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "asin" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		asin(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("acos" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		acos(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acos(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "acos" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		acos(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("atan" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		atan(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atan(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "atan" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		atan(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("sinh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		sinh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> sinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "sinh" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		sinh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("cosh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		cosh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> cosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "cosh" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		cosh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("tanh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		tanh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "tanh" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		tanh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("asinh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		asinh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> asinh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "asinh" "(" + df1.name() + ')', trans(df1.dimensions())));
		asinh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("acosh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		acosh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> acosh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "acosh" "(" + df1.name() + ')', trans(df1.dimensions())));
		acosh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("atanh" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		atanh(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> atanh(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::
			New(tdf1, "atanh" "(" + df1.name() + ')', trans(df1.dimensions())));
		atanh(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("erf" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		erf(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erf(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "erf" "(" + df1.name() + ')', trans(df1.dimensions())));
		erf(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("erfc" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		erfc(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> erfc(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "erfc" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		erfc(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("lgamma" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		lgamma(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> lgamma(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "lgamma" "(" + df1.name() + ')',
				trans(df1.dimensions())));
		lgamma(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("j0" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		j0(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "j0" "(" + df1.name() + ')', trans(df1.dimensions())));
		j0(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("j1" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		j1(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> j1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "j1" "(" + df1.name() + ')', trans(df1.dimensions())));
		j1(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("y0" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		y0(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y0(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "y0" "(" + df1.name() + ')', trans(df1.dimensions())));
		y0(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const DimensionedField<scalar, GeoMesh>& df1)
	{
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			DimensionedField<scalar, GeoMesh>::New("y1" "(" + df1.name() + ')', df1.mesh(), trans(df1.dimensions())));
		y1(tRes.ref().field(), df1.field());
		return tRes;
	}

	template<class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> y1(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1)
	{
		const DimensionedField<scalar, GeoMesh>& df1 = tdf1();
		tmp<DimensionedField<scalar, GeoMesh>> tRes(
			reuseTmpDimensionedField<scalar, scalar, GeoMesh>::New(tdf1, "y1" "(" + df1.name() + ')', trans(df1.dimensions())));
		y1(tRes.ref().field(), df1.field());
		tdf1.clear();
		return tRes;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#define BesselFunc(func)                                                       \
//                                                                               \
//template<class GeoMesh>                                                        \
//tmp<DimensionedField<scalar, GeoMesh>> func                                    \
//(                                                                              \
//    const int n,                                                               \
//    const DimensionedField<scalar, GeoMesh>& dsf                               \
//)                                                                              \
//{                                                                              \
//    if (!dsf.dimensions().dimensionless())                                     \
//    {                                                                          \
//        FatalErrorInFunction                                                   \
//            << "dsf not dimensionless"                                         \
//            << abort(FatalError);                                              \
//    }                                                                          \
//                                                                               \
//    tmp<DimensionedField<scalar, GeoMesh>> tFunc                               \
//    (                                                                          \
//        DimensionedField<scalar, GeoMesh>::New                                 \
//        (                                                                      \
//            #func "(" + name(n) + ',' + dsf.name() + ')',                      \
//            dsf.mesh(),                                                        \
//            dimless                                                            \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    func(tFunc.ref().field(), n, dsf.field());                                 \
//                                                                               \
//    return tFunc;                                                              \
//}                                                                              \
//                                                                               \
//template<class GeoMesh>                                                        \
//tmp<DimensionedField<scalar, GeoMesh>> func                                    \
//(                                                                              \
//    const int n,                                                               \
//    const tmp<DimensionedField<scalar, GeoMesh>>& tdsf                         \
//)                                                                              \
//{                                                                              \
//    const DimensionedField<scalar, GeoMesh>& dsf = tdsf();                     \
//                                                                               \
//    if (!dsf.dimensions().dimensionless())                                     \
//    {                                                                          \
//        FatalErrorInFunction                                                   \
//            << " : dsf not dimensionless"                                      \
//            << abort(FatalError);                                              \
//    }                                                                          \
//                                                                               \
//    tmp<DimensionedField<scalar, GeoMesh>> tFunc                               \
//    (                                                                          \
//        New                                                                    \
//        (                                                                      \
//            tdsf,                                                              \
//            #func "(" + name(n) + ',' + dsf.name() + ')',                      \
//            dimless                                                            \
//        )                                                                      \
//    );                                                                         \
//                                                                               \
//    func(tFunc.ref().field(), n, dsf.field());                                 \
//                                                                               \
//    tdsf.clear();                                                              \
//                                                                               \
//    return tFunc;                                                              \
//}


	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const DimensionedField<scalar, GeoMesh>& dsf)
	{
		if (!dsf.dimensions().dimensionless()) { FatalErrorInFunction << "dsf not dimensionless" << abort(FatalError); }
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(
			DimensionedField<scalar, GeoMesh>::New("jn" "(" + name(n) + ',' + dsf.name() + ')', dsf.mesh(), dimless));
		jn(tFunc.ref().field(), n, dsf.field());
		return tFunc;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> jn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>& tdsf)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();
		if (!dsf.dimensions().dimensionless()) { FatalErrorInFunction << " : dsf not dimensionless" << abort(FatalError); }
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(New(tdsf, "jn" "(" + name(n) + ',' + dsf.name() + ')', dimless));
		jn(tFunc.ref().field(), n, dsf.field());
		tdsf.clear();
		return tFunc;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const DimensionedField<scalar, GeoMesh>& dsf)
	{
		if (!dsf.dimensions().dimensionless()) { FatalErrorInFunction << "dsf not dimensionless" << abort(FatalError); }
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(
			DimensionedField<scalar, GeoMesh>::New("yn" "(" + name(n) + ',' + dsf.name() + ')', dsf.mesh(), dimless));
		yn(tFunc.ref().field(), n, dsf.field());
		return tFunc;
	}

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> yn(const int n, const tmp<DimensionedField<scalar, GeoMesh>>& tdsf)
	{
		const DimensionedField<scalar, GeoMesh>& dsf = tdsf();
		if (!dsf.dimensions().dimensionless()) { FatalErrorInFunction << " : dsf not dimensionless" << abort(FatalError); }
		tmp<DimensionedField<scalar, GeoMesh>> tFunc(New(tdsf, "yn" "(" + name(n) + ',' + dsf.name() + ')', dimless));
		yn(tFunc.ref().field(), n, dsf.field());
		tdsf.clear();
		return tFunc;
	}

//#undef BesselFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //