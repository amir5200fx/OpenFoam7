#pragma once
#ifndef _regionCoupledPolyPatch_Header
#define _regionCoupledPolyPatch_Header

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
	tnbLib::regionCoupledPolyPatch

Description
	Region coupled polyPatch

SourceFiles
	regionCoupledPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <regionCoupledBase.hxx>
#include <polyBoundaryMesh.hxx>
#include <polyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class regionCoupledPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledPolyPatch
		:
		public polyPatch,
		public regionCoupledBase
	{

	protected:

		// Protected Member Functions

			//- Initialise the calculation of the patch geometry
		FoamFvMesh_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamFvMesh_EXPORT virtual void initMovePoints(PstreamBuffers& pBufs, const pointField&);

		//- Correct patches after moving points
		FoamFvMesh_EXPORT virtual void movePoints(PstreamBuffers& pBufs, const pointField&);

		//- Initialise the update of the patch topology
		FoamFvMesh_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamFvMesh_EXPORT virtual void updateMesh(PstreamBuffers&);


	public:

		//- Runtime type information
		/*TypeName("regionCoupled");*/
		static const char* typeName_() { return "regionCoupled"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from (base couped patch) components
		FoamFvMesh_EXPORT regionCoupledPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT regionCoupledPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct as copy, resetting the boundary mesh
		FoamFvMesh_EXPORT regionCoupledPolyPatch
		(
			const regionCoupledPolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamFvMesh_EXPORT regionCoupledPolyPatch
		(
			const regionCoupledPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct given the original patch and a map
		FoamFvMesh_EXPORT regionCoupledPolyPatch
		(
			const regionCoupledPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);


		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new regionCoupledPolyPatch(*this, bm));
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
					new regionCoupledPolyPatch
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
					new regionCoupledPolyPatch
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
		FoamFvMesh_EXPORT virtual ~regionCoupledPolyPatch();


		// Member Functions

			// Access

				//- Is it coupled?
		virtual bool coupled() const
		{
			return false;
		}


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

#endif // !_regionCoupledPolyPatch_Header
