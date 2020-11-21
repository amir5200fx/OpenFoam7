#pragma once
#ifndef _zone_Header
#define _zone_Header

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
	tnbLib::zone

Description
	Base class for zones

SourceFiles
	zone.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <typeInfo.hxx>
#include <dictionary.hxx>
#include <Map.hxx>
#include <pointFieldFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class zone;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const zone&);

	/*---------------------------------------------------------------------------*\
							   Class zone Declaration
	\*---------------------------------------------------------------------------*/

	class zone
		:
		public labelList
	{

	protected:

		// Protected data

			//- Name of zone
		word name_;

		//- Index of zone
		label index_;


		// Demand-driven private data

			//- Map of labels in zone for fast location lookup
		mutable Map<label>* lookupMapPtr_;


		// Protected Member Functions

			//- Construct the look-up map
		void calcLookupMap() const;


	public:

		//- Runtime type information
		//TypeName("zone");
		static const char* typeName_() { return "zone"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT zone
		(
			const word& name,
			const labelUList& addr,
			const label index
		);

		//- Construct from components, moving contents
		FoamBase_EXPORT zone
		(
			const word& name,
			labelList&& addr,
			const label index
		);

		//- Construct from dictionary
		FoamBase_EXPORT zone
		(
			const word& name,
			const dictionary&,
			const word& labelsName,
			const label index
		);

		//- Construct given the original zone and resetting the
		//  cell list and zone mesh information
		FoamBase_EXPORT zone
		(
			const zone&,
			const labelUList& addr,
			const label index
		);

		//- Construct given the original zone, resetting the
		//  cell list and zone mesh information
		FoamBase_EXPORT zone
		(
			const zone&,
			labelList&& addr,
			const label index
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT zone(const zone&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~zone();


		// Member Functions

			//- Return name
		const word& name() const
		{
			return name_;
		}

		//- Map storing the local index for every global index.  Used to find
		//  the index of the item in the zone from the known global index. If
		//  the item is not in the zone, returns -1
		FoamBase_EXPORT label localID(const label globalID) const;

		//- Return the index of this zone in zone list
		label index() const
		{
			return index_;
		}

		//- Return a reference to the look-up map
		FoamBase_EXPORT const Map<label>& lookupMap() const;

		//- Clear addressing
		FoamBase_EXPORT virtual void clearAddressing();

		//- Check zone definition. Return true if in error.
		FoamBase_EXPORT virtual bool checkDefinition(const bool report = false) const = 0;

		//- Check zone definition with max size given. Return true if in error.
		FoamBase_EXPORT virtual bool checkDefinition
		(
			const label maxSize,
			const bool report = false
		) const;

		//- Correct patch after moving points
		virtual void movePoints(const pointField&)
		{}

		//- Write
		FoamBase_EXPORT virtual void write(Ostream&) const;

		//- Write dictionary
		FoamBase_EXPORT virtual void writeDict(Ostream&) const = 0;


		// Member Operators

			//- Assignment operator
		FoamBase_EXPORT void operator=(const zone&);

		//- Move assignment operator
		FoamBase_EXPORT void operator=(zone&&);

		//- Assignment operator to addressing
		FoamBase_EXPORT void operator=(const labelUList&);

		//- Move assignment of addressing
		FoamBase_EXPORT void operator=(labelList&&);


		// I-O

			//- Ostream Operator
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const zone&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zone_Header
