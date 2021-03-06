#pragma once
#ifndef _coupleGroupIdentifier_Header
#define _coupleGroupIdentifier_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::coupleGroupIdentifier

Description
	Encapsulates using patchGroups to specify coupled patch

SourceFiles
	coupleGroupIdentifierI.H
	coupleGroupIdentifier.C
	coupleGroupIdentifierIO.C

\*---------------------------------------------------------------------------*/

#include <word.hxx>
#include <label.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class dictionary;
	class polyMesh;
	class polyPatch;
	class Ostream;

	// Forward declaration of friend functions and operators
	class coupleGroupIdentifier;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const coupleGroupIdentifier&);


	/*---------------------------------------------------------------------------*\
							 Class coupleGroupIdentifier Declaration
	\*---------------------------------------------------------------------------*/

	class coupleGroupIdentifier
	{
		// Private Data

			//- Name of patchGroup
		word name_;


		// Private Member Functions

			//- Find other patch in specified mesh. Returns index of patch or -1.
		FoamBase_EXPORT label findOtherPatchID(const polyMesh&, const polyPatch&) const;


	public:

		// Constructors

			//- Construct null
		FoamBase_EXPORT coupleGroupIdentifier();

		//- Construct from components
		FoamBase_EXPORT coupleGroupIdentifier(const word& patchGroupName);

		//- Construct from dictionary
		FoamBase_EXPORT coupleGroupIdentifier(const dictionary&);


		// Member Functions

			//- Name of patchGroup
		inline const word& name() const;

		//- Is a valid patchGroup
		inline bool valid() const;

		//- Find other patch in same region. Returns index of patch or -1.
		FoamBase_EXPORT label findOtherPatchID(const polyPatch&) const;

		//- Find other patch and region. Returns index of patch and sets
		//  otherRegion to name of region. Fatal error if patch not found
		FoamBase_EXPORT label findOtherPatchID(const polyPatch&, word&) const;

		//- Write the data as a dictionary
		FoamBase_EXPORT void write(Ostream&) const;


		// IOstream Operators

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const coupleGroupIdentifier&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <coupleGroupIdentifierI.hxx>

#endif // !_coupleGroupIdentifier_Header
