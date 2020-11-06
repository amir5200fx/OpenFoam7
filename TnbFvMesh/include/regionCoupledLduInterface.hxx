#pragma once
#ifndef _regionCoupledLduInterface_Header
#define _regionCoupledLduInterface_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::regionCoupledLduInterface

Description
	An abstract base class for region coupled interfaces

SourceFiles
	regionCoupledLduInterface.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <AMIInterpolation.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class regionCoupledLduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledLduInterface
	{

	public:

		//- Runtime type information
		/*TypeName("regionCoupledLduInterface");*/
		static const char* typeName_() { return "regionCoupledLduInterface"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		regionCoupledLduInterface()
		{}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~regionCoupledLduInterface();


		// Member Functions

			// Access

				//- Return neighbour
		FoamFvMesh_EXPORT virtual label neighbPatchID() const = 0;

		//- Is it owner?
		FoamFvMesh_EXPORT virtual bool owner() const = 0;

		//- Return neighb regionCoupledLduInterface
		FoamFvMesh_EXPORT virtual const regionCoupledLduInterface& neighbPatch() const = 0;

		//- Return AMI
		// virtual const AMIInterpolation& AMI() const = 0;

		//- Return nbrMesh
		FoamFvMesh_EXPORT virtual const polyMesh& nbrMesh() const = 0;


	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledLduInterface_Header
