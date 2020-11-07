#pragma once
#ifndef _EulerD2dt2Scheme_Header
#define _EulerD2dt2Scheme_Header

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
	tnbLib::fv::EulerD2dt2Scheme

Description
	First-order Euler implicit d2dt2 using the current and two previous
	time-step values.

SourceFiles
	EulerD2dt2Scheme.C

\*---------------------------------------------------------------------------*/

#include <d2dt2Scheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamEulerD2dt2Scheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamEulerD2dt2Scheme_EXPORT_DEFINE
#define FoamEulerD2dt2Scheme_EXPORT __declspec(dllexport)
#else
#define FoamEulerD2dt2Scheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class EulerD2dt2Scheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class EulerD2dt2Scheme
			:
			public fv::d2dt2Scheme<Type>
		{
		public:

			//- Runtime type information
			/*TypeName("Euler");*/
			static const char* typeName_() { return "Euler"; }
			static FoamEulerD2dt2Scheme_EXPORT const ::tnbLib::word typeName;
			static FoamEulerD2dt2Scheme_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh
			EulerD2dt2Scheme(const fvMesh& mesh)
				:
				d2dt2Scheme<Type>(mesh)
			{}

			//- Construct from mesh and Istream
			EulerD2dt2Scheme(const fvMesh& mesh, Istream& is)
				:
				d2dt2Scheme<Type>(mesh, is)
			{}

			//- Disallow default bitwise copy construction
			EulerD2dt2Scheme(const EulerD2dt2Scheme&) = delete;


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return fv::d2dt2Scheme<Type>::mesh();
			}

			tmp<GeometricField<Type, fvPatchField, volMesh>> fvcD2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh>> fvcD2dt2
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type>> fvmD2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type>> fvmD2dt2
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type>> fvmD2dt2
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const EulerD2dt2Scheme&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <EulerD2dt2SchemeI.hxx>

//#ifdef NoRepository
//#include <EulerD2dt2Scheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_EulerD2dt2Scheme_Header
