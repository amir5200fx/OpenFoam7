#pragma once
#ifndef _midPoint_Header
#define _midPoint_Header

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
	tnbLib::midPoint

Description
	Mid-point interpolation (weighting factors = 0.5) scheme class.

SourceFiles
	midPoint.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <volFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamMidPoint_EXPORT __declspec(dllexport)
#else
#ifdef FoamMidPoint_EXPORT_DEFINE
#define FoamMidPoint_EXPORT __declspec(dllexport)
#else
#define FoamMidPoint_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class midPoint Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class midPoint
		:
		public surfaceInterpolationScheme<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("midPoint");*/
		static const char* typeName_() { return "midPoint"; }
		static FoamMidPoint_EXPORT const ::tnbLib::word typeName;
		static FoamMidPoint_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		midPoint(const fvMesh& mesh)
			:
			surfaceInterpolationScheme<Type>(mesh)
		{}

		//- Construct from Istream
		midPoint(const fvMesh& mesh, Istream&)
			:
			surfaceInterpolationScheme<Type>(mesh)
		{}

		//- Construct from faceFlux and Istream
		midPoint
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
			tmp<surfaceScalarField> taw
			(
				surfaceScalarField::New
				(
					"midPointWeights",
					this->mesh(),
					dimensionedScalar(dimless, 0.5)
				)
			);

			surfaceScalarField::Boundary& awBf =
				taw.ref().boundaryFieldRef();

			forAll(awBf, patchi)
			{
				if (!awBf[patchi].coupled())
				{
					awBf[patchi] = 1.0;
				}
			}

			return taw;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const midPoint&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_midPoint_Header
