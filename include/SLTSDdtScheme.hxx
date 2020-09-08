#pragma once
#ifndef _SLTSDdtScheme_Header
#define _SLTSDdtScheme_Header

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
	tnbLib::fv::SLTSDdtScheme

Description
	Stabilised local time-step first-order Euler implicit/explicit ddt.
	The time-step is adjusted locally so that an advective equations remains
	diagonally dominant.

	This scheme should only be used for steady-state computations
	using transient codes where local time-stepping is preferably to
	under-relaxation for transport consistency reasons.

See also
	tnbLib::fv::CoEulerDdtScheme

SourceFiles
	SLTSDdtScheme.C

\*---------------------------------------------------------------------------*/

#include <ddtScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class SLTSDdtScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class SLTSDdtScheme
			:
			public fv::ddtScheme<Type>
		{
			// Private Data

				//- Name of the flux field used to calculate the local time-step
			word phiName_;

			//- Name of the density field used to obtain the volumetric flux
			//  from the mass flux if required
			word rhoName_;

			//- Under-relaxation factor
			scalar alpha_;


			// Private Member Functions

				//- Calculate a relaxed diagonal from the given flux field
			void relaxedDiag(scalarField& rD, const surfaceScalarField& phi) const;

			//- Return the reciprocal of the stabilised local time-step
			tmp<volScalarField> SLrDeltaT() const;


		public:

			//- Runtime type information
			TypeName("SLTS");


			// Constructors

				//- Construct from mesh and Istream
			SLTSDdtScheme(const fvMesh& mesh, Istream& is)
				:
				ddtScheme<Type>(mesh, is),
				phiName_(is),
				rhoName_(is),
				alpha_(readScalar(is))
			{}

			//- Disallow default bitwise copy construction
			SLTSDdtScheme(const SLTSDdtScheme&) = delete;


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
			void operator=(const SLTSDdtScheme&) = delete;
		};


		template<>
		tmp<surfaceScalarField> SLTSDdtScheme<scalar>::fvcDdtUfCorr
		(
			const GeometricField<scalar, fvPatchField, volMesh>& U,
			const GeometricField<scalar, fvsPatchField, surfaceMesh>& Uf
		);

		template<>
		tmp<surfaceScalarField> SLTSDdtScheme<scalar>::fvcDdtPhiCorr
		(
			const volScalarField& U,
			const surfaceScalarField& phi
		);

		template<>
		tmp<surfaceScalarField> SLTSDdtScheme<scalar>::fvcDdtUfCorr
		(
			const volScalarField& rho,
			const volScalarField& U,
			const surfaceScalarField& Uf
		);

		template<>
		tmp<surfaceScalarField> SLTSDdtScheme<scalar>::fvcDdtPhiCorr
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

#include <SLTSDdtSchemeI.hxx>

//#ifdef NoRepository
//#include <SLTSDdtScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SLTSDdtScheme_Header
