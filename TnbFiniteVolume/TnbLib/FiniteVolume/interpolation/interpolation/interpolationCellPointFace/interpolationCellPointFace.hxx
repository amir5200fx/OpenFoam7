#pragma once
#ifndef _interpolationCellPointFace_Header
#define _interpolationCellPointFace_Header

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
	tnbLib::interpolationCellPointFace

Description
	tnbLib::interpolationCellPointFace

\*---------------------------------------------------------------------------*/

#include <interpolation.hxx>

#include <fvsPatchField.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamInterpolationCellPointFace_EXPORT __declspec(dllexport)
#else
#ifdef FoamInterpolationCellPointFace_EXPORT_DEFINE
#define FoamInterpolationCellPointFace_EXPORT __declspec(dllexport)
#else
#define FoamInterpolationCellPointFace_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class interpolationCellPointFace Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCellPointFace
		:
		public interpolation<Type>
	{
		// Private Data

			//- Interpolated volfield
		const GeometricField<Type, pointPatchField, pointMesh> psip_;

		//- Linearly interpolated volfield
		const GeometricField<Type, fvsPatchField, surfaceMesh> psis_;

		bool findTet
		(
			const vector& position,
			const label nFace,
			vector tetPoints[],
			label tetLabelCandidate[],
			label tetPointLabels[],
			scalar phi[],
			scalar phiCandidate[],
			label& closestFace,
			scalar& minDistance
		) const;

		bool findTriangle
		(
			const vector& position,
			const label nFace,
			label tetPointLabels[],
			scalar phi[]
		) const;


	public:

		//- Runtime type information
		/*TypeName("cellPointFace");*/
		static const char* typeName_() { return "cellPointFace"; }
		static FoamInterpolationCellPointFace_EXPORT const ::tnbLib::word typeName;
		static FoamInterpolationCellPointFace_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		interpolationCellPointFace
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Interpolate field to the given point in the given cell
		Type interpolate
		(
			const vector& position,
			const label celli,
			const label facei = -1
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationCellPointFaceI.hxx>

//#ifdef NoRepository
//#include <interpolationCellPointFace.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCellPointFace_Header
