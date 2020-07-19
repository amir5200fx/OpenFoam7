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
		TypeName("cyclicAMILduInterface");


		// Constructors

			//- Construct null
		cyclicAMILduInterface()
		{}


		//- Destructor
		virtual ~cyclicAMILduInterface();


		// Member Functions

			// Access

				//- Return neighbour
		virtual label neighbPatchID() const = 0;

		//- Does this side own the interface?
		virtual bool owner() const = 0;

		//- Return processor number
		virtual const cyclicAMILduInterface& neighbPatch() const = 0;

		//- Return a reference to the AMI interpolators
		virtual const PtrList<AMIInterpolation>& AMIs() const = 0;

		// Return a reference to the AMI transformations
		virtual const List<vectorTensorTransform>&
			AMITransforms() const = 0;

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const = 0;

		//- Return face reverse transformation tensor
		virtual const tensorField& reverseT() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMILduInterface_Header
