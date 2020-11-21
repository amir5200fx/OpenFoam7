#pragma once
#ifndef _coupledPointPatch_Header
#define _coupledPointPatch_Header

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
	tnbLib::coupledPointPatch

Description
	coupled patch for post-processing.  Used as the base class for processor
	and cyclic pointPatches

SourceFiles
	coupledPointPatch.C

\*---------------------------------------------------------------------------*/

#include <coupledPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointBoundaryMesh;

	/*---------------------------------------------------------------------------*\
						  Class coupledPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class coupledPointPatch
	{
		// Private Member Functions

			//- Disallow default bitwise copy construction
		FoamBase_EXPORT coupledPointPatch(const coupledPointPatch&);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const coupledPointPatch&);


	protected:

		// Protected Member Functions

			//- Initialise the calculation of the patch geometry
		FoamBase_EXPORT virtual void initGeometry(PstreamBuffers&) = 0;

		//- Calculate the patch geometry
		FoamBase_EXPORT virtual void calcGeometry(PstreamBuffers&) = 0;

		//- Initialise the patches for moving points
		FoamBase_EXPORT virtual void initMovePoints(PstreamBuffers&, const pointField&) = 0;

		//- Correct patches after moving points
		FoamBase_EXPORT virtual void movePoints(PstreamBuffers&, const pointField&) = 0;

		//- Initialise the update of the patch topology
		FoamBase_EXPORT virtual void initUpdateMesh(PstreamBuffers&) = 0;

		//- Update of the patch topology
		FoamBase_EXPORT virtual void updateMesh(PstreamBuffers&) = 0;


	public:

		//- Runtime type information
		//TypeName(coupledPolyPatch::typeName_());
		static const char* typeName_() { return coupledPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT coupledPointPatch(const pointBoundaryMesh& bm);


		//- Destructor
		FoamBase_EXPORT virtual ~coupledPointPatch();

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledPointPatch_Header
