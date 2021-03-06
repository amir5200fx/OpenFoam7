#pragma once
#ifndef _linear_Header
#define _linear_Header

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
	tnbLib::linear

Description
	Central-differencing interpolation scheme class

SourceFiles
	linear.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <volFields.hxx>

#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLinear_EXPORT __declspec(dllexport)
#else
#ifdef FoamLinear_EXPORT_DEFINE
#define FoamLinear_EXPORT __declspec(dllexport)
#else
#define FoamLinear_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class linear Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class linear
		:
		public surfaceInterpolationScheme<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("linear");*/
		static const char* typeName_() { return "linear"; }
		static FoamLinear_EXPORT const ::tnbLib::word typeName;
		static FoamLinear_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		linear(const fvMesh& mesh)
			:
			surfaceInterpolationScheme<Type>(mesh)
		{}

		//- Construct from Istream
		linear(const fvMesh& mesh, Istream&)
			:
			surfaceInterpolationScheme<Type>(mesh)
		{}

		//- Construct from faceFlux and Istream
		linear
		(
			const fvMesh& mesh,
			const surfaceScalarField&,
			Istream&
		)
			:
			surfaceInterpolationScheme<Type>(mesh)
		{}


		// Member Functions

			//- Return the interpolation weighting factors
		tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const
		{
			return this->mesh().surfaceInterpolation::weights();
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const linear&) = delete;
	};


	template<class Type>
	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
		linearInterpolate(const GeometricField<Type, fvPatchField, volMesh>& vf)
	{
		return surfaceInterpolationScheme<Type>::interpolate
		(
			vf,
			vf.mesh().surfaceInterpolation::weights()
		);
	}


	template<class Type>
	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
		linearInterpolate(const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf)
	{
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tinterp =
			linearInterpolate(tvf());
		tvf.clear();
		return tinterp;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linear_Header
