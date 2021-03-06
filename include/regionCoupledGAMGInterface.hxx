#pragma once
#ifndef _regionCoupledGAMGInterface_Header
#define _regionCoupledGAMGInterface_Header

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
	tnbLib::regionCoupledGAMGInterface

Description
	GAMG agglomerated coupled region interface.

SourceFiles
	regionCoupledGAMGInterface.C

\*---------------------------------------------------------------------------*/

#include <regionCoupledBaseGAMGInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class regionCoupledGAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledGAMGInterface
		:
		public regionCoupledBaseGAMGInterface
	{
	public:

		//- Runtime type information
		/*TypeName("regionCoupled");*/
		static const char* typeName_() { return "regionCoupled"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from fine level interface,
			//  local and neighbour restrict addressing
		FoamFvMesh_EXPORT regionCoupledGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const lduInterface& fineInterface,
			const labelField& restrictAddressing,
			const labelField& neighbourRestrictAddressing,
			const label fineLevelIndex,
			const label coarseComm
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT regionCoupledGAMGInterface(const regionCoupledGAMGInterface&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~regionCoupledGAMGInterface();


		// Member Functions

			// I/O

				//- Write to stream
		virtual void write(Ostream&) const
		{
			// TBD. How to serialise the AMI such that we can stream
			// regionCoupledGAMGInterface.
			NotImplemented;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const regionCoupledGAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledGAMGInterface_Header
