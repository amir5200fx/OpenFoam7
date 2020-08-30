#pragma once
#ifndef _processorPointPatch_Header
#define _processorPointPatch_Header

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
	tnbLib::processorPointPatch

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
	processorPointPatch.C

\*---------------------------------------------------------------------------*/

#include <coupledFacePointPatch.hxx>
#include <processorPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class processorPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class processorPointPatch
		:
		public coupledFacePointPatch
	{
		// Private Data

		const processorPolyPatch& procPolyPatch_;

		mutable labelList reverseMeshPoints_;


		// Private Member Functions

			//- Initialise the calculation of the patch geometry
		virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		virtual void initMovePoints(PstreamBuffers&, const pointField&);

		//- Correct patches after moving points
		virtual void movePoints(PstreamBuffers&, const pointField&);

		//- Initialise the update of the patch topology
		virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		virtual void updateMesh(PstreamBuffers&);


		//- Disallow default bitwise copy construction
		processorPointPatch(const processorPointPatch&);

		//- Disallow default bitwise assignment
		void operator=(const processorPointPatch&);

	public:

		//- Runtime type information
		TypeName(processorPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		processorPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);


		//- Destructor
		virtual ~processorPointPatch();


		// Member Functions

			//- Return message tag to use for communication
		virtual int tag() const
		{
			return procPolyPatch_.tag();
		}

		//- Return communicator used for communication
		virtual label comm() const
		{
			return procPolyPatch_.comm();
		}

		//- Return the constraint type this pointPatch implements.
		virtual const word& constraintType() const
		{
			return type();
		}

		//- Return processor number
		int myProcNo() const
		{
			return procPolyPatch_.myProcNo();
		}

		//- Return neighbour processor number
		int neighbProcNo() const
		{
			return procPolyPatch_.neighbProcNo();
		}

		//- Is this a master patch
		bool isMaster() const
		{
			return myProcNo() < neighbProcNo();
		}

		//- Is this a slave patch
		bool isSlave() const
		{
			return !isMaster();
		}

		//- Return the underlying processorPolyPatch
		const processorPolyPatch& procPolyPatch() const
		{
			return procPolyPatch_;
		}

		//- Return mesh points in the correct order for the receiving side
		const labelList& reverseMeshPoints() const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorPointPatch_Header