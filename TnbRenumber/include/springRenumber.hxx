#pragma once
#ifndef _springRenumber_Header
#define _springRenumber_Header

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
	tnbLib::springRenumber

Description
	Use spring analogy - attract neighbouring cells according to the distance
	of their cell indices.

	// Maximum jump of cell indices. Is fraction of number of cells
	maxCo 0.1;

	// Limit the amount of movement; the fraction maxCo gets decreased
	// with every iteration.
	freezeFraction 0.9;

	// Maximum number of iterations
	maxIter 1000;

SourceFiles
	springRenumber.C

\*---------------------------------------------------------------------------*/

#include <renumberMethod.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class springRenumber Declaration
	\*---------------------------------------------------------------------------*/

	class springRenumber
		:
		public renumberMethod
	{
		// Private Data

		const dictionary& dict_;

		const scalar maxCo_;

		const label maxIter_;

		const scalar freezeFraction_;


	public:

		//- Runtime type information
		//TypeName("spring");
		static const char* typeName_() { return "spring"; }
		static FoamRenumber_EXPORT const ::tnbLib::word typeName;
		static FoamRenumber_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the renumber dictionary
		FoamRenumber_EXPORT springRenumber(const dictionary& renumberDict);

		//- Disallow default bitwise copy construction
		FoamRenumber_EXPORT springRenumber(const springRenumber&) = delete;


		//- Destructor
		virtual ~springRenumber()
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
		FoamRenumber_EXPORT void operator=(const springRenumber&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_springRenumber_Header
