#pragma once
#ifndef _multiLevelDecomp_Header
#define _multiLevelDecomp_Header

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
	tnbLib::multiLevelDecomp

Description
	Decomposition given using consecutive application of decomposers.

SourceFiles
	multiLevelDecomp.C

\*---------------------------------------------------------------------------*/

#include <decompositionMethod.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class multiLevelDecomp Declaration
	\*---------------------------------------------------------------------------*/

	class multiLevelDecomp
		:
		public decompositionMethod
	{
		// Private Data

		dictionary methodsDict_;

		PtrList<decompositionMethod> methods_;


		// Private Member Functions

			//- Given connectivity across processors work out connectivity
			//  for a (consistent) subset
		FoamParallel_EXPORT void subsetGlobalCellCells
		(
			const label nDomains,
			const label domainI,
			const labelList& dist,

			const labelListList& cellCells,
			const labelList& set,
			labelListList& subCellCells,
			labelList& cutConnections
		) const;

		//- Decompose level methodI without addressing
		FoamParallel_EXPORT void decompose
		(
			const labelListList& pointPoints,
			const pointField& points,
			const scalarField& pointWeights,
			const labelList& pointMap,  // map back to original points
			const label levelI,

			labelField& finalDecomp
		);


	public:

		//- Runtime type information
		//TypeName("multiLevel");
		static const char* typeName_() { return "multiLevel"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the decomposition dictionary
		FoamParallel_EXPORT multiLevelDecomp(const dictionary& decompositionDict);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT multiLevelDecomp(const multiLevelDecomp&) = delete;


		//- Destructor
		virtual ~multiLevelDecomp()
		{}


		// Member Functions

			//- Is method parallel aware (i.e. does it synchronize domains across
			//  proc boundaries)
		FoamParallel_EXPORT virtual bool parallelAware() const;

		//- Inherit decompose from decompositionMethod
		using decompositionMethod::decompose;

		//- Return for every coordinate the wanted processor number. Use the
		//  mesh connectivity (if needed)
		FoamParallel_EXPORT virtual labelList decompose
		(
			const polyMesh& mesh,
			const pointField& points,
			const scalarField& pointWeights
		);

		//- Return for every coordinate the wanted processor number. Explicitly
		//  provided connectivity - does not use mesh_.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const labelListList& globalCellCells,
			const pointField& cc,
			const scalarField& cWeights
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const multiLevelDecomp&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_multiLevelDecomp_Header
