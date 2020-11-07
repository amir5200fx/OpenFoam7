#pragma once
#ifndef _mappedWallPolyPatch_Header
#define _mappedWallPolyPatch_Header

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
	tnbLib::mappedWallPolyPatch

Description
	Determines a mapping between patch face centres and mesh cell or face
	centres and processors they're on.

Note
	Storage is not optimal. It stores all face centres and cells on all
	processors to keep the addressing calculation simple.

SourceFiles
	mappedWallPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <wallPolyPatch.hxx>
#include <mappedPatchBase.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						  Class mappedWallPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class mappedWallPolyPatch
		:
		public wallPolyPatch,
		public mappedPatchBase
	{

	protected:

		//- Initialise the calculation of the patch geometry
		FoamFvMesh_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		FoamFvMesh_EXPORT virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamFvMesh_EXPORT virtual void initMovePoints(PstreamBuffers&, const pointField&);

		//- Correct patches after moving points
		FoamFvMesh_EXPORT virtual void movePoints(PstreamBuffers&, const pointField&);

		//- Initialise the update of the patch topology
		FoamFvMesh_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamFvMesh_EXPORT virtual void updateMesh(PstreamBuffers&);


	public:

		//- Runtime type information
		/*TypeName("mappedWall");*/
		static const char* typeName_() { return "mappedWall"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct from components
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const word& sampleRegion,
			const mappedPatchBase::sampleMode mode,
			const word& samplePatch,
			const vectorField& offset,
			const polyBoundaryMesh& bm
		);

		//- Construct from components. Uniform offset.
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const word& sampleRegion,
			const mappedPatchBase::sampleMode mode,
			const word& samplePatch,
			const vector& offset,
			const polyBoundaryMesh& bm
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct as copy, resetting the boundary mesh
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const mappedWallPolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const mappedWallPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct given the original patch and a map
		FoamFvMesh_EXPORT mappedWallPolyPatch
		(
			const mappedWallPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new mappedWallPolyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new mappedWallPolyPatch
					(
						*this,
						bm,
						index,
						newSize,
						newStart
					)
					);
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new mappedWallPolyPatch
					(
						*this,
						bm,
						index,
						mapAddressing,
						newStart
					)
					);
		}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~mappedWallPolyPatch();


		// Member Functions

			//- Write the polyPatch data as a dictionary
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mappedWallPolyPatch_Header
