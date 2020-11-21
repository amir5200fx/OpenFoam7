#pragma once
#ifndef _pointZone_Header
#define _pointZone_Header

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
	tnbLib::pointZone

Description
	A subset of mesh points.
	The labels of points in the zone can be obtained from the addressing()
	list.

	For quick check whether a point belongs to the zone use the lookup
	mechanism in pointZoneMesh, where all the zoned points are registered
	with their zone number.

SourceFiles
	pointZone.C
	pointZoneNew.C

\*---------------------------------------------------------------------------*/

#include <zone.hxx>
#include <pointZoneMeshFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class pointZone;
	Ostream& operator<<(Ostream&, const pointZone&);


	/*---------------------------------------------------------------------------*\
							  Class pointZone Declaration
	\*---------------------------------------------------------------------------*/

	class pointZone
		:
		public zone
	{

	protected:

		// Protected data

			//- Reference to zone list
		const pointZoneMesh& zoneMesh_;


	public:

		// Static Data Members

			//- The name associated with the zone-labels dictionary entry
		static FoamBase_EXPORT const char * const labelsName;


		//- Runtime type information
		//TypeName("pointZone");
		static const char* typeName_() { return "pointZone"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			pointZone,
			dictionary,
			(
				const word& name,
				const dictionary& dict,
				const label index,
				const pointZoneMesh& zm
				),
				(name, dict, index, zm)
		);*/

		typedef autoPtr<pointZone> (*dictionaryConstructorPtr)(const word& name, const dictionary& dict, const label index,
		                                                       const pointZoneMesh& zm);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamBase_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamBase_EXPORT void constructdictionaryConstructorTables();
		static FoamBase_EXPORT void destroydictionaryConstructorTables();

		template <class pointZoneType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<pointZone> New(const word& name, const dictionary& dict, const label index, const pointZoneMesh& zm)
			{
				return autoPtr<pointZone>(new pointZoneType(name, dict, index, zm));
			}

			adddictionaryConstructorToTable(const word& lookup = pointZoneType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "pointZone" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class pointZoneType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<pointZone> New(const word& name, const dictionary& dict, const label index, const pointZoneMesh& zm)
			{
				return autoPtr<pointZone>(new pointZoneType(name, dict, index, zm));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = pointZoneType::typeName) : lookup_(lookup)
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
		FoamBase_EXPORT pointZone
		(
			const word& name,
			const labelUList& addr,
			const label index,
			const pointZoneMesh&
		);

		//- Construct from components, transferring contents
		FoamBase_EXPORT pointZone
		(
			const word& name,
			labelList&& addr,
			const label index,
			const pointZoneMesh&
		);

		//- Construct from dictionary
		FoamBase_EXPORT pointZone
		(
			const word& name,
			const dictionary&,
			const label index,
			const pointZoneMesh&
		);

		//- Construct given the original zone and resetting the
		//  point list and zone mesh information
		FoamBase_EXPORT pointZone
		(
			const pointZone&,
			const labelUList& addr,
			const label index,
			const pointZoneMesh&
		);

		//- Construct given the original zone, resetting the
		//  face list and zone mesh information
		FoamBase_EXPORT pointZone
		(
			const pointZone&,
			labelList&& addr,
			const label index,
			const pointZoneMesh&
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT pointZone(const pointZone&) = delete;


		//- Construct and return a clone, resetting the zone mesh
		virtual autoPtr<pointZone> clone(const pointZoneMesh& zm) const
		{
			return autoPtr<pointZone>
				(
					new pointZone(*this, *this, index(), zm)
					);
		}

		//- Construct and return a clone, resetting the point list
		//  and zone mesh
		virtual autoPtr<pointZone> clone
		(
			const pointZoneMesh& zm,
			const label index,
			const labelUList& addr
		) const
		{
			return autoPtr<pointZone>
				(
					new pointZone(*this, addr, index, zm)
					);
		}


		// Selectors

			//- Return a pointer to a new point zone
			//  created on freestore from dictionary
		static FoamBase_EXPORT autoPtr<pointZone> New
		(
			const word& name,
			const dictionary&,
			const label index,
			const pointZoneMesh&
		);


		//- Destructor
		FoamBase_EXPORT virtual ~pointZone();


		// Member Functions

			//- Return zoneMesh reference
		FoamBase_EXPORT const pointZoneMesh& zoneMesh() const;

		//- Helper function to re-direct to zone::localID(...)
		FoamBase_EXPORT label whichPoint(const label globalPointID) const;

		//- Check zone definition. Return true if in error.
		FoamBase_EXPORT virtual bool checkDefinition(const bool report = false) const;

		//- Check whether zone is synchronised across coupled boundaries. Return
		//  true if in error.
		FoamBase_EXPORT virtual bool checkParallelSync(const bool report = false) const;

		//- Correct patch after moving points
		virtual void movePoints(const pointField&)
		{}

		//- Write dictionary
		FoamBase_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Assignment to zone, clearing demand-driven data
		FoamBase_EXPORT void operator=(const pointZone&);

		//- Move assignment to zone, clearing demand-driven data
		FoamBase_EXPORT void operator=(pointZone&&);

		//- Assign addressing, clearing demand-driven data
		FoamBase_EXPORT void operator=(const labelUList&);

		//- Move addressing, clearing demand-driven data
		FoamBase_EXPORT void operator=(labelList&&);


		// I-O

			//- Ostream Operator
		friend Ostream& operator<<(Ostream&, const pointZone&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointZone_Header
