#pragma once
#ifndef _circleRandom_Header
#define _circleRandom_Header

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
	tnbLib::sampledSets::circleRandom

Description
	Random samples within a circle

Usage
	\table
		Property    | Description                            | Req'd? | Default
		centre      | Centre of the circle                   | yes    |
		normal      | Direction normal to the plane of the circle | yes |
		radius      | Radius of the circle                   | yes    |
		nPoints     | The number of points                   | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        circleRandom;
		centre      (0.95 0 0.25);
		normal      (1 0 0);
		radius      0.25;
		nPoints     200;
		axis        x;
	}
	\endverbatim

SourceFiles
	circleRandom.C

\*---------------------------------------------------------------------------*/

#include <sampledSet.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{

		/*---------------------------------------------------------------------------*\
								  Class circleRandom Declaration
		\*---------------------------------------------------------------------------*/

		class circleRandom
			:
			public sampledSet
		{
			// Private Data

				//- Centre point
			const point centre_;

			//- Direction normal to the circle
			const vector normal_;

			//- Radius
			const scalar radius_;

			//- Number of points
			const label nPoints_;


			// Private Member Functions

				//- Samples all points in sampleCoords
			FoamSampling_EXPORT void calcSamples
			(
				DynamicList<point>& samplingPts,
				DynamicList<label>& samplingCells,
				DynamicList<label>& samplingFaces,
				DynamicList<label>& samplingSegments,
				DynamicList<scalar>& samplingCurveDist
			) const;

			//- Uses calcSamples to obtain samples. Copies them into *this.
			FoamSampling_EXPORT void genSamples();


		public:

			//- Runtime type information
			//TypeName("circleRandom");
			static const char* typeName_() { return "circleRandom"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT circleRandom
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			// Destructor

			FoamSampling_EXPORT virtual ~circleRandom();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_circleRandom_Header
