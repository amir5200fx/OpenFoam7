#pragma once
#ifndef _boundaryRegion_Header
#define _boundaryRegion_Header

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
	tnbLib::boundaryRegion

Description
	The boundaryRegion persistent data saved as a Map<dictionary>.

	The meshReader supports boundaryRegion information.

	The <tt>constant/boundaryRegion</tt> file is an \c IOMap<dictionary>
	that is used to save the information persistently.
	It contains the boundaryRegion information of the following form:

	\verbatim
		(
			INT
			{
				BoundaryType    WORD;
				Label           WORD;
			}
			...
		)
	\endverbatim

SourceFiles
	boundaryRegion.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <Map.hxx>
#include <dictionary.hxx>
#include <labelList.hxx>
#include <wordList.hxx>
#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class boundaryRegion Declaration
	\*---------------------------------------------------------------------------*/

	class boundaryRegion
		:
		public Map<dictionary>
	{
	public:

		// Constructors

			//- Construct null
		FoamConversion_EXPORT boundaryRegion();

		//- Construct read from registry, name. instance
		FoamConversion_EXPORT boundaryRegion
		(
			const objectRegistry&,
			const word& name = "boundaryRegion",
			const fileName& instance = "constant"
		);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT boundaryRegion(const boundaryRegion&) = delete;


		//- Destructor
		FoamConversion_EXPORT ~boundaryRegion();


		// Member Functions

			//- Append to the end, return index
		FoamConversion_EXPORT label append(const dictionary&);

		//- Return index corresponding to patch 'name'
		//  returns -1 if not found
		FoamConversion_EXPORT label findIndex(const word& name) const;

		//- Return a Map of (id => name)
		FoamConversion_EXPORT Map<word> names() const;

		//- Return a Map of (id => names) selected by patterns
		FoamConversion_EXPORT Map<word> names(const UList<wordRe>& patterns) const;

		//- Return a Map of (id => type)
		FoamConversion_EXPORT Map<word> boundaryTypes() const;

		//- Return BoundaryType corresponding to patch 'name'
		FoamConversion_EXPORT word boundaryType(const word& name) const;

		//- Read constant/boundaryRegion
		FoamConversion_EXPORT void readDict
		(
			const objectRegistry&,
			const word& name = "boundaryRegion",
			const fileName& instance = "constant"
		);

		//- Write constant/boundaryRegion for later reuse
		FoamConversion_EXPORT void writeDict
		(
			const objectRegistry&,
			const word& name = "boundaryRegion",
			const fileName& instance = "constant"
		) const;


		// Member Operators

			//- Assignment
		FoamConversion_EXPORT void operator=(const boundaryRegion&);

		//- Assign from Map<dictionary>
		FoamConversion_EXPORT void operator=(const Map<dictionary>&);


		// Friend Functions

			//- Rename regions
			//  each dictionary entry is a single word:
			//  \verbatim
			//      newPatchName    originalName;
			//  \endverbatim
		FoamConversion_EXPORT void rename(const dictionary&);
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundaryRegion_Header
