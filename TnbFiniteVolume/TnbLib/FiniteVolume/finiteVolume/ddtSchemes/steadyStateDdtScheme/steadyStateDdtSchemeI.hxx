#pragma once
#include <fvcDiv.hxx>
#include <fvMatrices.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const dimensioned<Type>& dt
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + dt.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							dt.dimensions() / dimTime,
							Zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							vf.dimensions() / dimTime,
							Zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + rho.name() + ',' + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							rho.dimensions()*vf.dimensions() / dimTime,
							Zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + rho.name() + ',' + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							rho.dimensions()*vf.dimensions() / dimTime,
							Zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			steadyStateDdtScheme<Type>::fvcDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"ddt(" + alpha.name() + ',' + rho.name() + ',' + vf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<Type>
						(
							"0",
							rho.dimensions()*vf.dimensions() / dimTime,
							Zero
							)
						)
					);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					rho.dimensions()*vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					rho.dimensions()*vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			steadyStateDdtScheme<Type>::fvmDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type>> tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					alpha.dimensions()*rho.dimensions()*vf.dimensions()*dimVol / dimTime
					)
			);

			return tfvm;
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtUfCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						IOobject
						(
							"ddtCorr(" + U.name() + ',' + Uf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<typename flux<Type>::type>
						(
							"0",
							Uf.dimensions()*dimArea / dimTime,
							Zero
							)
					)
					);
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtPhiCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						IOobject
						(
							"ddtCorr(" + U.name() + ',' + phi.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<typename flux<Type>::type>
						(
							"0",
							phi.dimensions() / dimTime,
							Zero
							)
					)
					);
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtUfCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						IOobject
						(
							"ddtCorr("
							+ rho.name()
							+ ',' + U.name() + ',' + Uf.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<typename flux<Type>::type>
						(
							"0",
							Uf.dimensions()*dimArea / dimTime,
							Zero
							)
					)
					);
		}


		template<class Type>
		tmp<typename steadyStateDdtScheme<Type>::fluxFieldType>
			steadyStateDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			return tmp<fluxFieldType>
				(
					new fluxFieldType
					(
						IOobject
						(
							"ddtCorr("
							+ rho.name()
							+ ',' + U.name() + ',' + phi.name() + ')',
							mesh().time().timeName(),
							mesh()
						),
						mesh(),
						dimensioned<typename flux<Type>::type>
						(
							"0",
							phi.dimensions() / dimTime,
							Zero
							)
					)
					);
		}


		template<class Type>
		tmp<surfaceScalarField> steadyStateDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
		{
			return surfaceScalarField::New
			(
				"meshPhi",
				mesh(),
				dimensionedScalar(dimVolume / dimTime, 0)
			);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //