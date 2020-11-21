#pragma once
#ifndef _cyclicAMIPointPatch_Header
#define _cyclicAMIPointPatch_Header

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
	tnbLib::cyclicAMIPointPatch

Description
	Cyclic AMI point patch - place holder only

SourceFiles
	cyclicAMIPointPatch.C

\*---------------------------------------------------------------------------*/


#include <coupledFacePointPatch.hxx>
#include <cyclicAMIPolyPatch.hxx>
#include <pointBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicAMIPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicAMIPointPatch
		:
		public coupledFacePointPatch
	{
		// Private Data

			//- Local reference cast into the cyclic AMI patch
		const cyclicAMIPolyPatch& cyclicAMIPolyPatch_;


	protected:

		// Protected Member Functions

			//- Initialise the calculation of the patch geometry
		FoamFvMesh_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		FoamFvMesh_EXPORT virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamFvMesh_EXPORT virtual void initMovePoints(PstreamBuffers&, const pointField&);

		//- Correct patches after moving points
		FoamFvMesh_EXPORT virtual void movePoints(PstreamBuffers&, const pointField&);

		//- Initialise the update of the patch topology
		FoamFvMesh_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamFvMesh_EXPORT virtual void updateMesh(PstreamBuffers&);


	public:

		//- Runtime type information
		//TypeName(cyclicAMIPolyPatch::typeName_());
		static const char* typeName_() { return cyclicAMIPolyPatch::typeName_(); }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT cyclicAMIPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT cyclicAMIPointPatch(const cyclicAMIPointPatch&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicAMIPointPatch();


		// Member Functions

			//- Return true if this patch field is coupled
		FoamFvMesh_EXPORT virtual bool coupled() const;

		//- Return the constraint type this pointPatch implements.
		virtual const word& constraintType() const
		{
			return type();
		}

		//- Return the underlying cyclicAMIPolyPatch
		const cyclicAMIPolyPatch& cyclicAMIPatch() const
		{
			return cyclicAMIPolyPatch_;
		}

		//- Return neighbour point patch
		const cyclicAMIPointPatch& neighbPatch() const
		{
			label patchi = cyclicAMIPolyPatch_.neighbPatchID();
			const pointPatch& pp = this->boundaryMesh()[patchi];
			return refCast<const cyclicAMIPointPatch>(pp);
		}

		//- Are the cyclic planes parallel
		bool parallel() const
		{
			return cyclicAMIPolyPatch_.parallel();
		}

		//- Return face transformation tensor
		const tensorField& forwardT() const
		{
			return cyclicAMIPolyPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		const tensorField& reverseT() const
		{
			return cyclicAMIPolyPatch_.reverseT();
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const cyclicAMIPointPatch&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMIPointPatch_Header
