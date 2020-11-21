#pragma once
#ifndef _cyclicAMILduInterface_Header
#define _cyclicAMILduInterface_Header

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
	tnbLib::cyclicAMILduInterface

Description
	An abstract base class for cyclic AMI coupled interfaces

SourceFiles
	cyclicAMILduInterface.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <AMIInterpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicAMILduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicAMILduInterface
	{

	public:

		//- Runtime type information
		//TypeName("cyclicAMILduInterface");
		static const char* typeName_() { return "cyclicAMILduInterface"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		cyclicAMILduInterface()
		{}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicAMILduInterface();


		// Member Functions

			// Access

				//- Return neighbour
		FoamFvMesh_EXPORT virtual label neighbPatchID() const = 0;

		//- Does this side own the interface?
		FoamFvMesh_EXPORT virtual bool owner() const = 0;

		//- Return processor number
		FoamFvMesh_EXPORT virtual const cyclicAMILduInterface& neighbPatch() const = 0;

		//- Return a reference to the AMI interpolators
		FoamFvMesh_EXPORT virtual const PtrList<AMIInterpolation>& AMIs() const = 0;

		// Return a reference to the AMI transformations
		FoamFvMesh_EXPORT virtual const List<vectorTensorTransform>&
			AMITransforms() const = 0;

		//- Return face transformation tensor
		FoamFvMesh_EXPORT virtual const tensorField& forwardT() const = 0;

		//- Return face reverse transformation tensor
		FoamFvMesh_EXPORT virtual const tensorField& reverseT() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMILduInterface_Header
