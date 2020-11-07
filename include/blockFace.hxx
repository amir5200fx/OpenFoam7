#pragma once
#ifndef _blockFace_Header
#define _blockFace_Header

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
	tnbLib::blockFace

Description
	Define a curved face.

SourceFiles
	blockFace.C

\*---------------------------------------------------------------------------*/

#include <searchableSurfaces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class blockDescriptor;
	class blockFace;

	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockFace&);

	/*---------------------------------------------------------------------------*\
							 Class blockFace Declaration
	\*---------------------------------------------------------------------------*/

	class blockFace
	{
	protected:

		// Protected data

			//- Block face vertices
		const face vertices_;


	public:

		//- Runtime type information
		//TypeName("blockFace");
		static const char* typeName_() { return "blockFace"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			blockFace,
			Istream,
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				Istream& is
				),
				(dict, index, geometry, is)
		);*/

		typedef autoPtr<blockFace> (*IstreamConstructorPtr)(const dictionary& dict, const label index,
		                                                    const searchableSurfaces& geometry, Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamFvMesh_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructIstreamConstructorTables();
		static FoamFvMesh_EXPORT void destroyIstreamConstructorTables();

		template <class blockFaceType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<blockFace> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                              Istream& is)
			{
				return autoPtr<blockFace>(new blockFaceType(dict, index, geometry, is));
			}

			addIstreamConstructorToTable(const word& lookup = blockFaceType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "blockFace" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class blockFaceType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<blockFace> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                              Istream& is)
			{
				return autoPtr<blockFace>(new blockFaceType(dict, index, geometry, is));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = blockFaceType::typeName) : lookup_(lookup)
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

			//- Construct from face vertices
		FoamFvMesh_EXPORT blockFace(const face& vertices);

		//- Construct from Istream
		FoamFvMesh_EXPORT blockFace
		(
			const dictionary& dict,
			const label index,
			Istream&
		);

		//- Clone function
		FoamFvMesh_EXPORT virtual autoPtr<blockFace> clone() const;

		//- New function which constructs and returns pointer to a blockFace
		static FoamFvMesh_EXPORT autoPtr<blockFace> New
		(
			const dictionary& dict,
			const label index,
			const searchableSurfaces& geometry,
			Istream&
		);

		//- Class used for the read-construction of
		//  PtrLists of blockFace
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

			autoPtr<blockFace> operator()(Istream& is) const
			{
				return blockFace::New(dict_, index_++, geometry_, is);
			}
		};


		//- Destructor
		virtual ~blockFace()
		{}


		// Member Functions

			//- Return block face vertices
		inline const face& vertices() const;

		//- Compare with given blockFace
		inline bool compare(const blockFace&) const;

		//- Compare with the given block and block face
		inline bool compare(const face& vertices) const;

		FoamFvMesh_EXPORT virtual void project
		(
			const blockDescriptor&,
			const label blockFacei,
			pointField& points
		) const = 0;

		//- Write face with variable backsubstitution
		FoamFvMesh_EXPORT void write(Ostream&, const dictionary&) const;


		// Ostream operator

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockFace&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <blockFaceI.hxx>

#endif // !_blockFace_Header
