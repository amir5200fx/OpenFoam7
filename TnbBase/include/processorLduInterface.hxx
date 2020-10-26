#pragma once
#ifndef _processorLduInterface_Header
#define _processorLduInterface_Header

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
	tnbLib::processorLduInterface

Description
	An abstract base class for processor coupled interfaces.

SourceFiles
	processorLduInterface.C
	processorLduInterfaceTemplates.C

\*---------------------------------------------------------------------------*/

#include <lduInterface.hxx>
#include <primitiveFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class processorLduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class processorLduInterface
	{
		// Private Data

			//- Send buffer.
			//  Only sized and used when compressed or non-blocking comms used.
		mutable List<char> sendBuf_;

		//- Receive buffer.
		//  Only sized and used when compressed or non-blocking comms used.
		mutable List<char> receiveBuf_;

		//- Resize the buffer if required
		FoamBase_EXPORT void resizeBuf(List<char>& buf, const label size) const;


	public:

		//- Runtime type information
		//TypeName("processorLduInterface");
		static const char* typeName_() { return "processorLduInterface"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		FoamBase_EXPORT processorLduInterface();


		//- Destructor
		FoamBase_EXPORT virtual ~processorLduInterface();


		// Member Functions

			// Access

				//- Return communicator used for parallel communication
		FoamBase_EXPORT virtual label comm() const = 0;

		//- Return processor number (rank in communicator)
		FoamBase_EXPORT virtual int myProcNo() const = 0;

		//- Return neighbour processor number (rank in communicator)
		FoamBase_EXPORT virtual int neighbProcNo() const = 0;

		//- Return face transformation tensor
		FoamBase_EXPORT virtual const tensorField& forwardT() const = 0;

		//- Return message tag used for sending
		FoamBase_EXPORT virtual int tag() const = 0;

		// Transfer functions

			//- Raw send function
		template<class Type>
		void send
		(
			const Pstream::commsTypes commsType,
			const UList<Type>&
		) const;

		//- Raw field receive function
		template<class Type>
		void receive
		(
			const Pstream::commsTypes commsType,
			UList<Type>&
		) const;

		//- Raw field receive function returning field
		template<class Type>
		tmp<Field<Type>> receive
		(
			const Pstream::commsTypes commsType,
			const label size
		) const;


		//- Raw field send function with data compression
		template<class Type>
		void compressedSend
		(
			const Pstream::commsTypes commsType,
			const UList<Type>&
		) const;

		//- Raw field receive function with data compression
		template<class Type>
		void compressedReceive
		(
			const Pstream::commsTypes commsType,
			UList<Type>&
		) const;

		//- Raw field receive function with data compression returning field
		template<class Type>
		tmp<Field<Type>> compressedReceive
		(
			const Pstream::commsTypes commsType,
			const label size
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <processorLduInterfaceTemplatesI.hxx>

//#ifdef NoRepository
//#include <processorLduInterfaceTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorLduInterface_Header
