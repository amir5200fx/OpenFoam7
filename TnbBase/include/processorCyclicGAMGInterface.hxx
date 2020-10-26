#pragma once
#ifndef _processorCyclicGAMGInterface_Header
#define _processorCyclicGAMGInterface_Header

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
	tnbLib::processorCyclicGAMGInterface

Description
	GAMG agglomerated processor interface.

SourceFiles
	processorCyclicGAMGInterface.C
	processorCyclicGAMGInterfaceTemplates.C

\*---------------------------------------------------------------------------*/

#include <processorGAMGInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class processorCyclicGAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class processorCyclicGAMGInterface
		:
		public processorGAMGInterface
	{

	public:

		//- Runtime type information
		//TypeName("processorCyclic");
		static const char* typeName_() { return "processorCyclic"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from fine-level interface,
			//  local and neighbour restrict addressing
		FoamBase_EXPORT processorCyclicGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const lduInterface& fineInterface,
			const labelField& restrictAddressing,
			const labelField& neighbourRestrictAddressing,
			const label fineLevelIndex,
			const label coarseComm
		);

		//- Construct from Istream
		FoamBase_EXPORT processorCyclicGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			Istream& is
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT processorCyclicGAMGInterface
		(
			const processorCyclicGAMGInterface&
		) = delete;


		// Destructor

		FoamBase_EXPORT virtual ~processorCyclicGAMGInterface();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const processorCyclicGAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorCyclicGAMGInterface_Header
