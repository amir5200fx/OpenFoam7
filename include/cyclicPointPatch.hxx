#pragma once
#ifndef _cyclicPointPatch_Header
#define _cyclicPointPatch_Header

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
	tnbLib::cyclicPointPatch

Description
	Cyclic patch for post-processing.

SourceFiles
	cyclicPointPatch.C

\*---------------------------------------------------------------------------*/

#include <coupledFacePointPatch.hxx>
#include <cyclicPolyPatch.hxx>
#include <pointBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicPointPatch
		:
		public coupledFacePointPatch
	{
		// Private Data

			//- Local reference cast into the cyclic patch
		const cyclicPolyPatch& cyclicPolyPatch_;


		// Private Member Functions

			//- Disallow default bitwise copy construction
		FoamBase_EXPORT cyclicPointPatch(const cyclicPointPatch&);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const cyclicPointPatch&);


		// Demand driven private data

			//- Initialise the calculation of the patch geometry
		FoamBase_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		FoamBase_EXPORT virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamBase_EXPORT virtual void initMovePoints(PstreamBuffers&, const pointField&);

		//- Correct patches after moving points
		FoamBase_EXPORT virtual void movePoints(PstreamBuffers&, const pointField&);

		//- Initialise the update of the patch topology
		FoamBase_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamBase_EXPORT virtual void updateMesh(PstreamBuffers&);


	public:

		//- Runtime type information
		//TypeName(cyclicPolyPatch::typeName_());
		static const char* typeName_() { return cyclicPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT cyclicPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);


		//- Destructor
		FoamBase_EXPORT virtual ~cyclicPointPatch();


		// Member Functions

			// Access

				//- Return the constraint type this pointPatch implements.
		virtual const word& constraintType() const
		{
			return type();
		}

		//- Return the underlying cyclicPolyPatch
		FoamBase_EXPORT const cyclicPolyPatch& cyclicPatch() const
		{
			return cyclicPolyPatch_;
		}

		//- Return neighbour point patch
		FoamBase_EXPORT const cyclicPointPatch& neighbPatch() const
		{
			label patchi = cyclicPolyPatch_.neighbPatchID();
			const pointPatch& pp = this->boundaryMesh()[patchi];
			return refCast<const cyclicPointPatch>(pp);
		}

		//- Are the cyclic planes parallel
		bool parallel() const
		{
			return cyclicPolyPatch_.parallel();
		}

		//- Return face transformation tensor
		const tensorField& forwardT() const
		{
			return cyclicPolyPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		const tensorField& reverseT() const
		{
			return cyclicPolyPatch_.reverseT();
		}


		// Access functions for demand driven data

			//- Return the set of pairs of points that require transformation
			//  and/or mapping. First index is on this patch, second on the
			//  neighbour patch.
		FoamBase_EXPORT virtual const edgeList& transformPairs() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicPointPatch_Header
