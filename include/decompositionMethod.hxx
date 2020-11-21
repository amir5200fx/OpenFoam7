#pragma once
#ifndef _decompositionMethod_Header
#define _decompositionMethod_Header

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
	tnbLib::decompositionMethod

Description
	Abstract base class for decomposition

SourceFiles
	decompositionMethod.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <CompactListList.hxx>
#include <decompositionConstraint.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class decompositionMethod Declaration
	\*---------------------------------------------------------------------------*/

	class decompositionMethod
	{
	protected:

		// Protected data

		const dictionary& decompositionDict_;
		label nProcessors_;

		//- Optional constraints
		PtrList<decompositionConstraint> constraints_;


	public:

		//- Runtime type information
		//TypeName("decompositionMethod");
		static const char* typeName_() { return "decompositionMethod"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			decompositionMethod,
			dictionary,
			(
				const dictionary& decompositionDict
				),
				(decompositionDict)
		);*/

		typedef autoPtr<decompositionMethod> (*dictionaryConstructorPtr)(const dictionary& decompositionDict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamParallel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamParallel_EXPORT void constructdictionaryConstructorTables();
		static FoamParallel_EXPORT void destroydictionaryConstructorTables();

		template <class decompositionMethodType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<decompositionMethod> New(const dictionary& decompositionDict)
			{
				return autoPtr<decompositionMethod>(new decompositionMethodType(decompositionDict));
			}

			adddictionaryConstructorToTable(const word& lookup = decompositionMethodType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "decompositionMethod"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class decompositionMethodType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<decompositionMethod> New(const dictionary& decompositionDict)
			{
				return autoPtr<decompositionMethod>(new decompositionMethodType(decompositionDict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = decompositionMethodType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Constructors

			//- Construct given the decomposition dictionary
		FoamParallel_EXPORT decompositionMethod(const dictionary& decompositionDict);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT decompositionMethod(const decompositionMethod&) = delete;


		// Selectors

			//- Return a reference to the selected decomposition method
		static FoamParallel_EXPORT autoPtr<decompositionMethod> New
		(
			const dictionary& decompositionDict
		);


		//- Destructor
		virtual ~decompositionMethod()
		{}


		// Member Functions

		label nDomains() const
		{
			return nProcessors_;
		}

		//- Is method parallel aware (i.e. does it synchronize domains across
		//  proc boundaries)
		FoamParallel_EXPORT virtual bool parallelAware() const = 0;


		// No topology (implemented by geometric decomposers)

			//- Return for every coordinate the wanted processor number.
		virtual labelList decompose
		(
			const pointField& points,
			const scalarField& pointWeights
		)
		{
			NotImplemented;
			return labelList(0);
		}

		//- Like decompose but with uniform weights on the points
		virtual labelList decompose(const pointField&)
		{
			NotImplemented;
			return labelList(0);
		}


		// Topology provided by mesh

			//- Return for every coordinate the wanted processor number. Use the
			//  mesh connectivity (if needed)
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const pointField& points,
			const scalarField& pointWeights
		) = 0;

		//- Like decompose but with uniform weights on the points
		FoamParallel_EXPORT virtual labelList decompose(const polyMesh&, const pointField&);


		//- Return for every coordinate the wanted processor number. Gets
		//  passed agglomeration map (from fine to coarse cells) and coarse
		//  cell
		//  location. Can be overridden by decomposers that provide this
		//  functionality natively. Coarse cells are local to the processor
		//  (if in parallel). If you want to have coarse cells spanning
		//  processors use the globalCellCells instead.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const labelList& cellToRegion,
			const pointField& regionPoints,
			const scalarField& regionWeights
		);

		//- Like decompose but with uniform weights on the regions
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const labelList& cellToRegion,
			const pointField& regionPoints
		);


		// Topology provided explicitly addressing

			//- Return for every coordinate the wanted processor number.
			//  The connectivity is equal to mesh.cellCells() except for
			//  - in parallel the cell numbers are global cell numbers
			//    (starting
			//    from 0 at processor0 and then incrementing all through the
			//    processors)
			//  - the connections are across coupled patches
		FoamParallel_EXPORT virtual labelList decompose
		(
			const labelListList& globalCellCells,
			const pointField& cc,
			const scalarField& cWeights
		) = 0;

		//- Like decompose but with uniform weights on the cells
		FoamParallel_EXPORT virtual labelList decompose
		(
			const labelListList& globalCellCells,
			const pointField& cc
		);


		// Other

			//- Helper: determine (local or global) cellCells from mesh
			//  agglomeration. Agglomeration is local to the processor.
			//  local  : connections are in local indices. Coupled across
			//           cyclics but not processor patches.
			//  global : connections are in global indices. Coupled across
			//            cyclics and processor patches.
		static FoamParallel_EXPORT void calcCellCells
		(
			const polyMesh& mesh,
			const labelList& agglom,
			const label nLocalCoarse,
			const bool global,
			CompactListList<label>& cellCells
		);

		//- Helper: determine (local or global) cellCells and face weights
		//  from mesh agglomeration.
		//  Uses mag of faceArea as weights
		static FoamParallel_EXPORT void calcCellCells
		(
			const polyMesh& mesh,
			const labelList& agglom,
			const label nLocalCoarse,
			const bool parallel,
			CompactListList<label>& cellCells,
			CompactListList<scalar>& cellCellWeights
		);

		//- Helper: extract constraints:
		//  blockedface: existing faces where owner and neighbour on same
		//               proc
		//  explicitConnections: sets of boundary faces  ,,     ,,
		//  specifiedProcessorFaces: groups of faces with all cells on
		//  same processor.
		FoamParallel_EXPORT void setConstraints
		(
			const polyMesh& mesh,
			boolList& blockedFace,
			PtrList<labelList>& specifiedProcessorFaces,
			labelList& specifiedProcessor,
			List<labelPair>& explicitConnections
		);

		//- Helper: apply constraints to a decomposition. This gives
		//  constraints opportunity to modify decomposition in case
		//  the native decomposition method has not obeyed all constraints
		FoamParallel_EXPORT void applyConstraints
		(
			const polyMesh& mesh,
			const boolList& blockedFace,
			const PtrList<labelList>& specifiedProcessorFaces,
			const labelList& specifiedProcessor,
			const List<labelPair>& explicitConnections,
			labelList& finalDecomp
		);

		// Decompose a mesh with constraints:
		// - blockedFace : whether owner and neighbour should be on same
		//   processor
		// - specifiedProcessorFaces, specifiedProcessor : sets of faces
		//   that should go to same processor (as specified in
		//   specifiedProcessor, can be -1)
		// - explicitConnections : connections between baffle faces
		//   (blockedFace should be false on these). Owner and
		//   neighbour on same processor.
		// Set all to zero size to have unconstrained decomposition.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const scalarField& cellWeights,
			const boolList& blockedFace,
			const PtrList<labelList>& specifiedProcessorFaces,
			const labelList& specifiedProcessor,
			const List<labelPair>& explicitConnections
		);


		//- Decompose a mesh. Apply all constraints from decomposeParDict
		//  ('preserveFaceZones' etc). Calls either
		//  - no constraints, empty weights:
		//      decompose(mesh, cellCentres())
		//  - no constraints, set weights:
		//      decompose(mesh, cellCentres(), cellWeights)
		//  - valid constraints:
		//      decompose(mesh, cellToRegion, regionPoints, regionWeights)
		FoamParallel_EXPORT labelList decompose
		(
			const polyMesh& mesh,
			const scalarField& cWeights
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const decompositionMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_decompositionMethod_Header
