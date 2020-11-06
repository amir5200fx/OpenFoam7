#pragma once
#ifndef _regionCoupledWallPolyPatch_Header
#define _regionCoupledWallPolyPatch_Header

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
	tnbLib::regionCoupledWallPolyPatch

Description
	regionCoupledWall

SourceFiles
	regionCoupledWallPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <wallPolyPatch.hxx>
#include <regionCoupledBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						  Class regionCoupledWallPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledWallPolyPatch
		:
		public wallPolyPatch,
		public regionCoupledBase
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
		/*TypeName("regionCoupledWall");*/
		static const char* typeName_() { return "regionCoupledWall"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT regionCoupledWallPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);


		//- Construct from dictionary
		FoamFvMesh_EXPORT regionCoupledWallPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct as copy, resetting the boundary mesh
		FoamFvMesh_EXPORT regionCoupledWallPolyPatch
		(
			const regionCoupledWallPolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamFvMesh_EXPORT regionCoupledWallPolyPatch
		(
			const regionCoupledWallPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct given the original patch and a map
		FoamFvMesh_EXPORT regionCoupledWallPolyPatch
		(
			const regionCoupledWallPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<wallPolyPatch::polyPatch> clone
		(
			const polyBoundaryMesh& bm
		) const
		{
			return autoPtr<wallPolyPatch::polyPatch>
				(
					new regionCoupledWallPolyPatch(*this, bm)
					);
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<wallPolyPatch::polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<wallPolyPatch::polyPatch>
				(
					new regionCoupledWallPolyPatch
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
					new regionCoupledWallPolyPatch
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
		FoamFvMesh_EXPORT virtual ~regionCoupledWallPolyPatch();


		// Member Functions

			//- Return the type
		virtual const word& regionCoupleType() const
		{
			return type();
		}

		//- Write the polyPatch data as a dictionary
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_regionCoupledWallPolyPatch_Header
