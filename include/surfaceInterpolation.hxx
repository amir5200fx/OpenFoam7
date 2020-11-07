#pragma once
#ifndef _surfaceInterpolation_Header
#define _surfaceInterpolation_Header

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
	tnbLib::surfaceInterpolation

Description
	Cell to surface interpolation scheme. Included in fvMesh.

SourceFiles
	surfaceInterpolation.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <scalar.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;  // added by amir

	/*---------------------------------------------------------------------------*\
						 Class surfaceInterpolation Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceInterpolation
	{
		// Private Data

			// Reference to fvMesh
		const fvMesh& mesh_;

		// Demand-driven data

			//- Linear difference weighting factors
		mutable surfaceScalarField* weights_;

		//- Cell-centre difference coefficients
		mutable surfaceScalarField* deltaCoeffs_;

		//- Non-orthogonal cell-centre difference coefficients
		mutable surfaceScalarField* nonOrthDeltaCoeffs_;

		//- Non-orthogonality correction vectors
		mutable surfaceVectorField* nonOrthCorrectionVectors_;


		// Private Member Functions

			//- Construct central-differencing weighting factors
		FoamFiniteVolume_EXPORT void makeWeights() const;

		//- Construct face-gradient difference factors
		FoamFiniteVolume_EXPORT void makeDeltaCoeffs() const;

		//- Construct face-gradient difference factors
		FoamFiniteVolume_EXPORT void makeNonOrthDeltaCoeffs() const;

		//- Construct non-orthogonality correction vectors
		FoamFiniteVolume_EXPORT void makeNonOrthCorrectionVectors() const;


	protected:

		// Protected Member Functions

		// Storage management

		//- Clear all geometry and addressing
		FoamFiniteVolume_EXPORT void clearOut();


	public:

		// Declare name of the class and its debug switch
		/*ClassName("surfaceInterpolation");*/
		static const char* typeName_() { return "surfaceInterpolation"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;


		// Constructors

			//- Construct given an fvMesh
		FoamFiniteVolume_EXPORT explicit surfaceInterpolation(const fvMesh&);


		//- Destructor
		FoamFiniteVolume_EXPORT ~surfaceInterpolation();


		// Member Functions

		//- Return reference to linear difference weighting factors
		FoamFiniteVolume_EXPORT const surfaceScalarField& weights() const;

		//- Return reference to cell-centre difference coefficients
		FoamFiniteVolume_EXPORT const surfaceScalarField& deltaCoeffs() const;

		//- Return reference to non-orthogonal cell-centre difference
		//  coefficients
		FoamFiniteVolume_EXPORT const surfaceScalarField& nonOrthDeltaCoeffs() const;

		//- Return reference to non-orthogonality correction vectors
		FoamFiniteVolume_EXPORT const surfaceVectorField& nonOrthCorrectionVectors() const;

		//- Do what is necessary if the mesh has moved
		FoamFiniteVolume_EXPORT bool movePoints();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolation_Header
