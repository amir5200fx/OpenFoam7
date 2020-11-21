#pragma once
#ifndef _arcUniform_Header
#define _arcUniform_Header

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
	tnbLib::sampledSets::arcUniform

Description
	Uniform samples along an arc

Usage
	\table
		Property    | Description                            | Req'd? | Default
		centre      | Centre of the circle                   | yes    |
		normal      | Direction normal to the plane of the circle  | yes |
		radial      | Vector from the centre to a point on the arc | yes |
		startAngle  | The angle of the start of the arc in radians | yes |
		endAngle    | The angle of the end of the arc in radians | yes |
		nPoints     | The number of points                   | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        arcUniform;
		centre      (0.95 0 0.25);
		normal      (1 0 0);
		radial      (0 0 0.25);
		startAngle  -1.57079633;
		endAngle    0.52359878;
		nPoints     200;
		axis        x;
	}
	\endverbatim

SourceFiles
	arcUniform.C

\*---------------------------------------------------------------------------*/

#include <sampledSet.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{

		/*---------------------------------------------------------------------------*\
								  Class arcUniform Declaration
		\*---------------------------------------------------------------------------*/

		class arcUniform
			:
			public sampledSet
		{
			// Private Data

				// Arc definition

					//- Centre of the circle of which the arc is a part
			const point centre_;

			//- Normal direction to the circle of which the arc is a part
			const vector normal_;

			//- Radial vector from the centre to the point on the arc from
			//  which the angles are measured
			const vector radial_;

			//- Start angle
			const scalar startAngle_;

			//- End angle
			const scalar endAngle_;

			//- Number of points spaced along the arc
			const label nPoints_;


			// Private Member Functions

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
			//TypeName("arcUniform");
			static const char* typeName_() { return "arcUniform"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT arcUniform
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			// Destructor
			FoamSampling_EXPORT virtual ~arcUniform();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_arcUniform_Header
