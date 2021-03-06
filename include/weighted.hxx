#pragma once
#ifndef _weighted_Header
#define _weighted_Header

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
	tnbLib::weighted

Description
	Interpolation scheme class using weights looked-up from the objectRegistry.

SourceFiles
	weighted.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <volFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamWeighted_EXPORT __declspec(dllexport)
#else
#ifdef FoamWeighted_EXPORT_DEFINE
#define FoamWeighted_EXPORT __declspec(dllexport)
#else
#define FoamWeighted_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class weighted Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class weighted
		:
		public surfaceInterpolationScheme<Type>
	{
		// Private member data

		const surfaceScalarField& weights_;


	public:

		//- Runtime type information
		/*TypeName("weighted");*/
		static const char* typeName_() { return "weighted"; }
		static FoamWeighted_EXPORT const ::tnbLib::word typeName;
		static FoamWeighted_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from weights
		weighted(const surfaceScalarField& weights)
			:
			surfaceInterpolationScheme<Type>(weights.mesh()),
			weights_(weights)
		{}

		//- Construct from Istream
		weighted(const fvMesh& mesh, Istream& is)
			:
			surfaceInterpolationScheme<Type>(mesh),
			weights_
			(
				this->mesh().objectRegistry::template
				lookupObject<const surfaceScalarField>
				(
					word(is)
					)
			)
		{}

		//- Construct from faceFlux and Istream
		weighted
		(
			const fvMesh& mesh,
			const surfaceScalarField&,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			weights_
			(
				this->mesh().objectRegistry::template
				lookupObject<const surfaceScalarField>
				(
					word(is)
					)
			)
		{}


		// Member Functions

			//- Return the interpolation weighting factors
		tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const
		{
			return weights_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const weighted&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_weighted_Header
