#pragma once
#ifndef _processorCyclicPointPatch_Header
#define _processorCyclicPointPatch_Header

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
	tnbLib::processorCyclicPointPatch

Description
	Processor patch boundary needs to be such that the ordering of
	points in the patch is the same on both sides.

	Looking at the creation of the faces on both sides of the processor
	patch they need to be identical on both sides with the normals pointing
	in opposite directions.  This is achieved by calling the reverseFace
	function in the decomposition.  It is therefore possible to re-create
	the ordering of patch points on the slave side by reversing all the
	patch faces of the owner.

SourceFiles
	processorCyclicPointPatch.C

\*---------------------------------------------------------------------------*/

#include <processorPointPatch.hxx>
#include <processorCyclicPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class processorCyclicPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class processorCyclicPointPatch
		:
		public processorPointPatch
	{
		// Private Data

		const processorCyclicPolyPatch& procCycPolyPatch_;

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT processorCyclicPointPatch(const processorCyclicPointPatch&);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const processorCyclicPointPatch&);

	public:

		//- Runtime type information
		//TypeName(processorCyclicPolyPatch::typeName_());
		static const char* typeName_() { return processorCyclicPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT processorCyclicPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);


		// Destructor

		FoamBase_EXPORT virtual ~processorCyclicPointPatch();


		// Member Functions


			//- Return message tag to use for communication
		virtual int tag() const
		{
			return procCycPolyPatch_.tag();
		}

		//- Return the underlying processorCyclicPolyPatch
		const processorCyclicPolyPatch& procCyclicPolyPatch() const
		{
			return procCycPolyPatch_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorCyclicPointPatch_Header
