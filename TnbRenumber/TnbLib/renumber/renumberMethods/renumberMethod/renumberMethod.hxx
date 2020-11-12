#pragma once
#ifndef _renumberMethod_Header
#define _renumberMethod_Header

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
	tnbLib::renumberMethod

Description
	Abstract base class for renumbering

SourceFiles
	renumberMethod.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <pointField.hxx>
#include <CompactListList.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class renumberMethod Declaration
	\*---------------------------------------------------------------------------*/

	class renumberMethod
	{

	protected:

		// Protected data

		const dictionary& renumberDict_;


	public:

		//- Runtime type information
		//TypeName("renumberMethod");
		static const char* typeName_() { return "renumberMethod"; }
		static FoamRenumber_EXPORT const ::tnbLib::word typeName;
		static FoamRenumber_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			renumberMethod,
			dictionary,
			(
				const dictionary& renumberDict
				),
				(renumberDict)
		);*/

		typedef autoPtr<renumberMethod> (*dictionaryConstructorPtr)(const dictionary& renumberDict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamRenumber_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamRenumber_EXPORT void constructdictionaryConstructorTables();
		static FoamRenumber_EXPORT void destroydictionaryConstructorTables();

		template <class renumberMethodType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<renumberMethod> New(const dictionary& renumberDict)
			{
				return autoPtr<renumberMethod>(new renumberMethodType(renumberDict));
			}

			adddictionaryConstructorToTable(const word& lookup = renumberMethodType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "renumberMethod" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class renumberMethodType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<renumberMethod> New(const dictionary& renumberDict)
			{
				return autoPtr<renumberMethod>(new renumberMethodType(renumberDict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = renumberMethodType::typeName) : lookup_(
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

			//- Construct given the renumber dictionary
		renumberMethod(const dictionary& renumberDict)
			:
			renumberDict_(renumberDict)
		{}

		//- Disallow default bitwise copy construction
		FoamRenumber_EXPORT renumberMethod(const renumberMethod&) = delete;


		// Selectors

			//- Return a reference to the selected renumbering method
		static FoamRenumber_EXPORT autoPtr<renumberMethod> New
		(
			const dictionary& renumberDict
		);


		//- Destructor
		virtual ~renumberMethod()
		{}


		// Member Functions

			//- Return the order in which cells need to be visited, i.e.
			//  from ordered back to original cell label.
			//  This is only defined for geometric renumberMethods.
		virtual labelList renumber(const pointField&) const
		{
			NotImplemented;
			return labelList(0);
		}

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  Use the mesh connectivity (if needed)
		FoamRenumber_EXPORT virtual labelList renumber(const polyMesh&, const pointField&) const;

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  Addressing in losort addressing (= neighbour + offsets into
		//  neighbour)
		FoamRenumber_EXPORT virtual labelList renumber
		(
			const labelList& cellCells,
			const labelList& offsets,
			const pointField&
		) const;

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  Gets passed agglomeration map (from fine to coarse cells) and coarse
		//  cell
		//  location. Can be overridden by renumberMethods that provide this
		//  functionality natively. Coarse cells are local to the processor
		//  (if in parallel). If you want to have coarse cells spanning
		//  processors use the globalCellCells instead.
		FoamRenumber_EXPORT virtual labelList renumber
		(
			const polyMesh& mesh,
			const labelList& cellToRegion,
			const pointField& regionPoints
		) const;

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  The connectivity is equal to mesh.cellCells() except
		//  - the connections are across coupled patches
		FoamRenumber_EXPORT virtual labelList renumber
		(
			const labelListList& cellCells,
			const pointField& cc
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamRenumber_EXPORT void operator=(const renumberMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_renumberMethod_Header
