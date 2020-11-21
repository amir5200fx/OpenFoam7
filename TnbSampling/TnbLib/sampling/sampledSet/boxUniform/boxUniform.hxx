#pragma once
#ifndef _boxUniform_Header
#define _boxUniform_Header

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
	tnbLib::sampledSets::boxUniform

Description
	Uniform 3D-grid of samples

Usage
	\table
		Property    | Description                            | Req'd? | Default
		box         | The box which contains the samples     | yes    |
		nPoints     | The number of points in each direction | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        boxUniform;
		box         (0.95 0 0.25) (1.2 0.25 0.5);
		nPoints     (2 4 6);
		axis        x;
	}
	\endverbatim

SourceFiles
	boxUniform.C

\*---------------------------------------------------------------------------*/


#include <sampledSet.hxx>
#include <DynamicList.hxx>
#include <labelVector.hxx>
#include <boundBox.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class passiveParticle;
	template<class Type> class particle;

	namespace sampledSets
	{

		/*---------------------------------------------------------------------------*\
								   Class boxUniform Declaration
		\*---------------------------------------------------------------------------*/

		class boxUniform
			:
			public sampledSet
		{
			// Private Data

				//- Box
			const boundBox box_;

			//- The number of points across each direction of the box
			const labelVector nPoints_;


			// Private Member Functions

				//- Samples all points in sampleCoords.
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
			//TypeName("boxUniform");
			static const char* typeName_() { return "boxUniform"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT boxUniform
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~boxUniform();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSets
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boxUniform_Header
