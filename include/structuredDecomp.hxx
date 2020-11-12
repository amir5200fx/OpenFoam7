#pragma once
#ifndef _structuredDecomp_Header
#define _structuredDecomp_Header

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
	tnbLib::structuredDecomp

Description
	Decomposition by walking out decomposition of patch cells mesh.

SourceFiles
	structuredDecomp.C

\*---------------------------------------------------------------------------*/

#include <decompositionMethod.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class structuredDecomp Declaration
	\*---------------------------------------------------------------------------*/

	class structuredDecomp
		:
		public decompositionMethod
	{
		// Private Data

		dictionary methodDict_;

		wordReList patches_;

		autoPtr<decompositionMethod> method_;


	public:

		//- Runtime type information
		//TypeName("structured");
		static const char* typeName_() { return "structured"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the decomposition dictionary
		FoamParallel_EXPORT structuredDecomp(const dictionary& decompositionDict);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT structuredDecomp(const structuredDecomp&) = delete;


		//- Destructor
		virtual ~structuredDecomp()
		{}


		// Member Functions

			//- Is method parallel aware (i.e. does it synchronize domains across
			//  proc boundaries)
		FoamParallel_EXPORT virtual bool parallelAware() const;

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
		FoamParallel_EXPORT void operator=(const structuredDecomp&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_structuredDecomp_Header
