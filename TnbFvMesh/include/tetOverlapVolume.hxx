#pragma once
#ifndef _tetOverlapVolume_Header
#define _tetOverlapVolume_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::tetOverlapVolume

Description
	Calculates the overlap volume of two cells using tetrahedral decomposition

SourceFiles
	tetOverlapVolume.C

\*---------------------------------------------------------------------------*/

#include <FixedList.hxx>
#include <labelList.hxx>
#include <treeBoundBox.hxx>
#include <tetPointRef.hxx>

namespace tnbLib
{

	class primitiveMesh;
	class polyMesh;

	/*---------------------------------------------------------------------------*\
						  Class tetOverlapVolume Declaration
	\*---------------------------------------------------------------------------*/

	class tetOverlapVolume
	{
		// Private Member Functions

			//- Tet overlap volume
		FoamFvMesh_EXPORT scalar tetTetOverlapVol
		(
			const tetPointRef& tetA,
			const tetPointRef& tetB
		) const;

		//- Return a const treeBoundBox
		FoamFvMesh_EXPORT treeBoundBox pyrBb
		(
			const pointField& points,
			const face& f,
			const point& fc
		) const;


		// Private classes

			//- A fixed list of tets which simulates a dynamic list by incrementing
			//  a counter whenever its append method is called. This is used as an
			//  optimisation for the tetTetOverlapVol method.
		template<unsigned Size>
		class cutTetList
			:
			public FixedList<FixedList<point, 4>, Size>
		{
		private:

			//- The number of stored elements
			label n_;


		public:

			//- Construct null
			cutTetList()
				:
				n_(0)
			{}

			//- Clear the array
			void clear()
			{
				n_ = 0;
			}

			//- Get the current size
			label size() const
			{
				return n_;
			}

			//- Add a new tet to the end of the array
			void append(const FixedList<point, 4>& t)
			{
				this->operator[](n_) = t;
				++n_;
			}
		};


	public:

		//- Runtime type information
		/*ClassName("tetOverlapVolume");*/
		static const char* typeName_() { return "tetOverlapVolume"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Null constructor
		FoamFvMesh_EXPORT tetOverlapVolume();


		// Public members

			//- Return a list of cells in meshA which overlaps with cellBI in
			// meshB
		FoamFvMesh_EXPORT labelList overlappingCells
		(
			const polyMesh& meshA,
			const polyMesh& meshB,
			const label cellBI
		) const;

		//- Return true if olverlap volume is greater than threshold
		FoamFvMesh_EXPORT bool cellCellOverlapMinDecomp
		(
			const primitiveMesh& meshA,
			const label cellAI,
			const primitiveMesh& meshB,
			const label cellBI,
			const treeBoundBox& cellBbB,
			const scalar threshold = 0.0
		) const;

		//- Calculates the overlap volume
		FoamFvMesh_EXPORT scalar cellCellOverlapVolumeMinDecomp
		(
			const primitiveMesh& meshA,
			const label cellAI,

			const primitiveMesh& meshB,
			const label cellBI,
			const treeBoundBox& cellBbB
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tetOverlapVolume_Header
