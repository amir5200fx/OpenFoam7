#pragma once
#ifndef _processorGAMGInterface_Header
#define _processorGAMGInterface_Header

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
	tnbLib::processorGAMGInterface

Description
	GAMG agglomerated processor interface.

SourceFiles
	processorGAMGInterface.C

\*---------------------------------------------------------------------------*/

#include <GAMGInterface.hxx>
#include <processorLduInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class processorGAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class processorGAMGInterface
		:
		public GAMGInterface,
		public processorLduInterface
	{
		// Private Data

			//- Communicator to use for parallel communication
		const label comm_;

		//- My processor rank in communicator
		label myProcNo_;

		//- Neighbouring processor rank in communicator
		label neighbProcNo_;

		//- Transformation tensor
		tensorField forwardT_;

		//- Message tag used for sending
		int tag_;


	public:

		//- Runtime type information
		//TypeName("processor");
		static const char* typeName_() { return "processor"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from fine-level interface,
			//  local and neighbour restrict addressing
		FoamBase_EXPORT processorGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const lduInterface& fineInterface,
			const labelField& restrictAddressing,
			const labelField& neighbourRestrictAddressing,
			const label fineLevelIndex,
			const label coarseComm
		);

		//- Construct from components
		FoamBase_EXPORT processorGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const labelUList& faceCells,
			const labelUList& faceRestrictAddresssing,
			const label coarseComm,
			const label myProcNo,
			const label neighbProcNo,
			const tensorField& forwardT,
			const int tag
		);

		//- Construct from Istream
		FoamBase_EXPORT processorGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			Istream& is
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT processorGAMGInterface(const processorGAMGInterface&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~processorGAMGInterface();


		// Member Functions

			// Interface transfer functions

				//- Initialise neighbour field transfer
		FoamBase_EXPORT virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const;

		//- Transfer and return internal field adjacent to the interface
		FoamBase_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const;


		//- Processor interface functions

			//- Return communicator used for sending
		virtual label comm() const
		{
			return comm_;
		}

		//- Return processor number (rank in communicator)
		virtual int myProcNo() const
		{
			return myProcNo_;
		}

		//- Return neighbour processor number (rank in communicator)
		virtual int neighbProcNo() const
		{
			return neighbProcNo_;
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return forwardT_;
		}

		//- Return message tag used for sending
		virtual int tag() const
		{
			return tag_;
		}


		// I/O

			//- Write to stream
		FoamBase_EXPORT virtual void write(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const processorGAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorGAMGInterface_Header
