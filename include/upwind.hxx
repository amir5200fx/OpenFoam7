#pragma once
#ifndef _upwind_Header
#define _upwind_Header

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
	tnbLib::upwind

Description
	Upwind differencing scheme class.

SourceFiles
	upwind.C

\*---------------------------------------------------------------------------*/

#include <limitedSurfaceInterpolationScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamUpwind_EXPORT __declspec(dllexport)
#else
#ifdef FoamUpwind_EXPORT_DEFINE
#define FoamUpwind_EXPORT __declspec(dllexport)
#else
#define FoamUpwind_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class upwind Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class upwind
		:
		public limitedSurfaceInterpolationScheme<Type>
	{

	public:

		//- Runtime type information
		//TypeName("upwind");
		static const char* typeName_() { return "upwind"; }
		static FoamUpwind_EXPORT const ::tnbLib::word typeName;
		static FoamUpwind_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from faceFlux
		upwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			limitedSurfaceInterpolationScheme<Type>(mesh, faceFlux)
		{}

		//- Construct from Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		upwind
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			limitedSurfaceInterpolationScheme<Type>(mesh, is)
		{}

		//- Construct from faceFlux and Istream
		upwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream&
		)
			:
			limitedSurfaceInterpolationScheme<Type>(mesh, faceFlux)
		{}


		// Member Functions

			//- Return the interpolation limiter
		virtual tmp<surfaceScalarField> limiter
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const
		{
			return surfaceScalarField::New
			(
				"upwindLimiter",
				this->mesh(),
				dimensionedScalar(dimless, 0)
			);
		}

		//- Return the interpolation weighting factors
		tmp<surfaceScalarField> weights() const
		{
			return pos0(this->faceFlux_);
		}

		//- Return the interpolation weighting factors
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const
		{
			return weights();
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const upwind&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_upwind_Header
