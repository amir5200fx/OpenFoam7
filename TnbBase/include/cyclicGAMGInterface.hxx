#pragma once
#ifndef _cyclicGAMGInterface_Header
#define _cyclicGAMGInterface_Header

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
	tnbLib::cyclicGAMGInterface

Description
	GAMG agglomerated cyclic interface.

SourceFiles
	cyclicGAMGInterface.C

\*---------------------------------------------------------------------------*/

#include <GAMGInterface.hxx>
#include <cyclicLduInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicGAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicGAMGInterface
		:
		public GAMGInterface,
		public cyclicLduInterface
	{
		// Private Data

			//- Neighbour patch number
		label neighbPatchID_;

		//- Am I owner?
		bool owner_;

		//- Transformation tensor
		tensorField forwardT_;

		//- Transformation tensor
		tensorField reverseT_;


	public:

		//- Runtime type information
		//TypeName("cyclic");
		static const char* typeName_() { return "cyclic"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from fine level interface,
			//  local and neighbour restrict addressing
		FoamBase_EXPORT cyclicGAMGInterface
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
		FoamBase_EXPORT cyclicGAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			Istream& is
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT cyclicGAMGInterface(const cyclicGAMGInterface&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~cyclicGAMGInterface();


		// Member Functions

			// Interface transfer functions

				//- Transfer and return internal field adjacent to the interface
		FoamBase_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const;


		//- Cyclic interface functions

			//- Return neighbour processor number
		virtual label neighbPatchID() const
		{
			return neighbPatchID_;
		}

		virtual bool owner() const
		{
			return owner_;
		}

		virtual const cyclicGAMGInterface& neighbPatch() const
		{
			return dynamic_cast<const cyclicGAMGInterface&>
				(
					coarseInterfaces_[neighbPatchID()]
					);
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return forwardT_;
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return reverseT_;
		}


		// I/O

			//- Write to stream
		FoamBase_EXPORT virtual void write(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const cyclicGAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicGAMGInterface_Header
