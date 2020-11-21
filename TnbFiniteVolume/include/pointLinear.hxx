#pragma once
#ifndef _pointLinear_Header
#define _pointLinear_Header

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
	tnbLib::pointLinear

Description
	Face-point interpolation scheme class derived from linear and
	returns linear weighting factors but also applies an explicit correction.

	Uses volPointInterpolation to obtain the field values at the face-points.

SourceFiles
	pointLinear.C

\*---------------------------------------------------------------------------*/

#include <linear.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamPointLinear_EXPORT __declspec(dllexport)
#else
#ifdef FoamPointLinear_EXPORT_DEFINE
#define FoamPointLinear_EXPORT __declspec(dllexport)
#else
#define FoamPointLinear_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class pointLinear Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class pointLinear
		:
		public linear<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("pointLinear");*/
		static const char* typeName_() { return "pointLinear"; }
		static FoamPointLinear_EXPORT const ::tnbLib::word typeName;
		static FoamPointLinear_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		pointLinear(const fvMesh& mesh)
			:
			linear<Type>(mesh)
		{}


		//- Construct from mesh and Istream
		pointLinear
		(
			const fvMesh& mesh,
			Istream&
		)
			:
			linear<Type>(mesh)
		{}


		//- Construct from mesh, faceFlux and Istream
		pointLinear
		(
			const fvMesh& mesh,
			const surfaceScalarField&,
			Istream&
		)
			:
			linear<Type>(mesh)
		{}

		//- Disallow default bitwise copy construction
		pointLinear(const pointLinear&) = delete;


		// Member Functions

			//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return true;
		}

		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const pointLinear&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointLinear_Header
