#pragma once
#ifndef _limitWith_Header
#define _limitWith_Header

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
	tnbLib::limitWith

Description
	limitWith differencing scheme limits the specified scheme with the
	specified limiter.

SourceFiles
	limitWith.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <limitedSurfaceInterpolationScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLimitWith_EXPORT __declspec(dllexport)
#else
#ifdef FoamLimitWith_EXPORT_DEFINE
#define FoamLimitWith_EXPORT __declspec(dllexport)
#else
#define FoamLimitWith_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class limitWith Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class limitWith
		:
		public surfaceInterpolationScheme<Type>
	{
		// Private Member Functions

			//- Interpolation scheme
		tmp<surfaceInterpolationScheme<Type>> tInterp_;

		//- Limiter
		tmp<limitedSurfaceInterpolationScheme<Type>> tLimiter_;


	public:

		//- Runtime type information
		/*TypeName("limitWith");*/
		static const char* typeName_() { return "limitWith"; }
		static FoamLimitWith_EXPORT const ::tnbLib::word typeName;
		static FoamLimitWith_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and Istream.
			//  The name of the flux field is read from the Istream and looked-up
			//  from the mesh objectRegistry
		limitWith
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			tInterp_
			(
				surfaceInterpolationScheme<Type>::New(mesh, is)
			),
			tLimiter_
			(
				limitedSurfaceInterpolationScheme<Type>::New(mesh, is)
			)
		{}

		//- Construct from mesh, faceFlux and Istream
		limitWith
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			tInterp_
			(
				surfaceInterpolationScheme<Type>::New(mesh, faceFlux, is)
			),
			tLimiter_
			(
				limitedSurfaceInterpolationScheme<Type>::New(mesh, faceFlux, is)
			)
		{}

		//- Disallow default bitwise copy construction
		limitWith(const limitWith&) = delete;


		// Member Functions

			//- Return the interpolation weighting factors
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		) const
		{
			return tLimiter_().weights
			(
				vf,
				tInterp_().weights(vf),
				tLimiter_().limiter(vf)
			);
		}

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return tInterp_().corrected();
		}

		//- Return the explicit correction to the face-interpolate
		//  for the given field
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction(const GeometricField<Type, fvPatchField, volMesh>& vf) const
		{
			return tLimiter_().limiter(vf)*tInterp_().correction(vf);
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const limitWith&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_limitWith_Header
