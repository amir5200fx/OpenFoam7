#pragma once
#ifndef _block_Header
#define _block_Header

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
	tnbLib::block

Description
	Creates a single block of cells from point coordinates, numbers of
	cells in each direction and an expansion ratio.

Note
	The vertices and cells for filling the block are demand-driven.

SourceFiles
	block.C
	blockCreate.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <labelList.hxx>

#include <blockDescriptor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class block;
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const block&);

	/*---------------------------------------------------------------------------*\
							   Class block Declaration
	\*---------------------------------------------------------------------------*/

	class block
		:
		public blockDescriptor
	{
		// Private Data

			//- List of points
		pointField points_;

		//- Boundary patches
		FixedList<List<FixedList<label, 4>>, 6> boundaryPatches_;


		// Private Member Functions

			//- Creates vertices for cells filling the block
		FoamFvMesh_EXPORT void createPoints();

		//- Creates boundary patch faces for the block
		FoamFvMesh_EXPORT void createBoundary();


	public:

		//- Runtime type information
		//TypeName("block");
		static const char* typeName_() { return "block"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			block,
			Istream,
			(
				const dictionary& dict,
				const label index,
				const pointField& vertices,
				const blockEdgeList& edges,
				const blockFaceList& faces,
				Istream& is
				),
				(dict, index, vertices, edges, faces, is)
		);*/

		typedef autoPtr<block> (*IstreamConstructorPtr)(const dictionary& dict, const label index, const pointField& vertices,
		                                                const blockEdgeList& edges, const blockFaceList& faces, Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamFvMesh_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructIstreamConstructorTables();
		static FoamFvMesh_EXPORT void destroyIstreamConstructorTables();

		template <class blockType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<block> New(const dictionary& dict, const label index, const pointField& vertices,
			                          const blockEdgeList& edges, const blockFaceList& faces, Istream& is)
			{
				return autoPtr<block>(new blockType(dict, index, vertices, edges, faces, is));
			}

			addIstreamConstructorToTable(const word& lookup = blockType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "block" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class blockType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<block> New(const dictionary& dict, const label index, const pointField& vertices,
			                          const blockEdgeList& edges, const blockFaceList& faces, Istream& is)
			{
				return autoPtr<block>(new blockType(dict, index, vertices, edges, faces, is));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = blockType::typeName) : lookup_(lookup)
			{
				constructIstreamConstructorTables();
				IstreamConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableIstreamConstructorToTable()
			{
				if (IstreamConstructorTablePtr_) { IstreamConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components with Istream
		FoamFvMesh_EXPORT block
		(
			const dictionary& dict,
			const label index,
			const pointField& vertices,
			const blockEdgeList& edges,
			const blockFaceList& faces,
			Istream& is
		);

		//- Construct from a block definition
		FoamFvMesh_EXPORT block(const blockDescriptor&);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT block(const block&) = delete;

		//- Clone
		autoPtr<block> clone() const
		{
			NotImplemented;
			return autoPtr<block>(nullptr);
		}

		//- New function which constructs and returns pointer to a block
		static FoamFvMesh_EXPORT autoPtr<block> New
		(
			const dictionary& dict,
			const label index,
			const pointField& points,
			const blockEdgeList& edges,
			const blockFaceList& faces,
			Istream&
		);

		//- Class used for the read-construction of
		//  PtrLists of blocks
		class iNew
		{
			const dictionary& dict_;
			const pointField& points_;
			const blockEdgeList& edges_;
			const blockFaceList& faces_;
			mutable label index_;

		public:

			iNew
			(
				const dictionary& dict,
				const pointField& points,
				const blockEdgeList& edges,
				const blockFaceList& faces
			)
				:
				dict_(dict),
				points_(points),
				edges_(edges),
				faces_(faces),
				index_(0)
			{}

			autoPtr<block> operator()(Istream& is) const
			{
				return block::New(dict_, index_++, points_, edges_, faces_, is);
			}
		};


		//- Destructor
		virtual ~block()
		{}


		// Member Functions

			// Access

				//- Return the points for filling the block
		inline const pointField& points() const;

		//- Return the cells for filling the block
		FoamFvMesh_EXPORT List<FixedList<label, 8>> cells() const;

		//- Return the boundary patch faces for the block
		inline const FixedList<List<FixedList<label, 4>>, 6>&
			boundaryPatches() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const block&) = delete;


		// Ostream Operator

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const block&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <blockI.hxx>

#endif // !_block_Header
