#pragma once
#ifndef _cellZone_Header
#define _cellZone_Header

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
	tnbLib::cellZone

Description
	A subset of mesh cells.

	Currently set up as an indirect list but will be extended to use a
	primitive mesh.  For quick check whether a cell belongs to the zone use
	the lookup mechanism in cellZoneMesh, where all the zoned cells are
	registered with their zone number.

SourceFiles
	cellZone.C
	cellZoneNew.C

\*---------------------------------------------------------------------------*/

#include <zone.hxx>
#include <cellZoneMeshFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class cellZone;
	Ostream& operator<<(Ostream&, const cellZone&);


	/*---------------------------------------------------------------------------*\
							   Class cellZone Declaration
	\*---------------------------------------------------------------------------*/

	class cellZone
		:
		public zone
	{

	protected:

		// Protected data

			//- Reference to zone list
		const cellZoneMesh& zoneMesh_;


	public:

		// Static Data Members

			//- The name associated with the zone-labels dictionary entry
		static FoamBase_EXPORT const char * const labelsName;


		//- Runtime type information
		//TypeName("cellZone");
		static const char* typeName_() { return "cellZone"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			cellZone,
			dictionary,
			(
				const word& name,
				const dictionary& dict,
				const label index,
				const cellZoneMesh& zm
				),
				(name, dict, index, zm)
		);*/

		typedef autoPtr<cellZone> (*dictionaryConstructorPtr)(const word& name, const dictionary& dict, const label index,
		                                                      const cellZoneMesh& zm);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamBase_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamBase_EXPORT void constructdictionaryConstructorTables();
		static FoamBase_EXPORT void destroydictionaryConstructorTables();

		template <class cellZoneType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<cellZone> New(const word& name, const dictionary& dict, const label index, const cellZoneMesh& zm)
			{
				return autoPtr<cellZone>(new cellZoneType(name, dict, index, zm));
			}

			adddictionaryConstructorToTable(const word& lookup = cellZoneType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "cellZone" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class cellZoneType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<cellZone> New(const word& name, const dictionary& dict, const label index, const cellZoneMesh& zm)
			{
				return autoPtr<cellZone>(new cellZoneType(name, dict, index, zm));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = cellZoneType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components
		FoamBase_EXPORT cellZone
		(
			const word& name,
			const labelUList& addr,
			const label index,
			const cellZoneMesh&
		);

		//- Construct from components, transferring contents
		FoamBase_EXPORT cellZone
		(
			const word& name,
			labelList&& addr,
			const label index,
			const cellZoneMesh&
		);

		//- Construct from dictionary
		FoamBase_EXPORT cellZone
		(
			const word& name,
			const dictionary&,
			const label index,
			const cellZoneMesh&
		);

		//- Construct given the original zone and resetting the
		//  cell list and zone mesh information
		FoamBase_EXPORT cellZone
		(
			const cellZone&,
			const labelUList& addr,
			const label index,
			const cellZoneMesh&
		);

		//- Construct given the original zone, resetting the
		//  cell list and zone mesh information
		FoamBase_EXPORT cellZone
		(
			const cellZone&,
			labelList&& addr,
			const label index,
			const cellZoneMesh&
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT cellZone(const cellZone&) = delete;


		//- Construct and return a clone, resetting the zone mesh
		virtual autoPtr<cellZone> clone(const cellZoneMesh& zm) const
		{
			return autoPtr<cellZone>
				(
					new cellZone(*this, *this, index(), zm)
					);
		}

		//- Construct and return a clone, resetting the cell list
		//  and zone mesh
		virtual autoPtr<cellZone> clone
		(
			const labelUList& addr,
			const label index,
			const cellZoneMesh& zm
		) const
		{
			return autoPtr<cellZone>
				(
					new cellZone(*this, addr, index, zm)
					);
		}


		// Selectors

			//- Return a pointer to a new cell zone
			//  created on freestore from dictionary
		static FoamBase_EXPORT autoPtr<cellZone> New
		(
			const word& name,
			const dictionary&,
			const label index,
			const cellZoneMesh&
		);


		//- Destructor
		FoamBase_EXPORT virtual ~cellZone();


		// Member Functions

			//- Helper function to re-direct to zone::localID(...)
		FoamBase_EXPORT label whichCell(const label globalCellID) const;

		//- Return zoneMesh reference
		FoamBase_EXPORT const cellZoneMesh& zoneMesh() const;

		//- Check zone definition. Return true if in error.
		FoamBase_EXPORT virtual bool checkDefinition(const bool report = false) const;

		//- Check whether zone is synchronised across coupled boundaries. Return
		//  true if in error.
		virtual bool checkParallelSync(const bool report = false) const
		{
			return false;
		}

		//- Write dictionary
		FoamBase_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Assignment to zone, clearing demand-driven data
		FoamBase_EXPORT void operator=(const cellZone&);

		//- Move assignment to zone, clearing demand-driven data
		FoamBase_EXPORT void operator=(cellZone&&);

		//- Assign addressing, clearing demand-driven data
		FoamBase_EXPORT void operator=(const labelUList&);

		//- Move addressing, clearing demand-driven data
		FoamBase_EXPORT void operator=(labelList&&);


		// I-O

			//- Ostream Operator
		friend Ostream& operator<<(Ostream&, const cellZone&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellZone_Header
