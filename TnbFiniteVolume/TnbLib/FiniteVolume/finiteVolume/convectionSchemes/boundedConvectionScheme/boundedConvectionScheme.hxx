#pragma once
#ifndef _boundedConvectionScheme_Header
#define _boundedConvectionScheme_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fv::boundedConvectionScheme

Description
	Bounded form of the selected convection scheme.

	Boundedness is achieved by subtracting div(phi)*vf or Sp(div(phi), vf)
	which is non-conservative if div(phi) != 0 but conservative otherwise.

	Can be used for convection of bounded scalar properties in steady-state
	solvers to improve stability if insufficient convergence of the pressure
	equation causes temporary divergence of the flux field.

SourceFiles
	boundedConvectionScheme.C

\*---------------------------------------------------------------------------*/

#include <convectionScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamBoundedConvectionScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamBoundedConvectionScheme_EXPORT_DEFINE
#define FoamBoundedConvectionScheme_EXPORT __declspec(dllexport)
#else
#define FoamBoundedConvectionScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class boundedConvectionScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class boundedConvectionScheme
			:
			public fv::convectionScheme<Type>
		{
			// Private Data

			tmp<fv::convectionScheme<Type>> scheme_;


		public:

			//- Runtime type information
			/*TypeName("bounded");*/
			static const char* typeName_() { return "bounded"; }
			static FoamBoundedConvectionScheme_EXPORT const ::tnbLib::word typeName;
			static FoamBoundedConvectionScheme_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from flux and Istream
			boundedConvectionScheme
			(
				const fvMesh& mesh,
				const surfaceScalarField& faceFlux,
				Istream& is
			)
				:
				convectionScheme<Type>(mesh, faceFlux),
				scheme_
				(
					fv::convectionScheme<Type>::New(mesh, faceFlux, is)
				)
			{}

			//- Disallow default bitwise copy construction
			boundedConvectionScheme(const boundedConvectionScheme&) = delete;


			// Member Functions

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> flux
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;

			tmp<fvMatrix<Type>> fvmDiv
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;

			tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDiv
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const boundedConvectionScheme&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <boundedConvectionSchemeI.hxx>

//#ifdef NoRepository
//#include <boundedConvectionScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundedConvectionScheme_Header
