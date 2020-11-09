#pragma once
#ifndef _meshReader_Header
#define _meshReader_Header

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

Namespace
	tnbLib::meshReaders

Description
	A namespace for holding various types of mesh readers.


Class
	tnbLib::meshReader

Description
	This class supports creating polyMeshes with baffles.

	The derived classes are responsible for providing the protected data.
	This implementation is somewhat messy, but could/should be restructured
	to provide a more generalized reader (at the moment it has been written
	for converting pro-STAR data).

	The meshReader supports cellTable information (see new user's guide entry).

Note
	The boundary definitions are given as cell/face.

SourceFiles
	calcPointCells.C
	createPolyBoundary.C
	createPolyCells.C
	meshReader.C
	meshReaderAux.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <HashTable.hxx>
#include <IOstream.hxx>

#include <cellTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class meshReader Declaration
	\*---------------------------------------------------------------------------*/

	class meshReader
	{
	protected:

		//- Identify cell faces in terms of cell Id and face Id
		class cellFaceIdentifier
		{
		public:
			// Public data

				//- Cell Id
			label cell;

			//- Face Id
			label face;


			// Constructors

				//- Construct null
			cellFaceIdentifier() : cell(-1), face(-1) {}

			//- Construct from cell/face components
			cellFaceIdentifier(label c, label f) : cell(c), face(f) {}


			// Check

				//- Used if cell or face are non-negative
			bool used() const
			{
				return (cell >= 0 && face >= 0);
			}

			//- Unused if cell or face are negative
			bool unused() const
			{
				return (cell < 0 || face < 0);
			}


			// Member Operators

			bool operator!=(const cellFaceIdentifier& cf) const
			{
				return (cell != cf.cell || face != cf.face);
			}

			bool operator==(const cellFaceIdentifier& cf) const
			{
				return (cell == cf.cell && face == cf.face);
			}

			// IOstream Operators

			friend Ostream& operator<<
				(
					Ostream& os,
					const cellFaceIdentifier& cf
					)
			{
				os << "(" << cf.cell << "/" << cf.face << ")";
				return os;
			}
		};


	private:

		// Private Data

			//- Point-cell addressing. Used for topological analysis
			// Warning. This point cell addressing list potentially contains
			// duplicate cell entries. Use additional checking
		mutable labelListList* pointCellsPtr_;

		//- Number of internal faces for polyMesh
		label nInternalFaces_;

		//- Polyhedral mesh boundary patch start indices and dimensions
		labelList patchStarts_;
		labelList patchSizes_;

		//- Association between two faces
		List<labelPair> interfaces_;

		//- List of cells/faces id pairs for each baffle
		List<List<cellFaceIdentifier>> baffleIds_;

		//- Global face list for polyMesh
		faceList meshFaces_;

		//- Cells as polyhedra for polyMesh
		cellList cellPolys_;

		//- Face sets for monitoring
		HashTable<List<label>, word, string::hash> monitoringSets_;


		// Private Member Functions

			//- Calculate pointCells
		FoamConversion_EXPORT void calcPointCells() const;

		FoamConversion_EXPORT const labelListList& pointCells() const;

		//- Make polyhedral cells and global faces if the mesh is polyhedral
		FoamConversion_EXPORT void createPolyCells();

		//- Add in boundary face
		FoamConversion_EXPORT void addPolyBoundaryFace
		(
			const label cellId,
			const label cellFaceId,
			const label nCreatedFaces
		);

		//- Add in boundary face
		FoamConversion_EXPORT void addPolyBoundaryFace
		(
			const cellFaceIdentifier& identifier,
			const label nCreatedFaces
		);

		//- Add cellZones based on cellTable Id
		FoamConversion_EXPORT void addCellZones(polyMesh&) const;

		//- Add faceZones based on monitoring boundary conditions
		FoamConversion_EXPORT void addFaceZones(polyMesh&) const;

		//- Make polyhedral boundary from shape boundary
		// (adds more faces to the face list)
		FoamConversion_EXPORT void createPolyBoundary();

		//- Add polyhedral boundary
		FoamConversion_EXPORT List<polyPatch*> polyBoundaryPatches(const polyMesh&);

		//- Clear extra storage before creation of the mesh to remove
		//  a memory peak
		FoamConversion_EXPORT void clearExtraStorage();

		FoamConversion_EXPORT void writeInterfaces(const objectRegistry&) const;

		//- Write List<label> in constant/polyMesh
		FoamConversion_EXPORT void writeMeshLabelList
		(
			const objectRegistry& registry,
			const word& propertyName,
			const labelList& list,
			IOstream::streamFormat fmt = IOstream::ASCII
		) const;

		//- Return list of faces for every cell
		faceListList& cellFaces() const
		{
			return const_cast<faceListList&>(cellFaces_);
		}


	protected:

		// Protected member data

			//- Pointers to cell shape models
		static FoamConversion_EXPORT const cellModel* unknownModel;
		static FoamConversion_EXPORT const cellModel* tetModel;
		static FoamConversion_EXPORT const cellModel* pyrModel;
		static FoamConversion_EXPORT const cellModel* prismModel;
		static FoamConversion_EXPORT const cellModel* hexModel;

		//- Referenced filename
		fileName geometryFile_;

		//- Geometry scaling
		scalar scaleFactor_;

		//- Points supporting the mesh
		pointField points_;

		//- Lookup original Cell number for a given cell
		labelList origCellId_;

		//- Identify boundary faces by cells and their faces
		//  for each patch
		List<List<cellFaceIdentifier>> boundaryIds_;

		//- Boundary patch types
		wordList patchTypes_;

		//- Boundary patch names
		wordList patchNames_;

		//- Boundary patch physical types
		wordList patchPhysicalTypes_;

		//- List of faces for every cell
		faceListList cellFaces_;

		//- List of each baffle face
		faceList baffleFaces_;

		//- Cell table id for each cell
		labelList cellTableId_;

		//- Cell table persistent data saved as a dictionary
		cellTable cellTable_;


		// Protected member functions

			//- Subclasses are required to supply this information
		FoamConversion_EXPORT virtual bool readGeometry(const scalar scaleFactor = 1.0) = 0;


	public:

		// Static Members

			//- Warn about repeated names
		static FoamConversion_EXPORT void warnDuplicates(const word& context, const wordList&);


		// Constructors

			//- Construct from fileName
		FoamConversion_EXPORT meshReader(const fileName&, const scalar scaleFactor = 1.0);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT meshReader(const meshReader&) = delete;


		//- Destructor
		FoamConversion_EXPORT virtual ~meshReader();


		// Member Functions

			//- Create and return polyMesh
		FoamConversion_EXPORT virtual autoPtr<polyMesh> mesh(const objectRegistry&);

		//- Write auxiliary information
		FoamConversion_EXPORT void writeAux(const objectRegistry&) const;

		//- Write mesh
		FoamConversion_EXPORT void writeMesh
		(
			const polyMesh&,
			IOstream::streamFormat fmt = IOstream::BINARY
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const meshReader&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


#endif // !_meshReader_Header
