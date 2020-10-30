#pragma once
#ifndef _blockEdge_Header
#define _blockEdge_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::blockEdge

Description
	Define a curved edge that is parameterized for 0<lambda<1
	between the start and end point.

SourceFiles
	blockEdge.C

\*---------------------------------------------------------------------------*/

#include <searchableSurfaces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class blockEdge;

	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockEdge&);


	/*---------------------------------------------------------------------------*\
							 Class blockEdge Declaration
	\*---------------------------------------------------------------------------*/

	class blockEdge
	{
	protected:

		// Protected data

		const pointField& points_;

		const label start_;
		const label end_;


		// Protected Member Functions

			//- Return a complete point field by appending the start/end points
			//  to the given list
		static FoamFvMesh_EXPORT pointField appendEndPoints
		(
			const pointField&,
			const label start,
			const label end,
			const pointField& otherKnots
		);


	public:

		//- Runtime type information
		//TypeName("blockEdge");
		static const char* typeName_() { return "blockEdge"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			blockEdge,
			Istream,
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				const pointField& points,
				Istream& is
				),
				(dict, index, geometry, points, is)
		);*/

		typedef autoPtr<blockEdge> (*IstreamConstructorPtr)(const dictionary& dict, const label index,
		                                                    const searchableSurfaces& geometry, const pointField& points,
		                                                    Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamFvMesh_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructIstreamConstructorTables();
		static FoamFvMesh_EXPORT void destroyIstreamConstructorTables();

		template <class blockEdgeType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<blockEdge> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                              const pointField& points, Istream& is)
			{
				return autoPtr<blockEdge>(new blockEdgeType(dict, index, geometry, points, is));
			}

			addIstreamConstructorToTable(const word& lookup = blockEdgeType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "blockEdge" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class blockEdgeType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<blockEdge> New(const dictionary& dict, const label index, const searchableSurfaces& geometry,
			                              const pointField& points, Istream& is)
			{
				return autoPtr<blockEdge>(new blockEdgeType(dict, index, geometry, points, is));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = blockEdgeType::typeName) : lookup_(lookup)
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

			//- Construct from components
		FoamFvMesh_EXPORT blockEdge
		(
			const pointField& points,
			const label start,
			const label end
		);

		//- Construct from Istream setting pointsList
		FoamFvMesh_EXPORT blockEdge
		(
			const dictionary& dict,
			const label index,
			const pointField&,
			Istream&
		);

		//- Clone function
		FoamFvMesh_EXPORT virtual autoPtr<blockEdge> clone() const;

		//- New function which constructs and returns pointer to a blockEdge
		static FoamFvMesh_EXPORT autoPtr<blockEdge> New
		(
			const dictionary& dict,
			const label index,
			const searchableSurfaces& geometry,
			const pointField&,
			Istream&
		);

		//- Class used for the read-construction of
		//  PtrLists of blockEdge
		class iNew
		{
			const dictionary& dict_;
			const searchableSurfaces& geometry_;
			const pointField& points_;
			mutable label index_;

		public:

			iNew
			(
				const dictionary& dict,
				const searchableSurfaces& geometry,
				const pointField& points
			)
				:
				dict_(dict),
				geometry_(geometry),
				points_(points),
				index_(0)
			{}

			autoPtr<blockEdge> operator()(Istream& is) const
			{
				return blockEdge::New(dict_, index_++, geometry_, points_, is);
			}
		};


		//- Destructor
		virtual ~blockEdge()
		{}


		// Member Functions

			//- Return label of start point
		inline label start() const;

		//- Return label of end point
		inline label end() const;

		//- Compare the given start and end points with this curve
		//  Return:
		//  -  0: different
		//  - +1: identical
		//  - -1: same edge, but different orientation
		inline int compare(const blockEdge&) const;

		//- Compare the given start and end points with this curve
		//  Return:
		//  -  0: different
		//  - +1: identical
		//  - -1: same edge, but different orientation
		inline int compare(const edge&) const;

		//- Compare the given start and end points with this curve
		//  Return:
		//  -  0: different
		//  - +1: identical
		//  - -1: same edge, but different orientation
		inline int compare(const label start, const label end) const;

		//- Return the point position corresponding to the curve parameter
		//  0 <= lambda <= 1
		FoamFvMesh_EXPORT virtual point position(const scalar) const = 0;

		//- Return the point positions corresponding to the curve parameters
		//  0 <= lambda <= 1
		FoamFvMesh_EXPORT virtual tmp<pointField> position(const scalarList&) const;

		//- Return the length of the curve
		FoamFvMesh_EXPORT virtual scalar length() const = 0;

		//- Write edge with variable backsubstitution
		FoamFvMesh_EXPORT void write(Ostream&, const dictionary&) const;


		// Ostream operator

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockEdge&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <blockEdgeI.hxx>

#endif // !_blockEdge_Header
