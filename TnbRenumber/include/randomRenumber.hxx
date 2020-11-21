#pragma once
#ifndef _randomRenumber_Header
#define _randomRenumber_Header

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
	tnbLib::randomRenumber

Description
	Random renumber. Just to see effect of renumbering.

SourceFiles
	randomRenumber.C

\*---------------------------------------------------------------------------*/

#include <renumberMethod.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class randomRenumber Declaration
	\*---------------------------------------------------------------------------*/

	class randomRenumber
		:
		public renumberMethod
	{
	public:

		//- Runtime type information
		//TypeName("random");
		static const char* typeName_() { return "random"; }
		static FoamRenumber_EXPORT const ::tnbLib::word typeName;
		static FoamRenumber_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the renumber dictionary
		FoamRenumber_EXPORT randomRenumber(const dictionary& renumberDict);

		//- Disallow default bitwise copy construction
		FoamRenumber_EXPORT randomRenumber(const randomRenumber&) = delete;


		//- Destructor
		virtual ~randomRenumber()
		{}


		// Member Functions

			//- Return the order in which cells need to be visited, i.e.
			//  from ordered back to original cell label.
			//  This is only defined for geometric renumberMethods.
		FoamRenumber_EXPORT virtual labelList renumber(const pointField&) const;

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  Use the mesh connectivity (if needed)
		FoamRenumber_EXPORT virtual labelList renumber
		(
			const polyMesh& mesh,
			const pointField& cc
		) const;

		//- Return the order in which cells need to be visited, i.e.
		//  from ordered back to original cell label.
		//  The connectivity is equal to mesh.cellCells() except
		//  - the connections are across coupled patches
		FoamRenumber_EXPORT virtual labelList renumber
		(
			const labelListList& cellCells,
			const pointField& cc
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamRenumber_EXPORT void operator=(const randomRenumber&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_randomRenumber_Header
