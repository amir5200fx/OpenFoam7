#pragma once
#ifndef _metisDecomp_Header
#define _metisDecomp_Header

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
	tnbLib::metisDecomp

Description
	Metis domain decomposition

SourceFiles
	metisDecomp.C

\*---------------------------------------------------------------------------*/

#include <decompositionMethod.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class metisDecomp Declaration
	\*---------------------------------------------------------------------------*/

	class metisDecomp
		:
		public decompositionMethod
	{

		// Private Member Functions

			//- Call Metis with options from dictionary.
		FoamParallel_EXPORT label decompose
		(
			const List<label>& adjncy,
			const List<label>& xadj,
			const scalarField& cellWeights,
			List<label>& finalDecomp
		);


	public:

		//- Runtime type information
		//TypeName("metis");
		static const char* typeName_() { return "metis"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the decomposition dictionary
		FoamParallel_EXPORT metisDecomp(const dictionary&);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT metisDecomp(const metisDecomp&) = delete;


		//- Destructor
		virtual ~metisDecomp()
		{}


		// Member Functions

		virtual bool parallelAware() const
		{
			// Metis does not know about proc boundaries
			return false;
		}

		//- Inherit decompose from decompositionMethod
		using decompositionMethod::decompose;

		//- Return for every coordinate the wanted processor number. Use the
		//  mesh connectivity (if needed)
		//  Weights get normalised so the minimum value is 1 before truncation
		//  to an integer so the weights should be multiples of the minimum
		//  value. The overall sum of weights might otherwise overflow.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const pointField& points,
			const scalarField& pointWeights
		);

		//- Return for every coordinate the wanted processor number. Gets
		//  passed agglomeration map (from fine to coarse cells) and coarse cell
		//  location. Can be overridden by decomposers that provide this
		//  functionality natively.
		//  See note on weights above.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const labelList& agglom,
			const pointField& regionPoints,
			const scalarField& regionWeights
		);

		//- Return for every coordinate the wanted processor number. Explicitly
		//  provided mesh connectivity.
		//  The connectivity is equal to mesh.cellCells() except for
		//  - in parallel the cell numbers are global cell numbers (starting
		//    from 0 at processor0 and then incrementing all through the
		//    processors)
		//  - the connections are across coupled patches
		//  See note on weights above.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const labelListList& globalCellCells,
			const pointField& cc,
			const scalarField& cWeights
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const metisDecomp&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_metisDecomp_Header
