#pragma once
#ifndef _directMethod_Header
#define _directMethod_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::directMethod

Description
	Direct (one-to-one cell correspondence) mesh-to-mesh interpolation class

	Volume conservative.

SourceFiles
	directMethod.C

\*---------------------------------------------------------------------------*/

#include <meshToMeshMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class directMethod Declaration
	\*---------------------------------------------------------------------------*/

	class directMethod
		:
		public meshToMeshMethod
	{
	protected:

		// Protected Member Functions

			//- Return the true if cells intersect
		FoamSampling_EXPORT virtual bool intersect
		(
			const label srcCelli,
			const label tgtCelli
		) const;

		//- Find indices of overlapping cells in src and tgt meshes - returns
		//  true if found a matching pair
		FoamSampling_EXPORT virtual bool findInitialSeeds
		(
			const labelList& srcCellIDs,
			const boolList& mapFlag,
			const label startSeedI,
			label& srcSeedI,
			label& tgtSeedI
		) const;

		//- Calculate the mesh-to-mesh addressing and weights
		FoamSampling_EXPORT virtual void calculateAddressing
		(
			labelListList& srcToTgtCellAddr,
			scalarListList& srcToTgtCellWght,
			labelListList& tgtToSrcCellAddr,
			scalarListList& tgtToSrcCellWght,
			const label srcSeedI,
			const label tgtSeedI,
			const labelList& srcCellIDs,
			boolList& mapFlag,
			label& startSeedI
		);

		//- Append to list of src mesh seed indices
		FoamSampling_EXPORT virtual void appendToDirectSeeds
		(
			boolList& mapFlag,
			labelList& srcTgtSeed,
			DynamicList<label>& srcSeeds,
			label& srcSeedI,
			label& tgtSeedI
		) const;


	public:

		//- Run-time type information
		//TypeName("direct");
		static const char* typeName_() { return "direct"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from source and target meshes
		FoamSampling_EXPORT directMethod(const polyMesh& src, const polyMesh& tgt);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT directMethod(const directMethod&) = delete;


		//- Destructor
		FoamSampling_EXPORT virtual ~directMethod();


		// Member Functions

			// Evaluate

				//- Calculate addressing and weights
		FoamSampling_EXPORT virtual void calculate
		(
			labelListList& srcToTgtAddr,
			scalarListList& srcToTgtWght,
			labelListList& tgtToTgtAddr,
			scalarListList& tgtToTgtWght
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const directMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_directMethod_Header
