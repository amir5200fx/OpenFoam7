#pragma once
#ifndef _downwind_Header
#define _downwind_Header

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
	tnbLib::downwind

Description
	Downwind differencing scheme class.

SourceFiles
	downwind.C

\*---------------------------------------------------------------------------*/


#include <surfaceInterpolationScheme.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamDownwind_EXPORT __declspec(dllexport)
#else
#ifdef FoamDownwind_EXPORT_DEFINE
#define FoamDownwind_EXPORT __declspec(dllexport)
#else
#define FoamDownwind_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class downwind Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class downwind
		:
		public surfaceInterpolationScheme<Type>
	{
		// Private Data

		const surfaceScalarField& faceFlux_;


	public:

		//- Runtime type information
		/*TypeName("downwind");*/
		static const char* typeName_() { return "downwind"; }
		static FoamDownwind_EXPORT const ::tnbLib::word typeName;
		static FoamDownwind_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from faceFlux
		downwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_(faceFlux)
		{}

		//- Construct from Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		downwind
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_
			(
				mesh.lookupObject<surfaceScalarField>
				(
					word(is)
					)
			)
		{}

		//- Construct from faceFlux and Istream
		downwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream&
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_(faceFlux)
		{}


		// Member Functions

			//- Return the interpolation weighting factors
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const
		{
			return neg(faceFlux_);
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const downwind&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_downwind_Header
