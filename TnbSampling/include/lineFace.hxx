#pragma once
#ifndef _lineFace_Header
#define _lineFace_Header


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
	tnbLib::sampledSets::lineFace

Description
	Face-intersections along a line

Usage
	\table
		Property    | Description                            | Req'd? | Default
		start       | The start point of the line            | yes    |
		end         | The end point of the line              | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        lineFace;
		start       (0.6 0.6 0.5);
		end         (0.6 -0.3 -0.1);
		axis        x;
	}
	\endverbatim

SourceFiles
	lineFace.C

\*---------------------------------------------------------------------------*/

#include <sampledSet.hxx>
#include <DynamicList.hxx>
#include <passiveParticleCloud.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{

		/*---------------------------------------------------------------------------*\
								 Class lineFace Declaration
		\*---------------------------------------------------------------------------*/

		class lineFace
			:
			public sampledSet
		{
			// Private Data

				//- Start point
			const point start_;

			//- End point
			const point end_;


			// Protected Member Functions

				//- Calculate all the sampling points
			FoamSampling_EXPORT void calcSamples
			(
				DynamicList<point>& samplingPts,
				DynamicList<label>& samplingCells,
				DynamicList<label>& samplingFaces,
				DynamicList<label>& samplingSegments,
				DynamicList<scalar>& samplingCurveDist
			) const;

			//- Uses calcSamples to obtain samples and copies them into *this
			FoamSampling_EXPORT void genSamples();


		public:

			//- Runtime type information
			//TypeName("lineFace");
			static const char* typeName_() { return "lineFace"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Static Member Functions

				//- Calculate all the sampling points
			static FoamSampling_EXPORT void calcSamples
			(
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const vector& start,
				const vector& end,
				DynamicList<point>& samplingPts,
				DynamicList<label>& samplingCells,
				DynamicList<label>& samplingFaces,
				DynamicList<label>& samplingSegments,
				DynamicList<scalar>& samplingCurveDist
			);


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT lineFace
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~lineFace();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lineFace_Header
