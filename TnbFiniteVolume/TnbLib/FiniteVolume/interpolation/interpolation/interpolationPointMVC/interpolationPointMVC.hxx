#pragma once
#ifndef _interpolationPointMVC_Header
#define _interpolationPointMVC_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::interpolationPointMVC

Description
	Given cell centre values interpolates to vertices and uses these to
	do a Mean Value Coordinates interpolation.

\*---------------------------------------------------------------------------*/

#include <interpolation.hxx>
#include <pointMVCWeight.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamInterpolationPointMVC_EXPORT __declspec(dllexport)
#else
#ifdef FoamInterpolationPointMVC_EXPORT_DEFINE
#define FoamInterpolationPointMVC_EXPORT __declspec(dllexport)
#else
#define FoamInterpolationPointMVC_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class interpolationPointMVC Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationPointMVC
		:
		public interpolation<Type>
	{
	protected:

		// Protected data

			//- Interpolated volfield
		const GeometricField<Type, pointPatchField, pointMesh> psip_;


	public:

		//- Runtime type information
		/*TypeName("pointMVC");*/
		static const char* typeName_() { return "pointMVC"; }
		static FoamInterpolationPointMVC_EXPORT const ::tnbLib::word typeName;
		static FoamInterpolationPointMVC_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		interpolationPointMVC
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Inherit interpolate from interpolation
		using interpolation<Type>::interpolate;

		//- Interpolate field for the given cellPointWeight
		inline Type interpolate(const pointMVCWeight& cpw) const;

		//- Interpolate field to the given point in the given cell
		inline Type interpolate
		(
			const vector& position,
			const label celli,
			const label facei = -1
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationPointMVCI.hxx>
#include <interpolationPointMVC_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <interpolationPointMVC.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationPointMVC_Header
