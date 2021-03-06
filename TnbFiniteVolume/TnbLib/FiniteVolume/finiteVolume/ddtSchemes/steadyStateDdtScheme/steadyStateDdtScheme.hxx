#pragma once
#ifndef _steadyStateDdtScheme_Header
#define _steadyStateDdtScheme_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::fv::steadyStateDdtScheme

Description
	SteadyState implicit/explicit ddt which returns 0.

SourceFiles
	steadyStateDdtScheme.C

\*---------------------------------------------------------------------------*/

#include <ddtScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSteadyStateDdtScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamSteadyStateDdtScheme_EXPORT_DEFINE
#define FoamSteadyStateDdtScheme_EXPORT __declspec(dllexport)
#else
#define FoamSteadyStateDdtScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class steadyStateDdtScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class steadyStateDdtScheme
			:
			public fv::ddtScheme<Type>
		{
		public:

			//- Runtime type information
			/*TypeName("steadyState");*/
			static const char* typeName_() { return "steadyState"; }
			static FoamSteadyStateDdtScheme_EXPORT const ::tnbLib::word typeName;
			static FoamSteadyStateDdtScheme_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh
			steadyStateDdtScheme(const fvMesh& mesh)
				:
				ddtScheme<Type>(mesh)
			{}

			//- Construct from mesh and Istream
			steadyStateDdtScheme(const fvMesh& mesh, Istream& is)
				:
				ddtScheme<Type>(mesh, is)
			{}

			//- Disallow default bitwise copy construction
			steadyStateDdtScheme(const steadyStateDdtScheme&) = delete;


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return fv::ddtScheme<Type>::mesh();
			}

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const dimensioned<Type>&
			);

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& psi
			);

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& psi
			);

			typedef typename ddtScheme<Type>::fluxFieldType fluxFieldType;

			virtual tmp<fluxFieldType> fvcDdtUfCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			);

			virtual tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			);

			virtual tmp<fluxFieldType> fvcDdtUfCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			);

			virtual tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			);

			virtual tmp<surfaceScalarField> meshPhi
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const steadyStateDdtScheme&) = delete;
		};


		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtUfCorr
		(
			const GeometricField<scalar, fvPatchField, volMesh>& U,
			const GeometricField<scalar, fvsPatchField, surfaceMesh>& Uf
		);

		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtPhiCorr
		(
			const volScalarField& U,
			const surfaceScalarField& phi
		);

		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtUfCorr
		(
			const volScalarField& rho,
			const volScalarField& U,
			const surfaceScalarField& Uf
		);

		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtPhiCorr
		(
			const volScalarField& rho,
			const volScalarField& U,
			const surfaceScalarField& phi
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <steadyStateDdtSchemeI.hxx>

//#ifdef NoRepository
//#include <steadyStateDdtScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_steadyStateDdtScheme_Header
