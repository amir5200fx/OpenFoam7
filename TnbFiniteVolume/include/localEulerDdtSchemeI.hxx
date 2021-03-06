#pragma once
#include <surfaceInterpolate.hxx>
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
		const volScalarField& localEulerDdtScheme<Type>::localRDeltaT() const
		{
			return localEulerDdt::localRDeltaT(mesh());
		}


		template<class Type>
		const surfaceScalarField& localEulerDdtScheme<Type>::localRDeltaTf() const
		{
			return localEulerDdt::localRDeltaTf(mesh());
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const dimensioned<Type>& dt
			)
		{
			IOobject ddtIOobject
			(
				"ddt(" + dt.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						mesh(),
						dimensioned<Type>
						(
							"0",
							dt.dimensions() / dimTime,
							Zero
							),
						calculatedFvPatchField<Type>::typeName
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const volScalarField& rDeltaT = localRDeltaT();

			IOobject ddtIOobject
			(
				"ddt(" + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						rDeltaT*(vf - vf.oldTime())
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const volScalarField& rDeltaT = localRDeltaT();

			IOobject ddtIOobject
			(
				"ddt(" + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						rDeltaT*rho*(vf - vf.oldTime())
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const volScalarField& rDeltaT = localRDeltaT();

			IOobject ddtIOobject
			(
				"ddt(" + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						rDeltaT*(rho*vf - rho.oldTime()*vf.oldTime())
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const volScalarField& rDeltaT = localRDeltaT();

			IOobject ddtIOobject
			(
				"ddt(" + alpha.name() + ',' + rho.name() + ',' + vf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvPatchField, volMesh>>
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						ddtIOobject,
						rDeltaT
						*(
							alpha*rho*vf
							- alpha.oldTime()*rho.oldTime()*vf.oldTime()
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			localEulerDdtScheme<Type>::fvcDdt
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
			)
		{
			const surfaceScalarField& rDeltaT = localRDeltaTf();

			IOobject ddtIOobject
			(
				"ddt(" + sf.name() + ')',
				mesh().time().timeName(),
				mesh()
			);

			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				(
					new GeometricField<Type, fvsPatchField, surfaceMesh>
					(
						ddtIOobject,
						rDeltaT*(sf - sf.oldTime())
						)
					);
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			localEulerDdtScheme<Type>::fvmDdt
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

			fvMatrix<Type>& fvm = tfvm.ref();

			const scalarField& rDeltaT = localRDeltaT();

			fvm.diag() = rDeltaT * mesh().Vsc();
			fvm.source() = rDeltaT * vf.oldTime().primitiveField()*mesh().Vsc();

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			localEulerDdtScheme<Type>::fvmDdt
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
			fvMatrix<Type>& fvm = tfvm.ref();

			const scalarField& rDeltaT = localRDeltaT();

			fvm.diag() = rDeltaT * rho.value()*mesh().Vsc();

			fvm.source() =
				rDeltaT * rho.value()*vf.oldTime().primitiveField()*mesh().Vsc();

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			localEulerDdtScheme<Type>::fvmDdt
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
			fvMatrix<Type>& fvm = tfvm.ref();

			const scalarField& rDeltaT = localRDeltaT();

			fvm.diag() = rDeltaT * rho.primitiveField()*mesh().Vsc();

			fvm.source() = rDeltaT
				* rho.oldTime().primitiveField()
				*vf.oldTime().primitiveField()*mesh().Vsc();

			return tfvm;
		}


		template<class Type>
		tmp<fvMatrix<Type>>
			localEulerDdtScheme<Type>::fvmDdt
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
			fvMatrix<Type>& fvm = tfvm.ref();

			const scalarField& rDeltaT = localRDeltaT();

			fvm.diag() =
				rDeltaT * alpha.primitiveField()*rho.primitiveField()*mesh().Vsc();

			fvm.source() = rDeltaT
				* alpha.oldTime().primitiveField()
				*rho.oldTime().primitiveField()
				*vf.oldTime().primitiveField()*mesh().Vsc();

			return tfvm;
		}


		/*
		// Courant number limited formulation
		template<class Type>
		tmp<surfaceScalarField> localEulerDdtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi,
			const fluxFieldType& phiCorr
		)
		{
			// Courant number limited formulation
			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
			  - min
				(
					mag(phiCorr)*mesh().deltaCoeffs()
				   /(fvc::interpolate(localRDeltaT())*mesh().magSf()),
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
		*/


		template<class Type>
		tmp<typename localEulerDdtScheme<Type>::fluxFieldType>
			localEulerDdtScheme<Type>::fvcDdtUfCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			const surfaceScalarField rDeltaT(fvc::interpolate(localRDeltaT()));

			fluxFieldType phiUf0(mesh().Sf() & Uf.oldTime());
			fluxFieldType phiCorr
			(
				phiUf0 - fvc::dotInterpolate(mesh().Sf(), U.oldTime())
			);

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
						this->fvcDdtPhiCoeff(U.oldTime(), phiUf0, phiCorr)
						*rDeltaT*phiCorr
					)
					);
		}


		template<class Type>
		tmp<typename localEulerDdtScheme<Type>::fluxFieldType>
			localEulerDdtScheme<Type>::fvcDdtPhiCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			const surfaceScalarField rDeltaT(fvc::interpolate(localRDeltaT()));

			fluxFieldType phiCorr
			(
				phi.oldTime() - fvc::dotInterpolate(mesh().Sf(), U.oldTime())
			);

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
						this->fvcDdtPhiCoeff(U.oldTime(), phi.oldTime(), phiCorr)
						*rDeltaT*phiCorr
					)
					);
		}


		template<class Type>
		tmp<typename localEulerDdtScheme<Type>::fluxFieldType>
			localEulerDdtScheme<Type>::fvcDdtUfCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			)
		{
			const surfaceScalarField rDeltaT(fvc::interpolate(localRDeltaT()));

			if
				(
					U.dimensions() == dimVelocity
					&& Uf.dimensions() == dimDensity * dimVelocity
					)
			{
				GeometricField<Type, fvPatchField, volMesh> rhoU0
				(
					rho.oldTime()*U.oldTime()
				);

				fluxFieldType phiUf0(mesh().Sf() & Uf.oldTime());
				fluxFieldType phiCorr(phiUf0 - fvc::dotInterpolate(mesh().Sf(), rhoU0));

				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtCorr("
								+ rho.name() + ',' + U.name() + ',' + Uf.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							this->fvcDdtPhiCoeff(rhoU0, phiUf0, phiCorr, rho.oldTime())
							*rDeltaT*phiCorr
						)
						);
			}
			else if
				(
					U.dimensions() == dimDensity * dimVelocity
					&& Uf.dimensions() == dimDensity * dimVelocity
					)
			{
				fluxFieldType phiUf0(mesh().Sf() & Uf.oldTime());
				fluxFieldType phiCorr
				(
					phiUf0 - fvc::dotInterpolate(mesh().Sf(), U.oldTime())
				);

				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtCorr("
								+ rho.name() + ',' + U.name() + ',' + Uf.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							this->fvcDdtPhiCoeff
							(
								U.oldTime(),
								phiUf0,
								phiCorr,
								rho.oldTime()
							)*rDeltaT*phiCorr
						)
						);
			}
			else
			{
				FatalErrorInFunction
					<< "dimensions of Uf are not correct"
					<< abort(FatalError);

				return fluxFieldType::null();
			}
		}


		template<class Type>
		tmp<typename localEulerDdtScheme<Type>::fluxFieldType>
			localEulerDdtScheme<Type>::fvcDdtPhiCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			)
		{
			const surfaceScalarField rDeltaT(fvc::interpolate(localRDeltaT()));

			if
				(
					U.dimensions() == dimVelocity
					&& phi.dimensions() == rho.dimensions()*dimVelocity*dimArea
					)
			{
				GeometricField<Type, fvPatchField, volMesh> rhoU0
				(
					rho.oldTime()*U.oldTime()
				);

				fluxFieldType phiCorr
				(
					phi.oldTime() - fvc::dotInterpolate(mesh().Sf(), rhoU0)
				);

				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtCorr("
								+ rho.name() + ',' + U.name() + ',' + phi.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							this->fvcDdtPhiCoeff
							(
								rhoU0,
								phi.oldTime(),
								phiCorr,
								rho.oldTime()
							)*rDeltaT*phiCorr
						)
						);
			}
			else if
				(
					U.dimensions() == rho.dimensions()*dimVelocity
					&& phi.dimensions() == rho.dimensions()*dimVelocity*dimArea
					)
			{
				fluxFieldType phiCorr
				(
					phi.oldTime() - fvc::dotInterpolate(mesh().Sf(), U.oldTime())
				);

				return tmp<fluxFieldType>
					(
						new fluxFieldType
						(
							IOobject
							(
								"ddtCorr("
								+ rho.name() + ',' + U.name() + ',' + phi.name() + ')',
								mesh().time().timeName(),
								mesh()
							),
							this->fvcDdtPhiCoeff
							(
								U.oldTime(),
								phi.oldTime(),
								phiCorr,
								rho.oldTime()
							)*rDeltaT*phiCorr
						)
						);
			}
			else
			{
				FatalErrorInFunction
					<< "dimensions of phi are not correct"
					<< abort(FatalError);

				return fluxFieldType::null();
			}
		}


		template<class Type>
		tmp<surfaceScalarField> localEulerDdtScheme<Type>::meshPhi
		(
			const GeometricField<Type, fvPatchField, volMesh>&
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