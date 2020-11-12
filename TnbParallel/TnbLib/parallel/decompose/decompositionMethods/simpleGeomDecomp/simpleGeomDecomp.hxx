#pragma once
#ifndef _simpleGeomDecomp_Header
#define _simpleGeomDecomp_Header

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
	tnbLib::simpleGeomDecomp

Description

SourceFiles
	simpleGeomDecomp.C

\*---------------------------------------------------------------------------*/

#include <geomDecomp.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class simpleGeomDecomp Declaration
	\*---------------------------------------------------------------------------*/

	class simpleGeomDecomp
		:
		public geomDecomp
	{
		// Private Member Functions

		FoamParallel_EXPORT void assignToProcessorGroup(labelList&, const label) const;

		FoamParallel_EXPORT void assignToProcessorGroup
		(
			labelList& processorGroup,
			const label nProcGroup,
			const labelList& indices,
			const scalarField& weights,
			const scalar summedWeights
		) const;

		FoamParallel_EXPORT labelList decomposeOneProc(const pointField& points) const;

		FoamParallel_EXPORT labelList decomposeOneProc
		(
			const pointField& points,
			const scalarField& weights
		) const;


	public:

		//- Runtime type information
		//TypeName("simple");
		static const char* typeName_() { return "simple"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given the decomposition dictionary
		FoamParallel_EXPORT simpleGeomDecomp(const dictionary& decompositionDict);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT simpleGeomDecomp(const simpleGeomDecomp&) = delete;


		//- Destructor
		virtual ~simpleGeomDecomp()
		{}


		// Member Functions

		virtual bool parallelAware() const
		{
			// simpleDecomp sends all points to the master which does
			// the decomposition.
			return true;
		}

		FoamParallel_EXPORT virtual labelList decompose(const pointField&);

		FoamParallel_EXPORT virtual labelList decompose(const pointField&, const scalarField&);

		virtual labelList decompose(const polyMesh&, const pointField& points)
		{
			return decompose(points);
		}

		virtual labelList decompose
		(
			const polyMesh&,
			const pointField& points,
			const scalarField& pointWeights
		)
		{
			return decompose(points, pointWeights);
		}

		//- Explicitly provided connectivity
		virtual labelList decompose
		(
			const labelListList& globalCellCells,
			const pointField& cc,
			const scalarField& cWeights
		)
		{
			return decompose(cc, cWeights);
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const simpleGeomDecomp&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_simpleGeomDecomp_Header
