#pragma once
#include <fv.hxx>
#include <HashTable.hxx>
#include <surfaceInterpolate.hxx>
#include <fvMatrix.hxx>
#include <cyclicAMIFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<ddtScheme<Type>> ddtScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing ddtScheme<Type>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Ddt scheme not specified" << endl << endl
					<< "Valid ddt schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename IstreamConstructorTable::iterator cstrIter =
				IstreamConstructorTablePtr_->find(schemeName);

			if (cstrIter == IstreamConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Unknown ddt scheme " << schemeName << nl << nl
					<< "Valid ddt schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		ddtScheme<Type>::~ddtScheme()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> ddtScheme<Type>::fvcDdt
		(
			const volScalarField& alpha,
			const volScalarField& rho,
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			NotImplemented;

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					GeometricField<Type, fvPatchField, volMesh>::null()
					);
		}


		template<class Type>
		tmp<fvMatrix<Type>> ddtScheme<Type>::fvmDdt
		(
			const volScalarField& alpha,
			const volScalarField& rho,
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			NotImplemented;

			return tmp<fvMatrix<Type>>
				(
					new fvMatrix<Type>
					(
						vf,
						alpha.dimensions()*rho.dimensions()
						*vf.dimensions()*dimVol / dimTime
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> ddtScheme<Type>::fvcDdt
		(
			const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
		)
		{
			NotImplemented;

			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				(
					GeometricField<Type, fvsPatchField, surfaceMesh>::null()
					);
		}



		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi,
			const fluxFieldType& phiCorr
		)
		{
			// Courant number limited formulation
			/*
			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
			  - min
				(
					mag(phiCorr)
				   *mesh().time().deltaT()*mesh().deltaCoeffs()/mesh().magSf(),
					scalar(1)
				);
			*/

			// Flux normalised formulation
			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
				- min
				(
					mag(phiCorr)
					/ (mag(phi) + dimensionedScalar("small", phi.dimensions(), SMALL)),
					scalar(1)
				);

			surfaceScalarField& ddtCouplingCoeff = tddtCouplingCoeff.ref();

			surfaceScalarField::Boundary& ccbf = ddtCouplingCoeff.boundaryFieldRef();

			forAll(U.boundaryField(), patchi)
			{
				if
					(
						U.boundaryField()[patchi].fixesValue()
						|| isA<cyclicAMIFvPatch>(mesh().boundary()[patchi])
						)
				{
					ccbf[patchi] = 0.0;
				}
			}

			if (debug > 1)
			{
				InfoInFunction
					<< "ddtCouplingCoeff mean max min = "
					<< gAverage(ddtCouplingCoeff.primitiveField())
					<< " " << gMax(ddtCouplingCoeff.primitiveField())
					<< " " << gMin(ddtCouplingCoeff.primitiveField())
					<< endl;
			}

			return tddtCouplingCoeff;
		}


		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi,
			const fluxFieldType& phiCorr,
			const volScalarField& rho
		)
		{
			return fvcDdtPhiCoeff(U, phi, phiCorr);
		}


		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi
		)
		{
			return fvcDdtPhiCoeff(U, phi, phi - fvc::dotInterpolate(mesh().Sf(), U));
		}


		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi,
			const volScalarField& rho
		)
		{
			return fvcDdtPhiCoeff
			(
				U,
				phi,
				(phi - fvc::dotInterpolate(mesh().Sf(), U))
			);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //