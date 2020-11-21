#pragma once
#ifndef _boundaryRandom_Header
#define _boundaryRandom_Header

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
	tnbLib::sampledSets::boundaryRandom

Description
	Random samples within patches

Usage
	\table
		Property    | Description                            | Req'd? | Default
		patches     | The patches on which to sample         | yes    |
		nPoints     | The number of points                   | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        boundaryRandom;
		patches     (inlet1 inlet2);
		nPoints     1000;
		axis        x;
	}
	\endverbatim

SourceFiles
	boundaryRandom.C

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
								Class boundaryRandom Declaration
		\*---------------------------------------------------------------------------*/

		class boundaryRandom
			:
			public sampledSet
		{
			// Private Data

				//- Patches to sample
			const labelHashSet patches_;

			//- Number of points
			const label nPoints_;


			// Private Member Functions

				//- Sample all points
			FoamSampling_EXPORT void calcSamples
			(
				DynamicList<point>& samplingPts,
				DynamicList<label>& samplingCells,
				DynamicList<label>& samplingFaces,
				DynamicList<label>& samplingSegments,
				DynamicList<scalar>& samplingCurveDist
			) const;

			//- Use calcSamples to obtain samples and copy them into *this
			FoamSampling_EXPORT void genSamples();


		public:

			//- Runtime type information
			//TypeName("boundaryRandom");
			static const char* typeName_() { return "boundaryRandom"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT boundaryRandom
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~boundaryRandom();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundaryRandom_Header
