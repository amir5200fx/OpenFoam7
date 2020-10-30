#pragma once
#ifndef _polyBoundaryMesh_Header
#define _polyBoundaryMesh_Header

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
	tnbLib::polyBoundaryMesh

Description
	tnbLib::polyBoundaryMesh

SourceFiles
	polyBoundaryMesh.C

\*---------------------------------------------------------------------------*/

#include <polyPatchList.hxx>
#include <regIOobject.hxx>
#include <labelPair.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class wordRe;

	// Forward declaration of friend functions and operators

	FoamBase_EXPORT Ostream& operator<<(Ostream&, const polyBoundaryMesh&);


	/*---------------------------------------------------------------------------*\
						  Class polyBoundaryMesh Declaration
	\*---------------------------------------------------------------------------*/

	class polyBoundaryMesh
		:
		public polyPatchList,
		public regIOobject
	{
		// private data

			//- Reference to mesh
		const polyMesh& mesh_;

		mutable autoPtr<labelList> patchIDPtr_;

		mutable autoPtr<HashTable<labelList, word>> groupPatchIDsPtr_;

		//- Edges of neighbouring patches
		mutable autoPtr<List<labelPairList>> neighbourEdgesPtr_;


		// Private Member Functions

			//- Calculate the geometry for the patches (transformation tensors etc.)
		FoamBase_EXPORT void calcGeometry();

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT polyBoundaryMesh(const polyBoundaryMesh&);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const polyBoundaryMesh&);


	public:

		//- Declare friendship with polyMesh
		friend class polyMesh;


		//- Runtime type information
		//TypeName("polyBoundaryMesh");
		static const char* typeName_() { return "polyBoundaryMesh"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Read constructor given IOobject and a polyMesh reference
			//  Note point pointers are unset, only used in copying meshes
		FoamBase_EXPORT polyBoundaryMesh
		(
			const IOobject&,
			const polyMesh&
		);

		//- Construct given size
		FoamBase_EXPORT polyBoundaryMesh
		(
			const IOobject&,
			const polyMesh&,
			const label size
		);

		//- Construct given polyPatchList
		FoamBase_EXPORT polyBoundaryMesh
		(
			const IOobject&,
			const polyMesh&,
			const polyPatchList&
		);


		//- Destructor
		FoamBase_EXPORT ~polyBoundaryMesh();

		//- Clear geometry at this level and at patches
		FoamBase_EXPORT void clearGeom();

		//- Clear addressing at this level and at patches
		FoamBase_EXPORT void clearAddressing();


		// Member Functions

			//- Return the mesh reference
		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Per patch the edges on the neighbouring patch. Is for every external
		//  edge the neighbouring patch and neighbouring (external) patch edge
		//  label. Note that edge indices are offset by nInternalEdges to keep
		//  it as much as possible consistent with coupled patch addressing
		//  (where coupling is by local patch face index).
		//  Only valid for singly connected polyBoundaryMesh and not parallel
		FoamBase_EXPORT const List<labelPairList>& neighbourEdges() const;

		//- Return a list of patch names
		FoamBase_EXPORT wordList names() const;

		//- Return a list of patch types
		FoamBase_EXPORT wordList types() const;

		//- Return a list of physical types
		FoamBase_EXPORT wordList physicalTypes() const;

		//- Return patch indices for all matches. Optionally matches patchGroups
		FoamBase_EXPORT labelList findIndices
		(
			const keyType&,
			const bool usePatchGroups = true
		) const;

		//- Return patch index for the first match, return -1 if not found
		FoamBase_EXPORT label findIndex(const keyType&) const;

		//- Find patch index given a name
		FoamBase_EXPORT label findPatchID(const word& patchName) const;

		//- Find patch indices for a given polyPatch type
		template<class Type>
		labelHashSet findPatchIDs() const;

		//- Return patch index for a given face label
		FoamBase_EXPORT label whichPatch(const label faceIndex) const;

		//- Per boundary face label the patch index
		FoamBase_EXPORT const labelList& patchID() const;

		//- Per patch group the patch indices
		FoamBase_EXPORT const HashTable<labelList, word>& groupPatchIDs() const;

		//- Set/add group with patches
		FoamBase_EXPORT void setGroup(const word& groupName, const labelList& patchIDs);

		//- Return the set of patch IDs corresponding to the given names
		//  By default warns if given names are not found. Optionally
		//  matches to patchGroups as well as patchNames
		FoamBase_EXPORT labelHashSet patchSet
		(
			const UList<wordRe>& patchNames,
			const bool warnNotFound = true,
			const bool usePatchGroups = true
		) const;

		//- Match the patches to groups. Returns all the (fully matched) groups
		//  and any remaining unmatched patches.
		FoamBase_EXPORT void matchGroups
		(
			const labelUList& patchIDs,
			wordList& groups,
			labelHashSet& nonGroupPatches
		) const;

		//- Check whether all procs have all patches and in same order. Return
		//  true if in error.
		FoamBase_EXPORT bool checkParallelSync(const bool report = false) const;

		//- Check boundary definition. Return true if in error.
		FoamBase_EXPORT bool checkDefinition(const bool report = false) const;

		//- Correct polyBoundaryMesh after moving points
		FoamBase_EXPORT void movePoints(const pointField&);

		//- Correct polyBoundaryMesh after topology update
		FoamBase_EXPORT void updateMesh();

		//- Reorders patches. Ordering does not have to be done in
		//  ascending or descending order. Reordering has to be unique.
		//  (is shuffle) If validBoundary calls updateMesh()
		//  after reordering to recalculate data (so call needs to be parallel
		//  sync in that case)
		FoamBase_EXPORT void shuffle(const labelUList& newToOld, const bool validBoundary);

		//- writeData member function required by regIOobject
		FoamBase_EXPORT bool writeData(Ostream&) const;

		//- Write using given format, version and form uncompression
		FoamBase_EXPORT bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write = true
		) const;


		// Member Operators

			//- Return const and non-const reference to polyPatch by index.
		using polyPatchList::operator[];

		//- Return const reference to polyPatch by name.
		FoamBase_EXPORT const polyPatch& operator[](const word&) const;

		//- Return reference to polyPatch by name.
		FoamBase_EXPORT polyPatch& operator[](const word&);


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const polyBoundaryMesh&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <polyBoundaryMeshTemplatesI.hxx>

//#ifdef NoRepository
//#include <polyBoundaryMeshTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyBoundaryMesh_Header
