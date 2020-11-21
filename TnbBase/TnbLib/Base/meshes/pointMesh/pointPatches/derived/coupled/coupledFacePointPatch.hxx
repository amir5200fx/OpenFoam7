#pragma once
#ifndef _coupledFacePointPatch_Header
#define _coupledFacePointPatch_Header

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
	tnbLib::coupledFacePointPatch

Description
	coupled patch for post-processing.  Used as the base class for processor
	and cyclic pointPatches

SourceFiles
	coupledFacePointPatch.C

\*---------------------------------------------------------------------------*/

#include <coupledPointPatch.hxx>
#include <facePointPatch.hxx>
#include <coupledPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointBoundaryMesh;

	/*---------------------------------------------------------------------------*\
						  Class coupledFacePointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class coupledFacePointPatch
		:
		public facePointPatch,
		public coupledPointPatch
	{
		// Private Data

		const coupledPolyPatch& coupledPolyPatch_;


		// Private Member Functions

			//- Disallow default bitwise copy construction
		FoamBase_EXPORT coupledFacePointPatch(const coupledFacePointPatch&);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const coupledFacePointPatch&);


	protected:

		// Construction of demand-driven data

			//- Calculate mesh points
		FoamBase_EXPORT virtual void calcGeometry(PstreamBuffers&) = 0;


	public:

		//- Runtime type information
		//TypeName(coupledPolyPatch::typeName_());
		static const char* typeName_() { return coupledPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT coupledFacePointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);


		//- Destructor
		FoamBase_EXPORT virtual ~coupledFacePointPatch();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledFacePointPatch_Header
