#pragma once
#ifndef _cellTable_Header
#define _cellTable_Header

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
	tnbLib::cellTable

Description
	The cellTable persistent data saved as a Map<dictionary>.

	The meshReader supports cellTable information.

	The <tt>constant/cellTable</tt> file is an \c IOMap<dictionary> that is
	used to save the information persistently. It contains the cellTable
	information of the following form:

	\verbatim
		(
			ID
			{
				Label           WORD;
				MaterialType    WORD;
				MaterialId      INT;
				PorosityId      INT;
				ColorIdx        INT;
				...
			}
		...
		)
	\endverbatim

	If the \a Label is missing, a value <tt>cellTable_{ID}</tt> will be
	inferred. If the \a MaterialType is missing, the value @a fluid will
	be inferred.

SourceFiles
	cellTable.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <Map.hxx>
#include <dictionary.hxx>
#include <labelList.hxx>
#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class cellTable Declaration
	\*---------------------------------------------------------------------------*/

	class cellTable
		:
		public Map<dictionary>
	{
		// Private Data

		static FoamConversion_EXPORT const char* const defaultMaterial_;


		// Private Member Functions

			//- Map from cellTable ID => zone number
		FoamConversion_EXPORT Map<label> zoneMap() const;

		//- A contiguous list of cellTable names
		FoamConversion_EXPORT List<word> namesList() const;

		//- Add required entries - MaterialType
		FoamConversion_EXPORT void addDefaults();

		FoamConversion_EXPORT void setEntry(const label id, const word& keyWord, const word& value);


	public:

		// Constructors

			//- Construct null
		FoamConversion_EXPORT cellTable();

		//- Construct read from registry, name. instance
		FoamConversion_EXPORT cellTable
		(
			const objectRegistry&,
			const word& name = "cellTable",
			const fileName& instance = "constant"
		);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT cellTable(const cellTable&) = delete;


		//- Destructor
		FoamConversion_EXPORT ~cellTable();


		// Member Functions

			//- Append to the end, return index
		FoamConversion_EXPORT label append(const dictionary&);

		//- Return index corresponding to name
		//  returns -1 if not found
		FoamConversion_EXPORT label findIndex(const word& name) const;

		//- Return the name corresponding to id
		//  returns cellTable_ID if not otherwise defined
		FoamConversion_EXPORT word name(const label id) const;

		//- Return a Map of (id => name)
		FoamConversion_EXPORT Map<word> names() const;

		//- Return a Map of (id => names) selected by patterns
		FoamConversion_EXPORT Map<word> names(const UList<wordRe>& patterns) const;

		//- Return a Map of (id => name) for materialType
		//  (fluid | solid | shell)
		FoamConversion_EXPORT Map<word> selectType(const word& materialType) const;

		//- Return a Map of (id => name) for fluids
		FoamConversion_EXPORT Map<word> fluids() const;

		//- Return a Map of (id => name) for shells
		FoamConversion_EXPORT Map<word> shells() const;

		//- Return a Map of (id => name) for solids
		FoamConversion_EXPORT Map<word> solids() const;

		//- Return a Map of (id => fluid|solid|shell)
		FoamConversion_EXPORT Map<word> materialTypes() const;

		//- Assign material Type
		FoamConversion_EXPORT void setMaterial(const label, const word&);

		//- Assign name
		FoamConversion_EXPORT void setName(const label, const word&);

		//- Assign default name if not already set
		FoamConversion_EXPORT void setName(const label);

		//- Read constant/cellTable
		FoamConversion_EXPORT void readDict
		(
			const objectRegistry&,
			const word& name = "cellTable",
			const fileName& instance = "constant"
		);

		//- Write constant/cellTable for later reuse
		FoamConversion_EXPORT void writeDict
		(
			const objectRegistry&,
			const word& name = "cellTable",
			const fileName& instance = "constant"
		) const;


		// Member Operators

			//- Assignment
		FoamConversion_EXPORT void operator=(const cellTable&);

		//- Assign from Map<dictionary>
		FoamConversion_EXPORT void operator=(const Map<dictionary>&);

		//- Assign from cellZones
		FoamConversion_EXPORT void operator=(const polyMesh&);


		// Friend Functions

			//- Classify tableIds into cellZones according to the cellTable
		FoamConversion_EXPORT void addCellZones(polyMesh&, const labelList& tableIds) const;

		//- Combine tableIds together
		//  each dictionary entry is a wordList
		FoamConversion_EXPORT void combine(const dictionary&, labelList& tableIds);
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellTable_Header
