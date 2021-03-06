#pragma once
#ifndef _multivariateUpwind_Header
#define _multivariateUpwind_Header

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
	tnbLib::multivariateUpwind

Description
	Upwind-difference form of the multivariate surfaceInterpolationScheme.

SourceFiles
	multivariateUpwindmake.C

\*---------------------------------------------------------------------------*/

#include <multivariateSurfaceInterpolationScheme.hxx>
#include <surfaceFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamMultivariateUpwind_EXPORT __declspec(dllexport)
#else
#ifdef FoamMultivariateUpwind_EXPORT_DEFINE
#define FoamMultivariateUpwind_EXPORT __declspec(dllexport)
#else
#define FoamMultivariateUpwind_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class multivariateUpwind Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class multivariateUpwind
		:
		public multivariateSurfaceInterpolationScheme<Type>
	{
		// Private Data

		const surfaceScalarField& faceFlux_;


	public:

		//- Runtime type information
		/*TypeName("upwind");*/
		static const char* typeName_() { return "upwind"; }
		static FoamMultivariateUpwind_EXPORT const ::tnbLib::word typeName;
		static FoamMultivariateUpwind_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct for field, faceFlux and Istream
		multivariateUpwind
		(
			const fvMesh& mesh,
			const typename multivariateSurfaceInterpolationScheme<Type>::
			fieldTable& fields,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
			:
			multivariateSurfaceInterpolationScheme<Type>
			(
				mesh,
				fields,
				faceFlux,
				schemeData
				),
			faceFlux_(faceFlux)
		{}

		//- Disallow default bitwise copy construction
		multivariateUpwind(const multivariateUpwind&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const multivariateUpwind&) = delete;

		//- surfaceInterpolationScheme sub-class returned by operator(field)
		//  which is used as the interpolation scheme for the field
		class fieldScheme
			:
			public multivariateSurfaceInterpolationScheme<Type>::fieldScheme
		{
			// Private Data

			const surfaceScalarField& faceFlux_;

		public:

			// Constructors

			fieldScheme
			(
				const GeometricField<Type, fvPatchField, volMesh>& field,
				const surfaceScalarField& faceFlux
			)
				:
				multivariateSurfaceInterpolationScheme<Type>::
				fieldScheme(field),
				faceFlux_(faceFlux)
			{}


			// Member Functions

				//- Return the interpolation weighting factors
			tmp<surfaceScalarField> weights
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const
			{
				return pos0(faceFlux_);
			}
		};

		tmp<surfaceInterpolationScheme<Type>> operator()
			(
				const GeometricField<Type, fvPatchField, volMesh>& field
				) const
		{
			return tmp<surfaceInterpolationScheme<Type>>
				(
					new fieldScheme(field, faceFlux_)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_multivariateUpwind_Header
