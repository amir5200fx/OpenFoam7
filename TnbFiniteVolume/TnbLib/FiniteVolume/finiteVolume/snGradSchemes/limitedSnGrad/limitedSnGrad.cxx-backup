#include <limitedSnGrad.hxx>

#include <fv.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <localMax.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		limitedSnGrad<Type>::~limitedSnGrad()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			limitedSnGrad<Type>::correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const GeometricField<Type, fvsPatchField, surfaceMesh> corr
			(
				correctedScheme_().correction(vf)
			);

			const surfaceScalarField limiter
			(
				min
				(
					limitCoeff_
					*mag(snGradScheme<Type>::snGrad(vf, deltaCoeffs(vf), "SndGrad"))
					/ (
					(1 - limitCoeff_)*mag(corr)
						+ dimensionedScalar(corr.dimensions(), small)
						),
					dimensionedScalar(dimless, 1.0)
				)
			);

			if (fv::debug)
			{
				InfoInFunction
					<< "limiter min: " << min(limiter.primitiveField())
					<< " max: " << max(limiter.primitiveField())
					<< " avg: " << average(limiter.primitiveField()) << endl;
			}

			return limiter * corr;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //