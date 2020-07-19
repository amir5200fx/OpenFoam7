#include <fvcVolumeIntegrate.hxx>

#include <fvMesh.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<Field<Type>>
			volumeIntegrate
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return vf.mesh().V()*vf.primitiveField();
		}


		template<class Type>
		tmp<Field<Type>>
			volumeIntegrate
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			)
		{
			tmp<Field<Type>> tvivf = tvf().mesh().V()*tvf().primitiveField();
			tvf.clear();
			return tvivf;
		}


		template<class Type>
		tmp<Field<Type>> volumeIntegrate(const DimensionedField<Type, volMesh>& df)
		{
			return df.mesh().V()*df.field();
		}


		template<class Type>
		tmp<Field<Type>>
			volumeIntegrate(const tmp<DimensionedField<Type, volMesh>>& tdf)
		{
			tmp<Field<Type>> tdidf = tdf().mesh().V()*tdf().field();
			tdf.clear();
			return tdidf;
		}


		template<class Type>
		dimensioned<Type>
			domainIntegrate
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return dimensioned<Type>
				(
					"domainIntegrate(" + vf.name() + ')',
					dimVol*vf.dimensions(),
					gSum(fvc::volumeIntegrate(vf))
					);
		}


		template<class Type>
		dimensioned<Type> domainIntegrate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
		)
		{
			dimensioned<Type> integral = domainIntegrate(tvf());
			tvf.clear();
			return integral;
		}


		template<class Type>
		dimensioned<Type> domainIntegrate
		(
			const DimensionedField<Type, volMesh>& df
		)
		{
			return dimensioned<Type>
				(
					"domainIntegrate(" + df.name() + ')',
					dimVol*df.dimensions(),
					gSum(fvc::volumeIntegrate(df))
					);
		}


		template<class Type>
		dimensioned<Type> domainIntegrate
		(
			const tmp<DimensionedField<Type, volMesh>>& tdf
		)
		{
			dimensioned<Type> integral = domainIntegrate(tdf());
			tdf.clear();
			return integral;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //