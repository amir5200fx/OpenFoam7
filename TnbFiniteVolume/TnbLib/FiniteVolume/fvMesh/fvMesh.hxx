#pragma once
#ifndef _fvMesh_Header
#define _fvMesh_Header

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
	tnbLib::fvMesh

Description
	Mesh data needed to do the Finite Volume discretisation.

	NOTE ON USAGE:
	fvMesh contains all the topological and geometric information
	related to the mesh.  It is also responsible for keeping the data
	up-to-date.  This is done by deleting the cell volume, face area,
	cell/face centre, addressing and other derived information as
	required and recalculating it as necessary.  The fvMesh therefore
	reserves the right to delete the derived information upon every
	topological (mesh refinement/morphing) or geometric change (mesh
	motion).  It is therefore unsafe to keep local references to the
	derived data outside of the time loop.

SourceFiles
	fvMesh.C
	fvMeshGeometry.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <lduMesh.hxx>
#include <primitiveMesh.hxx>
#include <fvBoundaryMesh.hxx>
#include <surfaceInterpolation.hxx>
#include <fvSchemes.hxx>
#include <fvSolution.hxx>
#include <data.hxx>
#include <DimensionedField.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <pointFieldsFwd.hxx>
#include <slicedVolFieldsFwd.hxx>
#include <slicedSurfaceFieldsFwd.hxx>
#include <className.hxx>

