#pragma once
#ifndef _lduPrimitiveMesh_Header
#define _lduPrimitiveMesh_Header

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
	tnbLib::lduPrimitiveMesh

Description
	Simplest contrete lduMesh which stores the addressing needed by lduMatrix.

SourceFiles
	lduPrimitiveMesh.C

\*---------------------------------------------------------------------------*/

#include <lduMesh.hxx>
#include <labelList.hxx>

#include <lduInterfacePtrsList.hxx>  // added by amir
#include <PtrList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class lduPrimitiveMesh Declaration
	\*---------------------------------------------------------------------------*/

	class lduPrimitiveMesh
		:
		public lduMesh,
		public lduAddressing
	{
		// Private Data

			//- Lower addressing
		labelList lowerAddr_;

		//- Upper addressing
		labelList upperAddr_;

		//- List of pointers for each patch
		//  with only those pointing to interfaces being set
		lduInterfacePtrsList interfaces_;

		//- Concrete interfaces
		PtrList<const lduInterface> primitiveInterfaces_;

		//- Patch field evaluation schedule
		lduSchedule patchSchedule_;

		//- Communicator to use for any parallel communication
		const label comm_;


		// Private Member Functions

			//- Get size of all meshes
		static FoamBase_EXPORT label totalSize(const PtrList<lduPrimitiveMesh>&);

		static FoamBase_EXPORT labelList upperTriOrder
		(
			const label nCells,
			const labelUList& lower,
			const labelUList& upper
		);

		//- Check if in upper-triangular ordering
		static FoamBase_EXPORT void checkUpperTriangular
		(
			const label size,
			const labelUList& l,
			const labelUList& u
		);


	public:

		// Static data

			// Declare name of the class and its debug switch
		//ClassName("lduPrimitiveMesh");
		static const char* typeName_() { return "lduPrimitiveMesh"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;

		// Constructors

			//- Construct from components but without interfaces. Add interfaces
			//  separately using addInterfaces
		FoamBase_EXPORT lduPrimitiveMesh
		(
			const label nCells,
			labelList& l,
			labelList& u,
			const label comm,
			bool reuse
		);

		//- Add interfaces to a mesh constructed without
		FoamBase_EXPORT void addInterfaces
		(
			lduInterfacePtrsList& interfaces,
			const lduSchedule& ps
		);

		//- Construct from components and re-use storage.
		FoamBase_EXPORT lduPrimitiveMesh
		(
			const label nCells,
			labelList& l,
			labelList& u,
			PtrList<const lduInterface>& primitiveInterfaces,
			const lduSchedule& ps,
			const label comm
		);

		//- Construct by combining multiple meshes. The meshes come from
		//  processors procIDs:
		//  procIDs[0] : local processor (myMesh)
		//  procIDs[i] : processor where otherMeshes[i-1] comes from
		//  procAgglomMap : for every processor which processor it agglomerates
		//                  onto. The new processor numbers are in compact
		//                  numbering (so ranks in communicator comm), i.e.
		//                  similar to cell-restrict-addressing.
		//                  We need this information to be able to map
		//                  inter-processor interfaces
		// cellOffsets : for every processor the offset it gets in the mesh
		// faceMap     : for every processor, for every face, the destination
		//               face. Negative for flipped faces.
		// boundaryMap : for every processor, for every patch, -1 or the new
		//               patch index in the mesh.
		// boundaryFaceMap : for every processor, for every patch, for every
		//                   patch face:
		//                   - the new internal face (if boundaryMap=-1)
		//                   - the new patch face (if boundaryMap>=0)
		//                   Faces becoming internal are negative for flipped
		//                   faces.
		FoamBase_EXPORT lduPrimitiveMesh
		(
			const label comm,
			const labelList& procAgglomMap,

			const labelList& procIDs,
			const lduMesh& myMesh,
			const PtrList<lduPrimitiveMesh>& otherMeshes,

			labelList& cellOffsets,
			labelList& faceOffsets,
			labelListList& faceMap,
			labelListList& boundaryMap,
			labelListListList& boundaryFaceMap
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT lduPrimitiveMesh(const lduPrimitiveMesh&) = delete;


		//- Destructor
		virtual ~lduPrimitiveMesh()
		{}


		// Member Functions

			// Access

				//- Return ldu addressing
		virtual const lduAddressing& lduAddr() const
		{
			return *this;
		}

		//- Return a list of pointers for each patch
		//  with only those pointing to interfaces being set
		virtual lduInterfacePtrsList interfaces() const
		{
			return interfaces_;
		}

		//- Return a list of pointers for each patch
		//  with only those pointing to interfaces being set
		//  (reference to cached interfaces)
		const lduInterfacePtrsList& rawInterfaces() const
		{
			return interfaces_;
		}

		//- Return communicator used for parallel communication
		virtual label comm() const
		{
			return comm_;
		}

		//- Return Lower addressing
		virtual const labelUList& lowerAddr() const
		{
			return lowerAddr_;
		}

		//- Return Upper addressing
		virtual const labelUList& upperAddr() const
		{
			return upperAddr_;
		}

		//- Return patch addressing
		virtual const labelUList& patchAddr(const label i) const
		{
			return interfaces_[i].faceCells();
		}

		//- Return patch evaluation schedule
		virtual const lduSchedule& patchSchedule() const
		{
			return patchSchedule_;
		}


		// Helper

			//- Select either mesh0 (meshI is 0) or otherMeshes[meshI-1]
		static FoamBase_EXPORT const lduMesh& mesh
		(
			const lduMesh& mesh0,
			const PtrList<lduPrimitiveMesh>& otherMeshes,
			const label meshI
		);

		//- Gather meshes from other processors onto procIDs[0].
		//  Received meshes get GAMGInterface and communicator comm
		static FoamBase_EXPORT void gather
		(
			const label comm,
			const lduMesh& mesh,
			const labelList& procIDs,
			PtrList<lduPrimitiveMesh>& otherMeshes
		);

		//- Get non-scheduled send/receive schedule
		template<class ProcPatch>
		static lduSchedule nonBlockingSchedule(const lduInterfacePtrsList&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const lduPrimitiveMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <lduPrimitiveMeshTemplatesI.hxx>

//#ifdef NoRepository
//#include <lduPrimitiveMeshTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lduPrimitiveMesh_Header
