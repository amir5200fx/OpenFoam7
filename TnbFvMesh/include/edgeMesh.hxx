#pragma once
#ifndef _edgeMesh_Header
#define _edgeMesh_Header

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
	tnbLib::edgeMesh

Description
	Points connected by edges.

	Can be read from fileName based on extension. Uses ::New factory method
	to select the reader and transfer the result.

SourceFiles
	edgeMeshI.H
	edgeMesh.C
	edgeMeshIO.C
	edgeMeshNew.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <edgeList.hxx>
#include <edgeMeshFormatsCore.hxx>
#include <runTimeSelectionTables.hxx>
#include <memberFunctionSelectionTables.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class edgeMesh;
	FoamFvMesh_EXPORT Istream& operator>>(Istream&, edgeMesh&);
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const edgeMesh&);


	/*---------------------------------------------------------------------------*\
							   Class edgeMesh Declaration
	\*---------------------------------------------------------------------------*/

	class edgeMesh
		:
		public fileFormats::edgeMeshFormatsCore
	{
		// Private Data

			//- Vertices of the edges
		pointField points_;

		//- The edges defining the boundary
		edgeList edges_;

		//- From point to edges
		mutable autoPtr<labelListList> pointEdgesPtr_;


		// Private Member Functions

			//- Calculate point-edge addressing (inverse of edges)
		FoamFvMesh_EXPORT void calcPointEdges() const;


	protected:

		// Protected Member Functions

			//- Non-const access to global points
		inline pointField& storedPoints();

		//- Non-const access to the edges
		inline edgeList& storedEdges();


	public:

		//- Runtime type information
		/*TypeName("edgeMesh");*/
		static const char* typeName_() { return "edgeMesh"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Static

			//- Can we read this file format?
		static FoamFvMesh_EXPORT bool canRead(const fileName&, const bool verbose = false);

		//- Can we read this file format?
		static FoamFvMesh_EXPORT bool canReadType(const word& ext, const bool verbose = false);

		//- Can we write this file format type?
		static FoamFvMesh_EXPORT bool canWriteType(const word& ext, const bool verbose = false);

		static FoamFvMesh_EXPORT wordHashSet readTypes();
		static FoamFvMesh_EXPORT wordHashSet writeTypes();


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT edgeMesh();

		//- Construct from components
		FoamFvMesh_EXPORT edgeMesh(const pointField&, const edgeList&);

		//- Construct by transferring components (points, edges).
		FoamFvMesh_EXPORT edgeMesh
		(
			pointField&&,
			edgeList&&
		);

		//- Copy constructor
		FoamFvMesh_EXPORT edgeMesh(const edgeMesh&);

		//- Move constructor
		FoamFvMesh_EXPORT edgeMesh(edgeMesh&&);

		//- Construct from file name (uses extension to determine type)
		FoamFvMesh_EXPORT edgeMesh(const fileName&);

		//- Construct from file name (uses extension to determine type)
		FoamFvMesh_EXPORT edgeMesh(const fileName&, const word& ext);

		//- Construct from Istream
		FoamFvMesh_EXPORT edgeMesh(Istream&);


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			edgeMesh,
			fileExtension,
			(
				const fileName& name
				),
				(name)
		);*/

		typedef autoPtr<edgeMesh> (*fileExtensionConstructorPtr)(const fileName& name);
		typedef HashTable<fileExtensionConstructorPtr, word, string::hash> fileExtensionConstructorTable;
		static FoamFvMesh_EXPORT fileExtensionConstructorTable* fileExtensionConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructfileExtensionConstructorTables();
		static FoamFvMesh_EXPORT void destroyfileExtensionConstructorTables();

		template <class edgeMeshType>
		class addfileExtensionConstructorToTable
		{
		public:
			static autoPtr<edgeMesh> New(const fileName& name) { return autoPtr<edgeMesh>(new edgeMeshType(name)); }

			addfileExtensionConstructorToTable(const word& lookup = edgeMeshType::typeName)
			{
				constructfileExtensionConstructorTables();
				if (!fileExtensionConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "edgeMesh" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfileExtensionConstructorToTable() { destroyfileExtensionConstructorTables(); }
		};

		template <class edgeMeshType>
		class addRemovablefileExtensionConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<edgeMesh> New(const fileName& name) { return autoPtr<edgeMesh>(new edgeMeshType(name)); }

			addRemovablefileExtensionConstructorToTable(const word& lookup = edgeMeshType::typeName) : lookup_(lookup)
			{
				constructfileExtensionConstructorTables();
				fileExtensionConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefileExtensionConstructorToTable()
			{
				if (fileExtensionConstructorTablePtr_) { fileExtensionConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Selectors

			//- Select constructed from filename (explicit extension)
		static FoamFvMesh_EXPORT autoPtr<edgeMesh> New
		(
			const fileName&,
			const word& ext
		);

		//- Select constructed from filename (implicit extension)
		static FoamFvMesh_EXPORT autoPtr<edgeMesh> New(const fileName&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~edgeMesh();


		// Member Function Selectors

		/*declareMemberFunctionSelectionTable
		(
			void,
			edgeMesh,
			write,
			fileExtension,
			(
				const fileName& name,
				const edgeMesh& mesh
				),
				(name, mesh)
		);*/

		typedef void (*writefileExtensionMemberFunctionPtr)(const fileName& name, const edgeMesh& mesh);
		typedef HashTable<writefileExtensionMemberFunctionPtr, word, string::hash> writefileExtensionMemberFunctionTable;
		static FoamFvMesh_EXPORT writefileExtensionMemberFunctionTable* writefileExtensionMemberFunctionTablePtr_;

		template <class edgeMeshType>
		class addwritefileExtensionMemberFunctionToTable
		{
		public:
			addwritefileExtensionMemberFunctionToTable(const word& lookup = edgeMeshType::typeName)
			{
				constructwritefileExtensionMemberFunctionTables();
				writefileExtensionMemberFunctionTablePtr_->insert(lookup, edgeMeshType::write);
			}

			~addwritefileExtensionMemberFunctionToTable() { destroywritefileExtensionMemberFunctionTables(); }
		};

		static FoamFvMesh_EXPORT void constructwritefileExtensionMemberFunctionTables();
		static FoamFvMesh_EXPORT void destroywritefileExtensionMemberFunctionTables();

		//- Write to file
		static FoamFvMesh_EXPORT void write(const fileName&, const edgeMesh&);


		// Member Functions

			//- Transfer the contents of the argument and annul the argument
		FoamFvMesh_EXPORT void transfer(edgeMesh&);


		// Read

			//- Read from file. Chooses reader based on explicit extension
		FoamFvMesh_EXPORT bool read(const fileName&, const word& ext);

		//- Read from file. Chooses reader based on detected extension
		FoamFvMesh_EXPORT virtual bool read(const fileName&);


		// Access

			//- Return points
		inline const pointField& points() const;

		//- Return edges
		inline const edgeList& edges() const;

		//- Return edges
		inline const labelListList& pointEdges() const;

		//- Find connected regions. Set region number per edge.
		//  Returns number of regions.
		FoamFvMesh_EXPORT label regions(labelList& edgeRegion) const;


		// Edit

			//- Clear all storage
		FoamFvMesh_EXPORT virtual void clear();

		//- Reset primitive data (points, edges)
		//  Note, optimized to avoid overwriting data (with null)
		FoamFvMesh_EXPORT virtual void reset
		(
			pointField&& points,
			edgeList&& edges
		);

		//- Scale points. A non-positive factor is ignored
		FoamFvMesh_EXPORT virtual void scalePoints(const scalar);

		//- Merge common points (points within mergeDist). Return map from
		//  old to new points.
		FoamFvMesh_EXPORT virtual void mergePoints(const scalar mergeDist, labelList&);

		//- Merge duplicate edges
		FoamFvMesh_EXPORT virtual void mergeEdges();


		// Write

		FoamFvMesh_EXPORT virtual void writeStats(Ostream&) const;

		//- Generic write routine. Chooses writer based on extension.
		virtual void write(const fileName& name) const
		{
			write(name, *this);
		}


		// Member Operators

		inline void operator=(const edgeMesh&);
		inline void operator=(edgeMesh&&);


		// Ostream Operator

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const edgeMesh&);
		friend FoamFvMesh_EXPORT Istream& operator>>(Istream&, edgeMesh&);

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <edgeMeshI.hxx>

#endif // !_edgeMesh_Header
