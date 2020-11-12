#pragma once
#ifndef _boundaryPoints_Header
#define _boundaryPoints_Header

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
	tnbLib::sampledSets::boundaryPoints

Description
	Specified point samples within patches

Usage
	\table
		Property    | Description                            | Req'd? | Default
		patches     | The patches on which to sample         | yes    |
		points      | The points to sample                   | yes    |
		maxDistance | The maximum distance from patch to point | yes  |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        boundaryPoints;
		patches     (inlet1 inlet2);
		points
		(
			(0 -0.05 0.05)
			(0 -0.05 0.15)
			(0 0.05 0.15)
			(0 0.05 0.05)
		);
		maxDistance 0.01;
		axis        x;
	}
	\endverbatim

SourceFiles
	boundaryPoints.C

\*---------------------------------------------------------------------------*/

#include <sampledSet.hxx>
#include <DynamicList.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{

		/*---------------------------------------------------------------------------*\
								Class boundaryPoints Declaration
		\*---------------------------------------------------------------------------*/

		class boundaryPoints
			:
			public sampledSet
		{
			// Private Data

				//- Sampling points
			const List<point> points_;

			//- Patches to sample
			const labelHashSet patches_;

			//- Maximum distance to to search for a nearby patch
			const scalar maxDistance_;


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
			//TypeName("boundaryPoints");
			static const char* typeName_() { return "boundaryPoints"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT boundaryPoints
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~boundaryPoints();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundaryPoints_Header
