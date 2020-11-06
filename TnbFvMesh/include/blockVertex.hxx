#pragma once
#ifndef _blockVertex_Header
#define _blockVertex_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::blockVertex

Description
	Define a block vertex.

SourceFiles
	blockVertex.C

\*---------------------------------------------------------------------------*/

#include <searchableSurfaces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class blockVertex Declaration
	\*---------------------------------------------------------------------------*/

	class blockVertex
	{

	public:

		//- Runtime type information
		//TypeName("blockVertex");
		static const char* typeName_() { return "blockVertex"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			blockVertex,
			Istream,
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				Istream& is
				),
				(dict, index, geometry, is)
		);*/

		typedef autoPtr<blockVertex> (*IstreamConstructorPtr)(const dictionary& dict, const label index,
		                                                      const searchableSurfaces& geometry, Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamFvMesh_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructIstreamConstructorTables();
		static FoamFvMesh_EXPORT void destroyIstreamConstructorTables();

		template <class blockVertexType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<blockVertex> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                                Istream& is)
			{
				return autoPtr<blockVertex>(new blockVertexType(dict, index, geometry, is));
			}

			addIstreamConstructorToTable(const word& lookup = blockVertexType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "blockVertex" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class blockVertexType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<blockVertex> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                                Istream& is)
			{
				return autoPtr<blockVertex>(new blockVertexType(dict, index, geometry, is));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = blockVertexType::typeName) : lookup_(lookup)
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

			//- Construct null
		FoamFvMesh_EXPORT blockVertex();

		//- Clone function
		FoamFvMesh_EXPORT virtual autoPtr<blockVertex> clone() const;

		//- New function which constructs and returns pointer to a blockVertex
		static FoamFvMesh_EXPORT autoPtr<blockVertex> New
		(
			const dictionary& dict,
			const label index,
			const searchableSurfaces& geometry,
			Istream&
		);

		//- Class used for the read-construction of
		//  PtrLists of blockVertex
		class iNew
		{
			const dictionary& dict_;
			const searchableSurfaces& geometry_;
			mutable label index_;

		public:

			iNew(const dictionary& dict, const searchableSurfaces& geometry)
				:
				dict_(dict),
				geometry_(geometry),
				index_(0)
			{}

			autoPtr<blockVertex> operator()(Istream& is) const
			{
				return blockVertex::New(dict_, index_++, geometry_, is);
			}
		};


		//- Destructor
		virtual ~blockVertex()
		{}


		// Member Functions

		FoamFvMesh_EXPORT virtual operator point() const = 0;

		//- Read vertex index with optional name lookup
		static FoamFvMesh_EXPORT label read(Istream&, const dictionary&);

		//- Write vertex index with optional name backsubstitution
		static FoamFvMesh_EXPORT void write(Ostream&, const label, const dictionary&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blockVertex_Header