#include <processorFvPatch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMeshLduAddressing;
	class volMesh;


	/*---------------------------------------------------------------------------*\
							   Class fvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class fvMesh
		:
		public polyMesh,
		public lduMesh,
		public surfaceInterpolation,
		public fvSchemes,
		public fvSolution,
		public data
	{
		// Private Data

			//- Boundary mesh
		fvBoundaryMesh boundary_;


		// Demand-driven data

		mutable fvMeshLduAddressing* lduPtr_;

		//- Current time index for cell volumes
		//  Note.  The whole mechanism will be replaced once the
		//  dimensionedField is created and the dimensionedField
		//  will take care of the old-time levels.
		mutable label curTimeIndex_;

		//- Cell volumes old time level
		mutable void* VPtr_;

		//- Cell volumes old time level
		mutable DimensionedField<scalar, volMesh>* V0Ptr_;

		//- Cell volumes old-old time level
		mutable DimensionedField<scalar, volMesh>* V00Ptr_;

		//- Face area vectors
		mutable slicedSurfaceVectorField* SfPtr_;

		//- Mag face area vectors
		mutable surfaceScalarField* magSfPtr_;

		//- Cell centres
		mutable slicedVolVectorField* CPtr_;

		//- Face centres
		mutable slicedSurfaceVectorField* CfPtr_;

		//- Face motion fluxes
		mutable surfaceScalarField* phiPtr_;


		// Private Member Functions

			// Storage management

				//- Clear geometry but not the old-time cell volumes
		FoamFiniteVolume_EXPORT void clearGeomNotOldVol();

		//- Clear geometry like clearGeomNotOldVol but recreate any
		//  geometric demand-driven data that was set
		FoamFiniteVolume_EXPORT void updateGeomNotOldVol();

		//- Clear geometry
		FoamFiniteVolume_EXPORT void clearGeom();

		//- Clear addressing
		FoamFiniteVolume_EXPORT void clearAddressing(const bool isMeshUpdate = false);

		//- Preserve old volume(s)
		FoamFiniteVolume_EXPORT void storeOldVol(const scalarField&);


		// Make geometric data

		FoamFiniteVolume_EXPORT void makeSf() const;
		FoamFiniteVolume_EXPORT void makeMagSf() const;

		FoamFiniteVolume_EXPORT void makeC() const;
		FoamFiniteVolume_EXPORT void makeCf() const;


	public:

		// Public Typedefs

		typedef fvMesh Mesh;
		typedef fvBoundaryMesh BoundaryMesh;


		// Declare name of the class and its debug switch
		/*ClassName("fvMesh");*/
		static const char* typeName_() { return "fvMesh"; } 
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName; 
		static FoamFiniteVolume_EXPORT int debug;


		// Constructors

			//- Construct from IOobject
		FoamFiniteVolume_EXPORT explicit fvMesh(const IOobject& io);

		//- Construct from cellShapes with boundary.
		FoamFiniteVolume_EXPORT fvMesh
		(
			const IOobject& io,
			pointField&& points,
			const cellShapeList& shapes,
			const faceListList& boundaryFaces,
			const wordList& boundaryPatchNames,
			const PtrList<dictionary>& boundaryDicts,
			const word& defaultBoundaryPatchName,
			const word& defaultBoundaryPatchType,
			const bool syncPar = true
		);

		//- Construct from components without boundary.
		//  Boundary is added using addFvPatches() member function
		FoamFiniteVolume_EXPORT fvMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			labelList&& allOwner,
			labelList&& allNeighbour,
			const bool syncPar = true
		);

		//- Construct without boundary from cells rather than owner/neighbour.
		//  Boundary is added using addPatches() member function
		FoamFiniteVolume_EXPORT fvMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			cellList&& cells,
			const bool syncPar = true
		);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT fvMesh(const fvMesh&);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~fvMesh();


		// Member Functions

		// Helpers

		//- Add boundary patches. Constructor helper
		FoamFiniteVolume_EXPORT void addFvPatches
		(
			const List<polyPatch*>&,
			const bool validBoundary = true
		);

		//- Update the mesh based on the mesh files saved in time
		//  directories
		FoamFiniteVolume_EXPORT virtual readUpdateState readUpdate();


		// Access

			//- Return the top-level database
		const Time& time() const
		{
			return polyMesh::time();
		}

		//- Return the object registry - resolve conflict polyMesh/lduMesh
		virtual const objectRegistry& thisDb() const
		{
			return polyMesh::thisDb();
		}

		//- Return reference to name
		//  Note: name() is currently ambiguous due to derivation from
		//  surfaceInterpolation
		const word& name() const
		{
			return polyMesh::name();
		}

		//- Return reference to boundary mesh
		FoamFiniteVolume_EXPORT const fvBoundaryMesh& boundary() const;

		//- Return ldu addressing
		FoamFiniteVolume_EXPORT virtual const lduAddressing& lduAddr() const;

		//- Return a list of pointers for each patch
		//  with only those pointing to interfaces being set
		virtual lduInterfacePtrsList interfaces() const
		{
			return boundary().interfaces();
		}

		//- Return communicator used for parallel communication
		virtual label comm() const
		{
			return polyMesh::comm();
		}

		//- Internal face owner
		const labelUList& owner() const
		{
			return lduAddr().lowerAddr();
		}

		//- Internal face neighbour
		const labelUList& neighbour() const
		{
			return lduAddr().upperAddr();
		}

		//- Return cell volumes
		FoamFiniteVolume_EXPORT const DimensionedField<scalar, volMesh>& V() const;

		//- Return old-time cell volumes
		FoamFiniteVolume_EXPORT const DimensionedField<scalar, volMesh>& V0() const;

		//- Return old-old-time cell volumes
		FoamFiniteVolume_EXPORT const DimensionedField<scalar, volMesh>& V00() const;

		//- Return sub-cycle cell volumes
		FoamFiniteVolume_EXPORT tmp<DimensionedField<scalar, volMesh>> Vsc() const;

		//- Return sub-cycl old-time cell volumes
		FoamFiniteVolume_EXPORT tmp<DimensionedField<scalar, volMesh>> Vsc0() const;

		//- Return cell face area vectors
		FoamFiniteVolume_EXPORT const surfaceVectorField& Sf() const;

		//- Return cell face area magnitudes
		FoamFiniteVolume_EXPORT const surfaceScalarField& magSf() const;

		//- Return cell face motion fluxes
		FoamFiniteVolume_EXPORT const surfaceScalarField& phi() const;

		//- Return cell centres as volVectorField
		FoamFiniteVolume_EXPORT const volVectorField& C() const;

		//- Return face centres as surfaceVectorField
		FoamFiniteVolume_EXPORT const surfaceVectorField& Cf() const;

		//- Return face deltas as surfaceVectorField
		FoamFiniteVolume_EXPORT tmp<surfaceVectorField> delta() const;

		//- Return a labelType of valid component indicators
		//  1 : valid (solved)
		// -1 : invalid (not solved)
		template<class Type>
		typename pTraits<Type>::labelType validComponents() const;


		// Edit

			//- Clear all geometry and addressing
		FoamFiniteVolume_EXPORT void clearOut();

		//- Update mesh corresponding to the given map
		FoamFiniteVolume_EXPORT virtual void updateMesh(const mapPolyMesh& mpm);

		//- Move points, returns volumes swept by faces in motion
		FoamFiniteVolume_EXPORT virtual tmp<scalarField> movePoints(const pointField&);

		//- Map all fields in time using given map.
		FoamFiniteVolume_EXPORT virtual void mapFields(const mapPolyMesh& mpm);

		//- Add/insert single patch. If validBoundary the new situation
		//  is consistent across processors.
		FoamFiniteVolume_EXPORT virtual void addPatch
		(
			const label insertPatchi,
			const polyPatch& patch,
			const dictionary& patchFieldDict,
			const word& defaultPatchFieldType,
			const bool validBoundary
		);

		//- Reorder and trim existing patches. If validBoundary the new
		//  situation is consistent across processors
		FoamFiniteVolume_EXPORT virtual void reorderPatches
		(
			const labelUList& newToOld,
			const bool validBoundary
		);

		//- Remove boundary patches. Warning: fvPatchFields hold ref to
		//  these fvPatches.
		FoamFiniteVolume_EXPORT void removeFvBoundary();

		//- Return cell face motion fluxes
		FoamFiniteVolume_EXPORT surfaceScalarField& setPhi();

		//- Return old-time cell volumes
		FoamFiniteVolume_EXPORT DimensionedField<scalar, volMesh>& setV0();


		// Write

			//- Write the underlying polyMesh and other data
		FoamFiniteVolume_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write = true
		) const;

		//- Write mesh using IO settings from time
		FoamFiniteVolume_EXPORT virtual bool write(const bool write = true) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const fvMesh&);

		FoamFiniteVolume_EXPORT bool operator!=(const fvMesh&) const;
		FoamFiniteVolume_EXPORT bool operator==(const fvMesh&) const;
	};


	template<>
	FoamFiniteVolume_EXPORT typename pTraits<sphericalTensor>::labelType
		fvMesh::validComponents<sphericalTensor>() const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvMeshI.hxx>


//#ifdef NoRepository
//#include <fvMeshTemplates.cxx>
//#include <fvPatchFvMeshTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMesh_Header
